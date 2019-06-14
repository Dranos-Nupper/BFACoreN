/*
* Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "AccountMgr.h"
#include "BattlePay.h"
#include "BattlePayPackets.h"
#include "Chat.h"

void WorldSession::HandleGetProductList(WorldPackets::BattlePayPackets::GetProductList& /*getProductList*/)
{
    // always re-send feature system status in case shop was enabled/disabled since last products list check
    if (GetPlayer())
        SendFeatureSystemStatus();
    else
        SendFeatureSystemStatusGlueScreen();

    SendGetProductListResponse();
}

void WorldSession::HandleGetPurchaseList(WorldPackets::BattlePayPackets::GetPurchaseList& /*getPurchaseList*/)
{
    SendGetPurchaseListResponse();
}

void WorldSession::HandleStartPurchase(WorldPackets::BattlePayPackets::StartPurchase& packet)
{
    // check if valid product
    BattlePay::Product* product = sBattlePayMgr->GetProductByProductID(packet.ProductID);
    if (!product)
    {
        SendAckFailed(nullptr, BattlePay::Error::SHOP_ERROR_TRY_AGAIN);
        return;
    }

    BattlePay::Purchase* purchase = new BattlePay::Purchase(sBattlePayMgr->GeneratePurchaseID(), BattlePay::PurchaseStatus::WAITING_CONFIRMATION, packet.ProductID);
    sBattlePayMgr->AddPendingPurchase(purchase);

    SendStartPurchaseResponse(packet.ClientToken, purchase->PurchaseID, 0);
    SendPurchaseUpdate(purchase);
    SendConfirmPurchase(purchase->PurchaseID, purchase->PurchaseID, 0);

    if (!purchase)
    {
        SendAckFailed(NULL, BattlePay::Error::SHOP_ERROR_TRY_AGAIN);
        return;
    }

    // check various restrictions / funds / etc
    TrinityStrings customError = LANG_NONE;
    BattlePay::Error error = sBattlePayMgr->IsValidPurchase(this, purchase, customError);
    if (customError != LANG_NONE)
        if (Player* player = GetPlayer())
            ChatHandler(this).PSendSysMessage(customError);

    if (error != BattlePay::Error::OK)
    {
        SendAckFailed(purchase, error);
        return;
    }

    // update purchase status
    purchase->Status = BattlePay::PurchaseStatus::FINISHED;

    // send product and delivery notification (delivery only for items)
    if (uint32 itemId = sBattlePayMgr->FinalizePurchase(this, purchase))
        SendDeliveryEnded(itemId);

    // update product list because balance was modified, "HasItem" was modified, etc
    SendGetProductListResponse();

    // send purchase update
    SendPurchaseUpdate(purchase);

    // cleanup (if an error was triggered, purchase will be deleted in HandleAckFailedResponse)
    sBattlePayMgr->DeletePurchase(purchase);
}

void WorldSession::HandleConfirmPurchaseResponse(WorldPackets::BattlePayPackets::ConfirmPurchaseResponse& packet)
{
    uint64 PurchaseId = packet.ServerToken; // PurchaseID used as ServerToken

    // check if valid active purchase
    BattlePay::Purchase* purchase = sBattlePayMgr->GetPurchaseByPurchaseID(PurchaseId);
    if (!purchase)
    {
        SendAckFailed(NULL, BattlePay::Error::SHOP_ERROR_TRY_AGAIN);
        return;
    }

    if (packet.ConfirmPurchase)
    {
        // check various restrictions / funds / etc
        TrinityStrings customError = LANG_NONE;
        BattlePay::Error error = sBattlePayMgr->IsValidPurchase(this, purchase, customError);
        if (customError != LANG_NONE)
            if (Player* player = GetPlayer())
                ChatHandler(this).PSendSysMessage(customError);

        if (error != BattlePay::Error::OK)
        {
            SendAckFailed(purchase, error);
            return;
        }

        // update purchase status
        purchase->Status = BattlePay::PurchaseStatus::FINISHED;

        // send product and delivery notification (delivery only for items)
        if (uint32 itemId = sBattlePayMgr->FinalizePurchase(this, purchase))
            SendDeliveryEnded(itemId);

        // update product list because balance was modified, "HasItem" was modified, etc
        SendGetProductListResponse();
    }
    else
        purchase->ResultCode = 1; // unknown, seems to cancel the purchase clientside

    // send purchase update
    SendPurchaseUpdate(purchase);

    // cleanup (if an error was triggered, purchase will be deleted in HandleAckFailedResponse)
    sBattlePayMgr->DeletePurchase(purchase);
}

void WorldSession::HandleAckFailedResponse(WorldPackets::BattlePayPackets::AckFailedResponse& packet)
{
    uint64 PurchaseID = packet.ServerToken; // ServerToken used as PurchaseID

    BattlePay::Purchase* purchase = sBattlePayMgr->GetPurchaseByPurchaseID(PurchaseID);
    if (!purchase)
        return;

    // cleanup
    sBattlePayMgr->DeletePurchase(purchase);
}

void WorldSession::SendGetProductListResponse()
{
    // get copies of products / groups / shop entries to be modified for each player separately
    BattlePay::ProductList products = sBattlePayMgr->GetStoreProducts();
    BattlePay::GroupList groups = sBattlePayMgr->GetStoreGroups();
    BattlePay::ShopEntryList shopEntries = sBattlePayMgr->GetStoreEntries();

    // update products status/data for current player
    sBattlePayMgr->UpdateProductListForPlayer(this, products, groups, shopEntries);

    WorldPackets::BattlePayPackets::GetProductListResponse packet;

    for (auto currentProduct : products)
        packet.Products.push_back(currentProduct);

    for (auto shopEntry : shopEntries)
        packet.ShopEntries.push_back(shopEntry);

    for (auto group : groups)
        packet.Groups.push_back(group);

    packet.CurrencyID = BattlePay::Currency::BATTLE_COIN;
    packet.Result = 0;

    SendPacket(packet.Write());
}

void WorldSession::SendGetPurchaseListResponse()
{
    WorldPackets::BattlePayPackets::GetPurchaseListResponse packet;

    packet.Result = 0;

    SendPacket(packet.Write());
}

void WorldSession::SendGetDistributionListResponse()
{
    WorldPackets::BattlePayPackets::GetDistributionListResponse packet;

    packet.Result = 0;

    SendPacket(packet.Write());
}

void WorldSession::SendStartPurchaseResponse( uint32 ClientToken, uint64 PurchaseID, uint32 PurchaseResult)
{
    WorldPackets::BattlePayPackets::StartPurchaseResponse packet;

    packet.PurchaseID = PurchaseID;
    packet.PurchaseResult = PurchaseResult;
    packet.ClientToken = ClientToken;

    SendPacket(packet.Write());
}

void WorldSession::SendConfirmPurchase(uint32 ServerToken, uint64 PurchaseID, uint64 CurrentFixedPrice)
{
    WorldPackets::BattlePayPackets::ConfirmPurchase packet;

    packet.PurchaseID = PurchaseID;
    packet.CurrentPriceFixedPoint = CurrentFixedPrice;
    packet.ServerToken = ServerToken;

    SendPacket(packet.Write());
}

void WorldSession::SendPurchaseUpdate(BattlePay::Purchase* purchase)
{
    WorldPackets::BattlePayPackets::PurchaseUpdate packet;

    BattlePay::Purchase purchasePacket = *purchase;
    AccountMgr::GetName(GetAccountId(), purchasePacket.WalletName);
    packet.Purchases.push_back(purchasePacket);

    SendPacket(packet.Write());
}

void WorldSession::SendDeliveryEnded(uint32 itemId)
{
    WorldPackets::BattlePayPackets::DeliveryEnded packet;

    packet.DistributionID = 0;

    WorldPackets::Item::ItemInstance item;
    item.ItemID = itemId;
    packet.Items.push_back(item);

    SendPacket(packet.Write());
}

void WorldSession::SendAckFailed(BattlePay::Purchase* purchase, BattlePay::Error error)
{
    // cancel pending purchase clientside
    if (purchase)
    {
        purchase->ResultCode = 1; // unknown, seems to cancel the purchase clientside
        SendPurchaseUpdate(purchase);
    }

    WorldPackets::BattlePayPackets::AckFailed packet;

    packet.Status = 0;
    packet.Result = error;
    packet.ServerToken = purchase ? purchase->PurchaseID : 1; // must be > 0 to trigger error frame
    packet.PurchaseID = purchase ? purchase->PurchaseID : 1;

    SendPacket(packet.Write());
}
