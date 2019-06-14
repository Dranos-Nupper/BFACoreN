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

#include "BattlePay.h"
#include "Realm.h"
#include "Config.h"
#include "ReputationMgr.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "Guild.h"
#include "Item.h"
#include "Bag.h"
#include "SpellMgr.h"
#include "SpellInfo.h"
#include "ObjectMgr.h"
#include "BattlePetMgr.h"

namespace BattlePay {

Manager* Manager::instance()
{
    static Manager instance;
    return &instance;
}

Manager::Manager()
{
    lastPurchaseId = 1;
}

void Manager::CacheData()
{
    // cache glyphs
    static uint32 const toExclude[] = { 43384, 37301, 63415, 43362, 40948, 43337, 43336, 45908, 71799, 85708, 85711, 85686, 87886, 85712, 76729 };
    ItemTemplateContainer const* its = sObjectMgr->GetItemTemplateStore();
    for (ItemTemplateContainer::const_iterator itr = its->begin(); itr != its->end(); ++itr)
    {
        const ItemTemplate * itemTemplate = &itr->second;

        // must be glyph
        if (itemTemplate->GetClass() != ITEM_CLASS_GLYPH)
            continue;

        // check if excluded
        uint32 itemId = itr->first;
        bool exclude = false;
        for (auto tmpItemId : toExclude)
        {
            if (tmpItemId == itemId)
            {
                exclude = true;
                break;
            }
        }
        if (exclude)
            continue;

        cacheGlyphs.push_back(itemId);
    }
}

void Manager::LoadFromDB()
{
    products.clear();
    groups.clear();
    shopEntries.clear();

    // groups
    if (QueryResult result = WorldDatabase.PQuery("SELECT id, ordering, name, iconFileDataId, displayType FROM battlepay_groups"))
    {
        do
        {
            Field * fields = result->Fetch();
            groups.push_back(Group(fields[0].GetUInt32(), fields[1].GetInt32(), fields[2].GetString(), fields[3].GetUInt32(), fields[4].GetUInt8()));
        } while (result->NextRow());
    }

    // products
    if (QueryResult result = WorldDatabase.PQuery("SELECT id, itemId, quantity, groupId, ordering, bannerType, choiceType, price, serverHardcodedId, displayCreature, displayFileData, displayItem, displayCustomItemDeliveryId, customFlags, customValue, logType, name, description FROM battlepay_products"))
    {
        do 
        {
            Field * fields = result->Fetch();
            uint32 fieldIndex = 0;

            uint32 productId = fields[fieldIndex++].GetUInt32();
            uint32 itemId = fields[fieldIndex++].GetUInt32();
            uint32 quantity = fields[fieldIndex++].GetUInt32();
            uint32 groupId = fields[fieldIndex++].GetUInt32();
            int32 ordering = fields[fieldIndex++].GetInt32();
            uint8 bannerType = fields[fieldIndex++].GetUInt8();
            uint8 choiceType = fields[fieldIndex++].GetUInt8();
            float price = fields[fieldIndex++].GetFloat();
            uint32 serverHardcodedId = fields[fieldIndex++].GetUInt32();
            uint32 displayCreature = fields[fieldIndex++].GetUInt32();
            uint32 displayFileData = fields[fieldIndex++].GetUInt32();
            uint32 displayItem = fields[fieldIndex++].GetUInt32();
            uint32 displayCustomItemDeliveryId = fields[fieldIndex++].GetUInt32();
            uint32 customFlags = fields[fieldIndex++].GetUInt32();
            int32 customValue = fields[fieldIndex++].GetInt32();
            uint32 logType = fields[fieldIndex++].GetInt32();
            std::string name = fields[fieldIndex++].GetString();
            std::string description = fields[fieldIndex++].GetString();
            
            // name/description
            if (itemId)
            {
                if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId))
                {
                    // if name empty, use default item name
                    if (name.empty())
                    {
                        std::ostringstream currentName;
                        
                        // show text color based on item quality
                        char tmpName[1024];
                        uint32 quality = itemTemplate->GetQuality();
                        if (itemTemplate->GetFlags3() & ITEM_FLAG3_DISPLAY_AS_HEIRLOOM)
                            quality = ITEM_QUALITY_HEIRLOOM;
                        sprintf(tmpName, "|c%X%s|r", ItemQualityColors[quality], itemTemplate->GetName(LOCALE_enUS));

                        // hide "Prideful Gladiator's " and show full item name as description
                        std::string replaceTmpName = tmpName;
                        std::string replaceFrom = "Prideful Gladiator's ";
                        size_t start_pos = replaceTmpName.find(replaceFrom);
                        if (start_pos != std::string::npos)
                        {
                            replaceTmpName.replace(start_pos, std::string(replaceFrom).length(), std::string(""));
                            std::ostringstream tmpDescription;
                            tmpDescription << "|cFFA335EE[" << itemTemplate->GetName(LOCALE_enUS) << "]|r";
                            if (!description.empty())
                                tmpDescription << '\n' << '\n' << description;
                            description = tmpDescription.str();
                        }

                        currentName << replaceTmpName;

                        // add 2 blank lines if showing item level or item name description
                        if (customFlags & (ProductFlagsCu::SHOW_ITEM_NAME_DESCRIPTION | ProductFlagsCu::SHOW_ITEM_LEVEL))
                            currentName << '\n' << '\n';

                        // item name description
                        /*if (customFlags & ProductFlagsCu::SHOW_ITEM_NAME_DESCRIPTION)
                            if (auto nameDescription = PROJECT::DataStores::ItemNameDescription.LookupEntry(itemId))
                                if (strlen(nameDescription->Description))
                                    currentName << "|cFF00FF00(" << nameDescription->Description << ")|r";*/

                        // item level
                        if (customFlags & ProductFlagsCu::SHOW_ITEM_LEVEL)
                        {
                            if (customFlags & ProductFlagsCu::SHOW_ITEM_NAME_DESCRIPTION)
                                currentName << " ";
                            currentName << "[" << itemTemplate->GetBaseItemLevel() << "]";
                        }

                        name = currentName.str();
                    }
                }
            } // if (itemId)

            if (!description.empty())
            {
                // replace ~~ with newline
                std::ostringstream to;
                to << '\n';
                do
                {
                    size_t start_pos = description.find("~~");
                    if (start_pos == std::string::npos)
                        break;
                    description.replace(start_pos, std::string("~~").length(), to.str());
                } while (true);
            }

            switch (serverHardcodedId)
            {
                // Battle Pets
                case HardcodedProducts::PET:
                {
                    // all battle pets bought through shop have Rare quality
                    std::ostringstream tmpName;
                    tmpName << "|cFF0070DD" << name << "|r";
                    name = tmpName.str();
                    break;
                }
            }

            // add product
            DisplayInfoStruct displayInfo(displayCreature, displayFileData, 0, displayItem, name, description, "");
            products.push_back(Product(productId, itemId, quantity, price, ProductFlags::ACTIVE_INGAME, choiceType, displayInfo, serverHardcodedId, displayCustomItemDeliveryId, customFlags, customValue, logType));
            shopEntries.push_back(ShopEntry(productId, groupId, productId, ordering, bannerType));
        } while (result->NextRow());
    }
}

void Manager::AddPendingPurchase(Purchase * purchase)
{
    activePurchases.push_back(purchase);
}

uint64 Manager::GeneratePurchaseID()
{
    return ++lastPurchaseId;
}

Purchase * Manager::GetPurchaseByPurchaseID(uint64 purchaseId)
{
    for (auto purchase : activePurchases)
        if (purchase->PurchaseID == purchaseId)
            return purchase;

    return NULL;
}

Product * Manager::GetProductByProductID(uint32 productId)
{
    for (ProductList::iterator it = products.begin(); it != products.end(); ++it)
        if (it->ID == productId)
            return &*it;

    return NULL;
}

void Manager::DeletePurchase(uint64 purchaseId)
{
    for (PurchaseList::iterator it = activePurchases.begin(); it != activePurchases.end(); ++it)
    {
        if ((*it)->PurchaseID == purchaseId)
        {
            DeletePurchase(*it);
            return;
        }
    }
}

void Manager::DeletePurchase(Purchase * purchase)
{
    activePurchases.erase(std::remove_if(activePurchases.begin(), activePurchases.end(),
        [&purchase](const Purchase * purchaseIterator) { return purchaseIterator == purchase; }), activePurchases.end());

    delete purchase;
}

uint32 Manager::FinalizePurchase(WorldSession * session, Purchase * purchase)
{
    Product * baseProduct = sBattlePayMgr->GetProductByProductID(purchase->ProductId);
    if (!baseProduct)
        return 0;

    PlayerSpecificValues playerSpecificValues = sBattlePayMgr->GetPlayerValues(session);

    // make a copy of the product
    Product product = *baseProduct;
    // and update it for the current player
    UpdateProductForPlayer(session, &product);

    // should always return valid player because this is checked in IsValidPurchase()
    Player * player = session->GetPlayer();
    uint32 playerFaction = player->GetTeam();
    uint8 playerClass = player->getClass();


    // spend funds
    SpendPlayerFunds(session, &product);

    uint32 learnedNpcId = 0;
    uint32 currentTime = time(nullptr);

    // hardcoded custom product IDs
    bool ignoreItem = false;
    std::vector<uint32> itemsToAdd;
    switch (product.HardcodedID)
    {
        // Level 90
        case HardcodedProducts::LEVEL_BOOST:
        {
            player->GiveLevel(sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL));
            player->InitTalentForLevel();
            player->SetUInt32Value(ACTIVE_PLAYER_FIELD_XP, 0);
            // add end-level quests
            bool isPandarenNeutral = player->getRace() == RACE_PANDAREN_NEUTRAL;
            std::vector<uint32> questsToAdd;
            if (playerFaction == HORDE || isPandarenNeutral)
            {
                // quests for Pandaria map
                questsToAdd.push_back(29611);   // The Art of War
                questsToAdd.push_back(31853);   // All Aboard!
                questsToAdd.push_back(29690);   // Into the Mists
                if (playerClass == CLASS_DEATH_KNIGHT)
                    questsToAdd.push_back(13189);
            }
            if (playerFaction == ALLIANCE || isPandarenNeutral)
            {
                // quests for Pandaria map
                questsToAdd.push_back(29547);   // The King's Command
                questsToAdd.push_back(29548);   // The Mission
                if (playerClass == CLASS_DEATH_KNIGHT)
                    questsToAdd.push_back(13188);
            }
            // pandarens
            if (isPandarenNeutral)
            {
                // add "A New Fate" quest
                if (Quest const* quest = sObjectMgr->GetQuestTemplate(31450))
                {
                    player->AddQuest(quest, NULL);
                    player->CompleteQuest(quest->GetQuestId());
                }
                // send faction selection screen
                player->ShowNeutralPlayerFactionSelectUI();
            }
            for (auto questId : questsToAdd)
                if (Quest const* quest = sObjectMgr->GetQuestTemplate(questId))
                    player->RewardQuest(quest, 0, NULL, true);
            break;
        }
        // Gold
        case HardcodedProducts::GOLD:
            player->ModifyMoney(product.Quantity * GOLD);
            break;
        // Codex of Xerrath
        case HardcodedProducts::CODEX_OF_XERRATH:
            player->LearnSpell(137206, false);
            player->LearnSpell(101508, false);
            break;
        // Battle Pets
        /*case HardcodedProducts::PET:
        {
            // don't directly add the pet with default stats, we want all pets to be of Rare quality
            uint32 speciesId = product.CustomValue;
            uint8 breed = PROJECT::BattlePets::Manager::GeneratePetBreed(speciesId);
            uint8 quality = ITEM_QUALITY_RARE;
            uint8 level = PROJECT::Config->GetInt("PetBattles.InitialLevel");

            player->GetBattlePetMgr()->Create(speciesId, level, quality, breed);

            ignoreItem = true;

            if (auto speciesData = sBattlePetSpeciesStore.LookupEntry(speciesId))
                learnedNpcId = speciesData->CreatureID;
            break;
        }
        // Battle Pet Level up
        case HardcodedProducts::PET_LEVEL_25:
        {
            // should always return valid pet, already checked in UpdateProductForPlayer()
            auto * pet = player->GetBattlePetMgr()->GetCurrentBattlePet();
            do
            {
                if (pet->GetLevel() >= PROJECT::BattlePets::Constants::MAX_PET_LEVEL)
                    break;
                // use XP gain to trigger achievements/kill credits/etc
                PROJECT::BattlePets::Battles::GiveXP(pet, PROJECT::BattlePets::GetMaxXPForLevel(pet->GetLevel()));
            } while (true);
            pet->XP = 0;
            pet->CalculateStats(true);
            player->GetBattlePetMgr()->SendBattlePetUpdate(pet, true);
            pet->Save();

            if (auto speciesData = sBattlePetSpeciesStore.LookupEntry(pet->GetSpecies()))
                learnedNpcId = speciesData->CreatureID;
            break;
        }
        // Batle Pet upgrade Epic
        case HardcodedProducts::PET_UPGRADE_EPIC:
        {
            // should always return valid pet, already checked in UpdateProductForPlayer()
            auto * pet = player->GetBattlePetMgr()->GetCurrentBattlePet();
            pet->SetQuality(ITEM_QUALITY_EPIC);
            pet->CalculateStats(true);
            player->GetBattlePetMgr()->SendBattlePetUpdate(pet, true);
            pet->Save();

            if (auto speciesData = sBattlePetSpeciesStore.LookupEntry(pet->GetSpecies()))
                learnedNpcId = speciesData->CreatureID;
            break;
        }*/
        // Mounts
        case HardcodedProducts::MOUNT:
            player->LearnSpell(product.CustomValue, false);
            ignoreItem = true;
            break;
        // Titles
        case HardcodedProducts::TITLE:
            if (CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(product.CustomValue))
                player->SetTitle(titleInfo);
            break;
        // Guild Reputation
        /*case HardcodedProducts::GUILD_REPUTATION:
        {
            if (FactionEntry const* factionEntry = sFactionStore.LookupEntry(PROJECT::Constants::Reputations::GUILD))
            {
                player->GetReputationMgr().SetOneFactionReputation(factionEntry, ReputationMgr::Reputation_Cap, false);
                player->GetReputationMgr().SendState(player->GetReputationMgr().GetState(factionEntry));
            }
            break;
        }*/
        // Character rename
        case HardcodedProducts::CHAR_RENAME:
            player->SetAtLoginFlag(AT_LOGIN_RENAME);
            break;
        // Character customize
        case HardcodedProducts::CHAR_CUSTOMIZE:
            player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
            break;
        // Character race chage
        case HardcodedProducts::CHAR_RACE_CHANGE:
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
            break;
        // Character faction change
        case HardcodedProducts::CHAR_FACTION_CHANGE:
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
            break;
        // Umute
        case HardcodedProducts::UNMUTE:
        {
            session->m_muteTime = 0;
            ChatHandler(session).PSendSysMessage(LANG_YOUR_CHAT_ENABLED);

            // must also update database
            PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_MUTE_TIME);
            stmt->setInt64(0, 0);
            stmt->setString(1, "");
            stmt->setString(2, "");
            stmt->setUInt32(3, session->GetAccountId());
            LoginDatabase.Execute(stmt);

            break;
        }
        // Full ilvl upgrade
        /*case HardcodedProducts::ILVL_UPGRADE_FULL:
            for (EquipmentSlots slot = EQUIPMENT_SLOT_HEAD; slot < EQUIPMENT_SLOT_TABARD; slot = (EquipmentSlots)(int(slot) + 1))
            {
                if (Item* item = PROJECT::Utils::Items::GetEquippedItem(player, slot))
                {
                    // item can never be upgraded
                    if (!item->GetModifier(ITEM_MODIFIER_UPGRADE_ID))
                        continue;
                    // check if donated
                    if (!item->HasFlag(ITEM_FIELD_FLAGS, PROJECT::Constants::Items::Flags::BOUGHT_FROM_DONATION_SHOP))
                        continue;
                    bool upgraded = false;
                    // upgrade the item
                    do 
                    {
                        upgraded = false;
                        uint32 currentUpgradeId = item->GetModifier(ITEM_MODIFIER_UPGRADE_ID);
                        for (uint32 i = 0; i < sItemUpgradeStore.GetNumRows(); i++)
                        {
                            if (auto currentUpgrade = sItemUpgradeStore.LookupEntry(i))
                            {
                                if (currentUpgrade->PrerequisiteID == currentUpgradeId)
                                {
                                    // equipped, unapply and apply item stats bonuses
                                    player->_ApplyItemMods(item, item->GetSlot(), false);

                                    // set upgrade id
                                    item->SetModifier(ITEM_MODIFIER_UPGRADE_ID, currentUpgrade->ID);
                                    // recalculate random suffix factor
                                    if (item->GetItemRandomPropertyId() < 0)
                                        item->UpdateItemSuffixFactor();

                                    // reapply item stats bonuses
                                    player->_ApplyItemMods(item, item->GetSlot(), true);

                                    upgraded = true;

                                    break;
                                }
                            }
                        }
                    } while (upgraded);
                }
            }
            break;*/
        // Professions
        case HardcodedProducts::PROFESSION_SKILL:
            if (auto spellInfo = sSpellMgr->GetSpellInfo(product.CustomValue))
            {
                uint32 skillId = spellInfo->GetEffect(EFFECT_1)->MiscValue;
                uint32 maxSkill = spellInfo->GetEffect(EFFECT_1)->BasePoints * 75;

                // learn last rank spell if not known
                if (!player->HasSpell(product.CustomValue))
                    player->LearnSpell(product.CustomValue, false);
                // set max skill
                player->SetSkill(skillId, player->GetSkillStep(skillId), maxSkill, maxSkill);
            }
            break;
        // All glyphs for class
        case HardcodedProducts::ALL_CLASS_GLYPHS:
            for (auto itemId : cacheGlyphs)
            {
                ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);

                // must be for player's class
                if (itemTemplate->GetSubClass() != player->getClass())
                    continue;

                if (itemTemplate->Effects.size() < 2)
                    continue;

                // add spell
                if (int32 spellId = itemTemplate->Effects[1]->SpellID)
                    if (spellId > 0)
                        if (!player->HasSpell(spellId))
                            player->LearnSpell(spellId, false);
            }
            break;
        // Challenge transmog gear set
        case HardcodedProducts::TRANSMOG_CHALLENGE_SET:
        {
            ignoreItem = true;
            ShopEntryList & shopEntries = sBattlePayMgr->GetStoreActualEntries();
            uint32 classMask = 1 << (playerSpecificValues.GetClass() - 1);
            // get all items which have class requirement from Transmog gear group (only Challenge mode items have class requirement)
            for (auto currentShopEntry : shopEntries)
            {
                if (currentShopEntry.GroupID != HardcodedGroups::GROUP_TRANSMOG_GEAR)
                    continue;
                Product * currentProduct = sBattlePayMgr->GetProductByProductID(currentShopEntry.ProductID);
                if (!currentProduct)
                    continue;
                ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(currentProduct->ItemID);
                if (!itemTemplate)
                    continue;

                // ignore items without class requirement
                if (itemTemplate->GetAllowableClass() == (uint32)-1 || !itemTemplate->GetAllowableClass())
                    continue;

                // ignore items with item level different than (Kor'kron Dark Shaman)
                if (itemTemplate->GetBaseItemLevel() != 90)
                    continue;

                // ignore items not for current class
                if (!(classMask & itemTemplate->GetAllowableClass()))
                    continue;

                itemsToAdd.push_back(itemTemplate->GetId());
            }
            break;
        }
    }

    // give item (or learn triggered spell from item)
    uint32 itemId = product.ItemID;
    if (!ignoreItem && itemId)
        itemsToAdd.push_back(itemId);
    for (auto currentItemId : itemsToAdd)
    {
        if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(currentItemId))
        {
            // learning
            bool spellLearned = false;
            if (proto->Effects.size() >= 2 && (proto->Effects[0]->SpellID == 483 || proto->Effects[0]->SpellID == 55884))
            {
                if (int32 learnSpellId = proto->Effects[1]->SpellID)
                {
                    if (learnSpellId > 0 && !player->HasSpell(learnSpellId))
                    {
                        spellLearned = true;

                        player->LearnSpell(learnSpellId, false);
                    }
                }
            }
            // otherwise add item
            if (!spellLearned)
            {
                uint32 noSpaceForCount = 0;
                uint32 count = product.Quantity;
                ItemPosCountVec dest;

                // faction-specific items
                /*if (uint32 factionSpecificItem = PROJECT::Loots::GetFactionSpecificItem(player, currentItemId))
                    currentItemId = factionSpecificItem;*/
                
                // update main itemId variable with last item so it will show ItemDelivery
                itemId = currentItemId;

                InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, currentItemId, count, &noSpaceForCount);
                if (msg != EQUIP_ERR_OK) // convert to possible store amount
                    count -= noSpaceForCount;
                if (count > 0 && !dest.empty())
                {
                    if (Item * item = player->StoreNewItem(dest, currentItemId, true, GenerateItemRandomPropertyId(currentItemId)))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_BOUGHT_FROM_SHOP);
                        player->SendNewItem(item, count, false, true);
                    }
                }
            }
        }

        // reward log
        /*std::ostringstream info;
        info << currentItemId;
        PreparedStatement* stmt = ShopDatabase.GetPreparedStatement(SHOP_INS_DONATIONS_REWARD_LOG);
        stmt->setInt32(0, session->GetAccountId());
        stmt->setInt32(1, player->GetGUID().GetCounter());
        stmt->setString(2, player->GetName());
        stmt->setUInt8(3, realm.Id.Realm);
        stmt->setUInt8(4, product.LogType);
        stmt->setInt32(5, currentTime);
        stmt->setString(6, info.str());
        ShopDatabase.Execute(stmt);*/
    }

    // reward log
    if (product.LogType)
    {
        std::ostringstream info;
        // explicit data logging
        bool alreadyLogged = false;
        switch (product.LogType)
        {
            // already logged manually above
            case LogType::LOG_ITEM:
                alreadyLogged = true;
                break;
            case LogType::LOG_SPELL:
                info << product.CustomValue;
                break;
            case LogType::LOG_TITLE:
                if (CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(product.CustomValue))
                    info << titleInfo->Name->Str[LOCALE_enUS];
                break;
            case LogType::LOG_GOLD:
                info << product.Quantity;
                break;
            case LogType::LOG_ALL_CLASS_GLYPHS:
                info << sChrClassesStore.LookupEntry(player->getClass())->Name->Str[LOCALE_enUS];
                break;
            case LogType::LOG_BATTLE_PET:
            case LogType::LOG_BATTLE_PET_LEVEL:
            case LogType::LOG_BATTLE_PET_UPGRADE:
                info << learnedNpcId;
                break;
            case LogType::LOG_GUILD_LEVEL:
            case LogType::LOG_GUILD_LEVEL_25:
                info << player->GetGuild()->GetName();
                break;
        }
        /*if (!alreadyLogged)
        {
            std::string infoStr = info.str().empty() ? "" : info.str().c_str();
            do
            {
                size_t start_pos = infoStr.find("'");
                if (start_pos == std::string::npos)
                    break;
                infoStr.replace(start_pos, std::string("'").length(), " ");
            } while (true);

            PreparedStatement* stmt = ShopDatabase.GetPreparedStatement(SHOP_INS_DONATIONS_REWARD_LOG);
            stmt->setInt32(0, session->GetAccountId());
            stmt->setInt32(1, player->GetGUID().GetCounter());
            stmt->setString(2, player->GetName());
            stmt->setUInt8(3, realm.Id.Realm);
            stmt->setUInt8(4, product.LogType);
            stmt->setInt32(5, currentTime);
            stmt->setString(6, infoStr);
            ShopDatabase.Execute(stmt);
        }*/
    }

    // make sure player is instantly saved to DB because funds data is also modified instantly
    player->SaveToDB();

    // show message in chat
    std::string itemName = product.DisplayInfo.Name1.c_str();
    do
    {
        size_t start_pos = itemName.find('\n'); // remove new lines
        if (start_pos == std::string::npos)
            break;
        itemName.replace(start_pos, 1, std::string(" "));
    } while (true);
    //PROJECT::Messages::SendToPlayer(player, PROJECT::Messages::Types::BOTH, PROJECT::Language::Strings::BATTLE_PAY_PRODUCT_SUCCESSFULLY_BOUGHT, itemName.c_str(), product.GetCost(), sBattlePayMgr->GetPlayerFunds(session));

    // returns item id to show DeliveryEnded
    if (product.CustomItemDeliveryId)
        return product.CustomItemDeliveryId;
    return itemId;
}

Error Manager::IsValidPurchase(WorldSession * session, Purchase * purchase, TrinityStrings& customError)
{
    customError = LANG_NONE;

    // check if valid product
    Product * baseProduct = sBattlePayMgr->GetProductByProductID(purchase->ProductId);
    if (!baseProduct)
        return Error::SHOP_ERROR_TRY_AGAIN;

    // check if store enabled
    if (!IsStoreEnabled() ||!IsStoreAvailable())
        return Error::BATTLEPAY_DISABLED;

    // make a copy of the product
    Product product = *baseProduct;
    // and update it for the current player
    UpdateProductForPlayer(session, &product);

    // allow only if logged in
    Player * player = session->GetPlayer();
    if (!player)
        return Error::PURCHASE_DENIED;

    // check if enough money
    if (product.GetCost() > sBattlePayMgr->GetPlayerFunds(session))
        return Error::INSUFFICIENT_BALANCE;

    // check if disabled due to custom restrictions in UpdateProductListForPlayer()
    if (!product.IsBuyableIngame())
        return Error::PURCHASE_DENIED;

    // check if already has product
    if (product.HasProduct())
        return Error::PURCHASE_DENIED;

    // check if enough room in bags
    uint32 productCount = product.Quantity;
    uint32 productItem = product.ItemID;
    // hack for Challenge Conqueror transmog set
    if (product.HardcodedID == HardcodedProducts::TRANSMOG_CHALLENGE_SET)
    {
        productCount = 8;
        productItem = 90136; // random item id
    }
    if (productItem)
    {
        // ignore for spells and mounts, those are learned directly in spell book
        if (product.HardcodedID != HardcodedProducts::PET && product.HardcodedID != HardcodedProducts::MOUNT)
        {
            uint32 noSpaceForCount = 0;
            ItemPosCountVec dest;
            InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, productItem, productCount, &noSpaceForCount);
            if (msg != EQUIP_ERR_OK)
            {
                customError = LANG_BATTLE_PAY_ERROR_BAGS_FULL;
                return Error::PURCHASE_DENIED;
            }
        }
    }

    return Error::OK;
}

PlayerSpecificValues Manager::GetPlayerValues(WorldSession * session, bool getLanguage)
{
    PlayerSpecificValues values;

    // funds
    values.funds = GetPlayerFunds(session) * Misc::COST_PRECISION;
    if (values.funds < 0)
        values.funds = 0;

    // sales active
    values.salesActive = SalesActive(session);

    Player * player = session->GetPlayer();

    if (getLanguage)
    {
        // if ingame, simply read language variable
        if (player)
            values.playerLanguage = player->GetSession()->GetSessionDbcLocale();
        // otherwise read it from database
        else
        {
            if (QueryResult result = LoginDatabase.PQuery("SELECT locale FROM account WHERE id = %u", session->GetAccountId()))
                values.playerLanguage = (LocaleConstant)(result->Fetch())[0].GetUInt32();
        }
    }

    // @ char select screen
    if (!player)
        return values;

    // player class
    values.playerClass = player->getClass();

    // player name
    values.name = player->GetName();

    // max level
    values.maxLevel = player->getLevel() == sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);

    // bonuses
    values.hasBonusCooldown = HasBonusCooldown(session);

    // known spells
    for (PlayerSpellMap::const_iterator itr = player->GetSpellMap().begin(); itr != player->GetSpellMap().end(); ++itr)
    {
        if (itr->second->state == PLAYERSPELL_REMOVED)
            continue;

        if (!itr->second->active || itr->second->disabled)
            continue;

        values.knownSpells.push_back(itr->first);
    }

    // owned battle pet species
    for (auto pet : player->GetSession()->GetBattlePetMgr()->GetPets())
        if (auto specie = pet.second.GetSpecies())
            values.ownedBattlePetSpecies.push_back(specie->ID);

    // owned items
    for (uint8 i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; i++)
        if (Item * pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            if (std::find(values.ownedItems.begin(), values.ownedItems.end(), pItem->GetEntry()) == values.ownedItems.end())
                values.ownedItems.push_back(pItem->GetEntry());
    for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
        if (Bag* pBag = (Bag*)player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            for (uint32 j = 0; j < pBag->GetBagSize(); j++)
                if (Item * pItem = player->GetItemByPos(i, j))
                    if (std::find(values.ownedItems.begin(), values.ownedItems.end(), pItem->GetEntry()) == values.ownedItems.end())
                        values.ownedItems.push_back(pItem->GetEntry());
    for (uint8 i = BANK_SLOT_ITEM_START; i < BANK_SLOT_ITEM_END; i++)
        if (Item * pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            if (std::find(values.ownedItems.begin(), values.ownedItems.end(), pItem->GetEntry()) == values.ownedItems.end())
                values.ownedItems.push_back(pItem->GetEntry());
    for (uint8 i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; i++)
        if (Bag* pBag = (Bag*)player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            if (std::find(values.ownedItems.begin(), values.ownedItems.end(), pBag->GetEntry()) == values.ownedItems.end())
                values.ownedItems.push_back(pBag->GetEntry());
            for (uint32 j = 0; j < pBag->GetBagSize(); j++)
                if (Item * pItem = player->GetItemByPos(i, j))
                    if (std::find(values.ownedItems.begin(), values.ownedItems.end(), pItem->GetEntry()) == values.ownedItems.end())
                        values.ownedItems.push_back(pItem->GetEntry());
        }
    // faction change items
    /*std::vector<uint32> factionChangeItems;
    for (auto itemId : values.ownedItems)
    {
        uint32 itemHorde = 0;
        uint32 itemAlliance = 0;
        if (!PROJECT::Loots::GetFactionSpecificItem(itemId, itemHorde, itemAlliance))
            continue;
        uint32 otherItemId = itemId == itemHorde ? itemAlliance : itemHorde;
        if (std::find(values.ownedItems.begin(), values.ownedItems.end(), otherItemId) == values.ownedItems.end())
            if (std::find(factionChangeItems.begin(), factionChangeItems.end(), otherItemId) == factionChangeItems.end())
                factionChangeItems.push_back(otherItemId);
    }
    for (auto itemId : factionChangeItems)
        values.ownedItems.push_back(itemId);*/

    return values;
}

void Manager::UpdateProductForPlayer(WorldSession * session, Product * product, PlayerSpecificValues * playerSpecificValues)
{
    PlayerSpecificValues playerSpecificValuesLocal;
    if (!playerSpecificValues)
    {
        playerSpecificValuesLocal = sBattlePayMgr->GetPlayerValues(session);
        playerSpecificValues = &playerSpecificValuesLocal;
    }

    Player * player = session->GetPlayer();

    // items
    if (product->ItemID)
    {
        if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(product->ItemID))
        {
            // check if allowed for player's class
            if (player)
            {
                if (itemTemplate->GetAllowableClass() != uint32(-1))
                    if (!((1 << (player->getClass() - 1)) & itemTemplate->GetAllowableClass()))
                        product->SetNotVisibleIngame();

                if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(product->ItemID))
                    if (!proto->IsUsableByLootSpecialization(player, false))
                        product->SetNotVisibleIngame();
            }

            // check if has product
            if (!(product->CustomFlags & ProductFlagsCu::ALLOW_MULTIPLE))
            {
                if (playerSpecificValues->HasItem(product->ItemID))
                    product->SetHasProduct();
                else if (playerSpecificValues->HasSpellFromItem(product->ItemID))
                    product->SetHasProduct();
            }

            // check required skill
            if (!(product->CustomFlags & ProductFlagsCu::IGNORE_REQUIRED_SKILL_CHECK))
                if (itemTemplate->GetRequiredSkill())
                    if (player && !player->HasSkill(itemTemplate->GetRequiredSkill()))
                        product->SetNotBuyableIngame();
        }
    }

    // hardcoded checks for custom product IDs
    switch (product->HardcodedID)
    {
        // Level 90
        case HardcodedProducts::LEVEL_BOOST:
            if (playerSpecificValues->HasMaxLevel())
                product->SetHasProduct();
            break;
        // Gold
        case HardcodedProducts::GOLD:
            if (!player)
                break;
            if (player->GetMoney() + product->Quantity * GOLD > MAX_MONEY_AMOUNT)
                product->SetNotBuyableIngame();
            break;
        // Codex of Xerrath
        case HardcodedProducts::CODEX_OF_XERRATH:
            if (playerSpecificValues->HasSpell(137206))
                product->SetHasProduct();
            if (playerSpecificValues->GetClass() != CLASS_WARLOCK)
                product->SetNotBuyableIngame();
            break;
        // Battle Pets
        case HardcodedProducts::PET:
            if (playerSpecificValues->HasBattlePetSpecies(product->CustomValue))
                product->SetHasProduct();
            break;
        // Battle Pet Level up
        /*case HardcodedProducts::PET_LEVEL_25:
        {
            if (!player)
                break;
            auto * battlePet = player->GetBattlePetMgr()->GetCurrentBattlePet();
            if (!battlePet)
                product->SetNotBuyableIngame();
            else if (battlePet->GetLevel() >= PROJECT::BattlePets::Constants::MAX_PET_LEVEL)
                product->SetHasProduct();
            break;
        }
        // Batle Pet upgrade Epic
        case HardcodedProducts::PET_UPGRADE_EPIC:
        {
            if (!player)
                break;
            auto * battlePet = player->GetBattlePetMgr()->GetCurrentBattlePet();
            if (!battlePet)
                product->SetNotBuyableIngame();
            else if (battlePet->GetQuality() >= ITEM_QUALITY_EPIC)
                product->SetHasProduct();
            break;
        }*/
        // Mounts
        case HardcodedProducts::MOUNT:
            if (playerSpecificValues->HasSpell(product->CustomValue))
                product->SetHasProduct();
            break;
        // Titles
        case HardcodedProducts::TITLE:
            if (!player)
                break;
            if (CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(product->CustomValue))
                if (player->HasTitle(titleInfo))
                    product->SetHasProduct();
            break;
        // Guild Reputation
        /*case HardcodedProducts::GUILD_REPUTATION:
            if (!player)
                break;
            if (!player->GetGuild())
                product->SetNotBuyableIngame();
            else if (player->GetReputation(PROJECT::Constants::Reputations::GUILD) >= ReputationMgr::Reputation_Cap)
                product->SetHasProduct();
            break;*/
        // Character rename
        case HardcodedProducts::CHAR_RENAME:
            if (!player)
                break;
            if (player->HasAtLoginFlag(AT_LOGIN_RENAME))
                product->SetHasProduct();
            break;
        // Character customize
        case HardcodedProducts::CHAR_CUSTOMIZE:
            if (!player)
                break;
            if (player->HasAtLoginFlag(AT_LOGIN_CUSTOMIZE))
                product->SetHasProduct();
            break;
        // Character race change and faction change
        case HardcodedProducts::CHAR_RACE_CHANGE:
        case HardcodedProducts::CHAR_FACTION_CHANGE:
            if (!player)
                break;
            if (player->HasAtLoginFlag(AT_LOGIN_CHANGE_FACTION) || player->HasAtLoginFlag(AT_LOGIN_CHANGE_RACE))
                product->SetHasProduct();
            break;
        // Umute
        case HardcodedProducts::UNMUTE:
            if (!player)
                break;
            if (player->CanSpeak())
                product->SetNotBuyableIngame();
            break;
        // Full ilvl upgrade
        /*case HardcodedProducts::ILVL_UPGRADE_FULL:
        {
            if (!player)
                break;
            bool atLeastOneDonatedItem = false;
            for (EquipmentSlots i = EQUIPMENT_SLOT_HEAD; i < EQUIPMENT_SLOT_TABARD; i = (EquipmentSlots)(int(i) + 1))
            {
                if (Item * item = PROJECT::Utils::Items::GetEquippedItem(player, i))
                {
                    // item can never be upgraded
                    if (!item->GetModifier(ITEM_MODIFIER_UPGRADE_ID))
                        continue;
                    // check if donated
                    if (!item->HasFlag(ITEM_FIELD_FLAGS, PROJECT::Constants::Items::Flags::BOUGHT_FROM_DONATION_SHOP))
                        continue;
                    // check if already upgraded
                    bool itemCanBeUpgraded = false;
                    uint32 currentUpgradeId = item->GetModifier(ITEM_MODIFIER_UPGRADE_ID);
                    for (uint32 i = 0; i < sItemUpgradeStore.GetNumRows(); i++)
                        if (auto currentUpgrade = sItemUpgradeStore.LookupEntry(i))
                            if (currentUpgrade->PrerequisiteID == currentUpgradeId)
                            {
                                itemCanBeUpgraded = true;
                                break;
                            }
                    if (!itemCanBeUpgraded)
                        continue;

                    atLeastOneDonatedItem = true;
                    break;
                }
            }
            if (!atLeastOneDonatedItem)
                product->SetNotBuyableIngame();
            break;
        }*/
        // Professions
        case HardcodedProducts::PROFESSION_SKILL:
            if (!player)
                break;
            if (auto spellInfo = sSpellMgr->GetSpellInfo(product->CustomValue))
            {
                uint32 skillId = spellInfo->GetEffect(EFFECT_1)->MiscValue;
                uint32 maxSkill = spellInfo->GetEffect(EFFECT_1)->BasePoints * 75;
                if (!player->HasSkill(skillId))
                    product->SetNotBuyableIngame();
                else if (player->GetSkillValue(skillId) == maxSkill)
                    product->SetHasProduct();
            }
            break;
        // All glyphs for class
        case HardcodedProducts::ALL_CLASS_GLYPHS:
        {
            if (!player)
                break;
            bool hasAllSpells = true;
            for (auto itemId : cacheGlyphs)
            {
                ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);

                // must be for player's class
                if (itemTemplate->GetSubClass() != playerSpecificValues->GetClass())
                    continue;

                // check if spell exists and if player has it
                if (itemTemplate->Effects.size() < 2)
                    continue;
                int32 spellId = itemTemplate->Effects[1]->SpellID;
                if (spellId <= 0)
                    continue;
                if (player->HasSpell(spellId))
                    continue;
                // ignore inexistent spells
                if (!sSpellMgr->GetSpellInfo(spellId))
                    continue;

                hasAllSpells = false;
                break;
            }
            if (hasAllSpells)
                product->SetHasProduct();
            break;
        }
        // Challenge transmog gear set
        case HardcodedProducts::TRANSMOG_CHALLENGE_SET:
        {
            std::vector<uint32> currentItems;
            ShopEntryList & shopEntries = sBattlePayMgr->GetStoreActualEntries();
            uint32 classMask = 1 << (playerSpecificValues->GetClass() - 1);
            // get all items which have class requirement from Transmog gear group (only Challenge mode items have class requirement)
            for (auto currentShopEntry : shopEntries)
            {
                if (currentShopEntry.GroupID != HardcodedGroups::GROUP_TRANSMOG_GEAR)
                    continue;
                Product * currentProduct = sBattlePayMgr->GetProductByProductID(currentShopEntry.ProductID);
                if (!currentProduct)
                    continue;
                ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(currentProduct->ItemID);
                if (!itemTemplate)
                    continue;

                // ignore items without class requirement
                if (itemTemplate->GetAllowableClass() == (uint32)-1 || !itemTemplate->GetAllowableClass())
                    continue;

                // ignore items with item level different than (Kor'kron Dark Shaman)
                if (itemTemplate->GetBaseItemLevel() != 90)
                    continue;

                // ignore items not for current class
                if (!(classMask & itemTemplate->GetAllowableClass()))
                    continue;

                currentItems.push_back(itemTemplate->GetId());
            }
            bool hasAllItems = true;
            for (auto currentItemId : currentItems)
                if (!playerSpecificValues->HasItem(currentItemId))
                {
                    hasAllItems = false;
                    break;
                }
            if (hasAllItems)
                product->SetHasProduct();
            break;
        }
    }

    // other
    switch (product->HardcodedID)
    {
        // Titles
        case HardcodedProducts::TITLE:
        {
            // show character name in titles
            size_t start_pos = product->DisplayInfo.Name1.find("%s");
            if (start_pos != std::string::npos)
                product->DisplayInfo.Name1.replace(start_pos, std::string("%s").length(), playerSpecificValues->GetName());
            break;
        }
    }

    // hack for "Account Balance"
    switch (product->ID)
    {
        case HardcodedProductIndexes::INFO:
        case HardcodedProductIndexes::SALES:
        case HardcodedProductIndexes::PLEASE_LOGIN:
        {
            product->NormalPrice = playerSpecificValues->funds;
            product->CurrentPrice = playerSpecificValues->funds;
            break;
        }
    }

    // sales
    if (playerSpecificValues->SalesActive())
    {
        product->CurrentPrice = sales.CalculateSales(product);
    }

    // flags
    // remove "buyable" flag if player doesn't have enough funds (makes the item gray)
    if ((uint32)playerSpecificValues->funds < product->CurrentPrice)
        product->Flags &= ~(ProductFlags::BUYABLE_INGAME | ProductFlags::BUYABLE_GLUE_SCREEN);
}

void Manager::UpdateProductListForPlayer(WorldSession * session, ProductList & currentProducts, GroupList & currentGroups, ShopEntryList & currentShopEntries)
{
    // check if shop enabled
    if (!IsStoreEnabled() || !IsStoreAvailable())
    {
        currentProducts.clear();
        currentGroups.clear();
        currentShopEntries.clear();
        return;
    }

    // get specific values for player
    PlayerSpecificValues playerSpecificValues = sBattlePayMgr->GetPlayerValues(session, true);

    // hardcoded products
    // sales
    /*if (SalesActive(session))
    {
        currentGroups.push_back(Group(HardcodedGroups::GROUP_SALES, -999999, PROJECT::Language::GetLanguageString(PROJECT::Language::Strings::BATTLE_PAY_PLEASE_SALES, playerSpecificValues.playerLanguage), 939376, GroupDisplay::GROUP_SPLASH));
        currentProducts.push_back(Product(HardcodedProductIndexes::SALES, 0, 0, 0.0f, ProductFlags::VISIBLE_EVERYWHERE, ChoiceTypes::CHOICE_DEFAULT, DisplayInfoStruct(0, 939375, 0, 0, PROJECT::Language::GetLanguageString(PROJECT::Language::Strings::BATTLE_PAY_PLEASE_SALES, playerSpecificValues.playerLanguage), "", "")));
        currentShopEntries.push_back(ShopEntry(HardcodedProductIndexes::SALES, HardcodedGroups::GROUP_SALES, HardcodedProductIndexes::SALES, 0, SplashBannerText::SPLASH_NEW));
    }
    // account balance info @ ingame (only if sales not already visible)
    else if (ShowAccountBalance())
    {
        currentGroups.push_back(Group(HardcodedGroups::GROUP_INFO, -999998, PROJECT::Language::GetLanguageString(PROJECT::Language::Strings::BATTLE_PAY_ACCOUNT_BALANCE, playerSpecificValues.playerLanguage), 939381, GroupDisplay::GROUP_SPLASH));
        currentProducts.push_back(Product(HardcodedProductIndexes::INFO, 0, 0.0f, 0, ProductFlags::VISIBLE_INGAME, ChoiceTypes::CHOICE_DEFAULT, DisplayInfoStruct(0, 939375, 0, 0, PROJECT::Language::GetLanguageString(PROJECT::Language::Strings::BATTLE_PAY_ACCOUNT_BALANCE, playerSpecificValues.playerLanguage), PROJECT::Language::GetLanguageString(PROJECT::Language::Strings::BATTLE_PAY_ACCOUNT_BALANCE_EXPLAIN, playerSpecificValues.playerLanguage), "")));
        currentShopEntries.push_back(ShopEntry(HardcodedProductIndexes::INFO, HardcodedGroups::GROUP_INFO, HardcodedProductIndexes::INFO, 0, SplashBannerText::SPLASH_FEATURED));
    }
    // login message @ char selection screen
    if (!session->GetPlayer())
    {
        currentProducts.push_back(Product(HardcodedProductIndexes::PLEASE_LOGIN, 0, 0.0f, 0, ProductFlags::VISIBLE_GLUE_SCREEN, ChoiceTypes::CHOICE_DEFAULT, DisplayInfoStruct(0, 939375, 0, 0, PROJECT::Language::GetLanguageString(PROJECT::Language::Strings::BATTLE_PAY_PLEASE_LOGIN, playerSpecificValues.playerLanguage), PROJECT::Language::GetLanguageString(PROJECT::Language::Strings::BATTLE_PAY_PLEASE_LOGIN_EXPLAIN, playerSpecificValues.playerLanguage), "")));
        for (GroupList::iterator it = currentGroups.begin(); it != currentGroups.end(); ++it)
        {
            Group * group = &*it;

            // show it in all groups
            currentShopEntries.push_back(ShopEntry(HardcodedProductIndexes::PLEASE_LOGIN, group->GroupID, HardcodedProductIndexes::PLEASE_LOGIN, 0, SplashBannerText::SPLASH_FEATURED));

            // and make all groups display type splash
            group->DisplayType = GroupDisplay::GROUP_SPLASH;
        }
    }*/

    // update products
    for (ProductList::iterator it = currentProducts.begin(); it != currentProducts.end(); ++it)
    {
        Product * product = &*it;

        UpdateProductForPlayer(session, product, &playerSpecificValues);
    }
}

float Manager::GetPlayerFunds(WorldSession * session)
{
    return 0.0f;
    PreparedStatement* stmt = ShopDatabase.GetPreparedStatement(SHOP_SEL_DONATIONS_POINTS);
    stmt->setInt32(0, session->GetAccountId());
    if (PreparedQueryResult result = ShopDatabase.Query(stmt))
        return float(result->Fetch()[0].GetDouble());

    return 0.0f;
}

void Manager::SpendPlayerFunds(WorldSession * session, Product * product)
{
    return;
    float cost = product->GetCost();
    PreparedStatement* stmt = ShopDatabase.GetPreparedStatement(SHOP_UPD_DONATIONS_POINTS);
    stmt->setFloat(0, cost);
    stmt->setFloat(1, cost);
    stmt->setUInt32(2, session->GetAccountId());
    // block calling thread so remaining points get updated correctly
    ShopDatabase.DirectExecute(stmt);
}

bool SalesStruct::SalesActive(WorldSession * session)
{
    // force for specific users
    if (session)
        if (std::find(salesForAccounts.begin(), salesForAccounts.end(), session->GetAccountId()) != salesForAccounts.end())
            return true;

    // too early
    uint32 currentTime = time(nullptr);
    if (currentTime < start)
        return false;

    // too late
    if (currentTime > start + duration)
        return false;

    return true;
}

uint32 SalesStruct::CalculateSales(Product * product)
{
    return product->CurrentPrice;
}

void Product::InitializePrices(float price)
{
    // round at 1 decimal
    uint32 finalPrice = uint32(price * Misc::COST_PRECISION / 1000) * 1000;
    // and simulate round() (either floor or ceil)
    if ((uint32(price * Misc::COST_PRECISION) / 100) % 10 >= 5)
        finalPrice += 1000;
    NormalPrice = finalPrice;
    CurrentPrice = finalPrice;
}

bool Manager::HasBonusCooldown(WorldSession * session)
{
    Player * player = session->GetPlayer();
    //if (!player)
        return false;

    uint32 lastDonation = 0;
    PreparedStatement* stmt = ShopDatabase.GetPreparedStatement(SHOP_SEL_DONATIONS_COOLDOWN);
    stmt->setUInt32(0, session->GetAccountId());
    stmt->setUInt32(1, player->GetGUID().GetCounter());
    if (PreparedQueryResult result = ShopDatabase.Query(stmt))
        lastDonation = result->Fetch()[0].GetUInt32();

    uint32 timeDiff = time(nullptr) - lastDonation;
    if (lastDonation > time(nullptr) - Misc::BONUS_COOLDOWN)
        return true;

    return false;
}

void Manager::AddBonusCooldown(WorldSession * session, uint32 currentTime)
{
    Player * player = session->GetPlayer();
    //if (!player)
        return;

    if (!currentTime)
        currentTime = time(nullptr);

    PreparedStatement* stmt = ShopDatabase.GetPreparedStatement(SHOP_REP_DONATIONS_BONUS_COOLDOWN);
    stmt->setUInt32(0, session->GetAccountId());
    stmt->setUInt32(1, player->GetGUID().GetCounter());
    stmt->setUInt32(2, currentTime);
    // block calling thread so shop product gets correctly updated with bonus cooldowns
    ShopDatabase.DirectExecute(stmt);
}

void Manager::AddBonus(WorldSession * session, uint32 bonusType, uint32 currentTime)
{
    Player * player = session->GetPlayer();
    //if (!player)
        return;

    if (!currentTime)
        currentTime = time(nullptr);

    PreparedStatement* stmt = ShopDatabase.GetPreparedStatement(SHOP_INS_DONATIONS_BONUS);
    stmt->setUInt32(0, session->GetAccountId());
    stmt->setUInt32(1, player->GetGUID().GetCounter());
    stmt->setUInt32(2, realm.Id.Realm);
    stmt->setUInt32(3, bonusType);
    stmt->setUInt32(4, currentTime);
    ShopDatabase.Execute(stmt);
}

void SchedulePendingAction(uint32 guid, Actions type, uint32 param1, uint32 param2)
{
    CharacterDatabase.PQuery("INSERT INTO project_donations_actions VALUES (0, %u, %u, %u, %u, 0)", guid, type, param1, param2);
}

} // BattlePay
