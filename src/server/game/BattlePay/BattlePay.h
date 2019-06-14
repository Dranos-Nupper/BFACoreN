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

#include <Server/WorldSession.h>
#include <Globals/ObjectMgr.h>
#include "Config.h"
#include "Language.h"

#ifndef BATTLE_PAY_H
#define BATTLE_PAY_H

namespace BattlePay
{
    enum Misc
    {
        COST_PRECISION    = 10000,
        SALES_UPDATE      = 10 * IN_MILLISECONDS,
        BONUS_COOLDOWN    = 86400,
    };
    enum Status
    {
        ENABLED                       = 0,
        AVAILABLE                     = 1,
        DIABLED_BY_PARENTAL_CONTROLS  = 2,
    };

    enum ChoiceTypes
    {
        CHOICE_DEFAULT      = 0,
        CHOICE_FEATURE      = 1,
        CHOICE_PET          = 2,
        CHOICE_MOUNT        = 3,
    };

    enum ProductFlags
    {
        VISIBLE_GLUE_SCREEN  = 0x01,
        BUYABLE_GLUE_SCREEN  = 0x02,
        VISIBLE_INGAME       = 0x04,
        BUYABLE_INGAME       = 0x08,

        // combined
        ACTIVE_INGAME = (VISIBLE_INGAME | BUYABLE_INGAME),
        VISIBLE_EVERYWHERE = (VISIBLE_INGAME | VISIBLE_GLUE_SCREEN),
    };

    enum GroupDisplay
    {
        GROUP_DEFAULT = 0,
        GROUP_SPLASH  = 1,
    };

    enum PurchaseStatus
    {
        WAITING_CONFIRMATION      = 3,
        FINISHED                  = 6,
    };

    enum SplashBannerText
    {
        SPLASH_FEATURED   = 0,
        SPLASH_DISCOUNT   = 1,
        SPLASH_NEW        = 2,
    };

    enum Currency
    {
        DOLLAR              = 1,
        POUND               = 2,
        BATTLE_COIN         = 3,
        EURO                = 4,
        TEST                = 16,
    };

    enum HardcodedProducts
    {
        LEVEL_BOOST                 = 1,
        GOLD                        = 2,
        CODEX_OF_XERRATH            = 3,
        PET                         = 4,
        MOUNT                       = 5,
        TITLE                       = 6,
        GUILD_REPUTATION            = 8,
        CHAR_RENAME                 = 9,
        CHAR_CUSTOMIZE              = 10,
        UNMUTE                      = 11,
        ILVL_UPGRADE_FULL           = 12,
        CHAR_RACE_CHANGE            = 13,
        CHAR_FACTION_CHANGE         = 14,
        PROFESSION_SKILL            = 15,
        ALL_CLASS_GLYPHS            = 16,
        PET_LEVEL_25                = 17,
        PET_UPGRADE_EPIC            = 18,
        TRANSMOG_CHALLENGE_SET      = 19,
    };

    enum HardcodedProductIndexes
    {
        // internal
        SALES                 = 999997,
        PLEASE_LOGIN          = 999998,
        INFO                  = 999999,
    };

    enum HardcodedGroups
    {
        GROUP_TRANSMOG_GEAR     = 10,
        // internal
        GROUP_INFO              = 999,
        GROUP_SALES             = 997,
    };

    enum ProductFlagsCu
    {
        ALLOW_MULTIPLE                    = 0x01, // allows buying items even if player already has them
        SHOW_SPELL_AS_DESCRIPTION         = 0x02, // if no custom description set, shows item spells descriptions (if any) as item description if item doesn't have any default description
        SHOW_ITEM_NAME_DESCRIPTION        = 0x04, // show Heroic / Warforged / Season X, etc
        SHOW_ITEM_LEVEL                   = 0x08, // show item level [xxx]
        SHOW_SPELL_AS_DESCRIPTION_FORCE   = 0x10, // if no custom description set, shows item spells descriptions (if any) as item description even if item has a default description
        IGNORE_REQUIRED_SKILL_CHECK       = 0x20, // don't check RequiredSkill @ item template
    };

    enum BonusType
    {
        BONUS_GROUND_MOUNT                    = 1,
        BONUS_FLY_MOUNT                       = 2,
        BONUS_RACE_FACTION_RENAME_CUSTOMIZE   = 3,
        BONUS_COMPANION                       = 4,
        BONUS_PROFESSION                      = 5,
        BONUS_TITLE                           = 6,
        BONUS_FLY_GUILD_GOLD                  = 7,
        BONUS_LEVEL_85                        = 8,
        BONUS_GLYPHS                          = 9,
        BONUS_ENCHANTS                        = 10,
        BONUS_GEMS                            = 11,
        BONUS_GUILD_RENAME                    = 12
    };

    enum LogType
    {
        LOG_ITEM                         = 1,
        LOG_SET                          = 2,
        LOG_PROFESSION                   = 3,
        LOG_RENAME                       = 4,
        LOG_RACE_CHANGE                  = 5,
        LOG_GEAR_TRANSFER                = 6,
        LOG_LEVEL_90                     = 7,
        LOG_ITEM_CHANGE                  = 8,
        LOG_SPEC_CHANGE                  = 9,
        LOG_UNBAN                        = 10,
        LOG_FULL_CHAR                    = 11,
        LOG_OTHER                        = 12,
        LOG_CUSTOMIZE_CHAR               = 14,
        LOG_TITLE                        = 15,
        LOG_CHAR_TO_NEW_ACCOUNT          = 16,
        LOG_GOLD                         = 17,
        LOG_EXPENSE                      = 18,
        LOG_NO_MORE_BONUSES              = 19,
        LOG_ARENA_RATING                 = 20,
        LOG_UNMUTE                       = 21,
        LOG_DONATION_BIND                = 22,
        LOG_CHAR_EXCHANGE                = 23,
        LOG_GUILD_RENAME                 = 24,
        LOG_REALM_TRANSFER               = 25,
        LOG_SPELL                        = 26,
        LOG_FULL_CHAR_ENCH_GEM_GLYPHS    = 27,
        LOG_GUILD_LEVEL                  = 28,
        LOG_LEVEL_85_DUNGEON_ITEMS       = 29,
        LOG_GUILD_REPUTATION             = 30,
        LOG_FACTION_REPUTATION           = 31,
        LOG_GUILD_TRANSFER               = 32,
        LOG_GUILD_LEVEL_25               = 33,
        LOG_OLD_ITEM_1                   = 34,
        LOG_OLD_ITEMS_5                  = 35,
        LOG_OLD_ITEMS_10                 = 36,
        LOG_ACHIEVEMENT                  = 37,
        LOG_ALL_CLASS_GLYPHS             = 38,
        LOG_PET_RENAME                   = 39,
        LOG_FORUM_REPUTATION             = 40,
        LOG_FORUM_UNBAN                  = 41,
        LOG_FORUM_RENAME                 = 42,
        LOG_CODEX_OF_XERRATH             = 43,
        LOG_CURRENCY                     = 44,
        LOG_FULL_ILVL_UPGRADE            = 45,
        LOG_ILVL_UPGRADE                 = 46,
        LOG_MONEY_TRANSFER_TO            = 47,
        LOG_MONEY_TRANSFER_FROM          = 48,
        LOG_BATTLE_PET_LEVEL             = 49,
        LOG_BATTLE_PET_UPGRADE           = 50,
        LOG_BATTLE_PET                   = 51,
        LOG_ITEM_UPGRADE                 = 52,
        LOG_FREE_UP_NAME                 = 53,
        LOG_CHARGEBACK_INVESTIGATION_FEE = 54,
    };

    enum Error : uint16
    {
        SHOP_ERROR_TRY_AGAIN            = 0,
        PURCHASE_DENIED                 = 1,
        NO_VALID_PAYMENT_METHOD         = 2,
        SHOP_ERROR_TRY_LATER            = 13,
        INSUFFICIENT_BALANCE            = 28,
        BATTLEPAY_DISABLED              = 34,

        // internal
        OK                              = 999,
    };

    enum Actions
    {
        PET_BATTLE_LEVEL             = 1,
        PET_BATTLE_UPGRADE           = 2,
        PET_BATTLE_ADD_NPC           = 3,
        ITEM_DELETE_ONLINE           = 4,
        TITLE_DELETE                 = 5,
        TITLE_ADD                    = 6,
        ACHIEVEMENT_ADD              = 7,
    };
    enum ActionsResult
    {
        RESULT_PENDING               = 0,
        RESULT_DONE                  = 1,
        RESULT_ERROR                 = 2,
    };


    struct Purchase
    {
        Purchase() { }
        Purchase(uint64 purchaseId, uint32 status, uint32 productId) : PurchaseID(purchaseId), Status(status), ProductId(productId) { }
        uint64 PurchaseID;
        uint32 Status;
        uint32 ResultCode = 0;
        uint32 ProductId;
        std::string WalletName;
    };

    struct DisplayInfoExtras
    {
        uint32 DisplayID;
        uint32 Unk2;
        std::string Name;
    };

    struct DisplayInfoStruct
    {
        DisplayInfoStruct(uint32 creatureDisplayInfoID, uint32 fileDataID, uint32 flags, uint32 itemDisplayInfoID, std::string name1, std::string description, std::string name3)
            : CreatureDisplayInfoID(creatureDisplayInfoID), ItemDisplayInfoID(itemDisplayInfoID), FileDataID(fileDataID), Flags(flags), Name1(name1), Description(description), Name3(name3)
        {
            hasDisplayInfo = true;
        }
        DisplayInfoStruct()
        {
            hasDisplayInfo = false;
        }
        bool HasDisplayInfo() { return hasDisplayInfo; }

        bool hasDisplayInfo;
        uint32 CreatureDisplayInfoID;
        uint32 ItemDisplayInfoID;
        uint32 FileDataID;
        uint32 Flags;
        uint32 Flags2;
        uint32 Flags3;
        uint32 Flags4;
        std::string Name1;
        std::string Description; // Name2
        std::string Name3;
        std::string Description2;
        std::vector<DisplayInfoExtras> DisplayInfoExtra;
    };

    struct PlayerSpecificValues
    {
        int32 funds = 0;
        bool maxLevel = false;
        bool salesActive = false;
        bool hasBonusCooldown = false;
        uint32 playerClass = 0;
        LocaleConstant playerLanguage = LOCALE_enUS;
        std::string name = "";
        std::list<uint32> knownSpells;
        std::list<uint32> ownedItems;
        std::list<uint32> ownedBattlePetSpecies;

        bool HasBonusCooldown() { return hasBonusCooldown; }
        bool HasMaxLevel() { return maxLevel; }
        bool SalesActive() { return salesActive; }
        uint32 GetClass() { return playerClass; }
        std::string GetName() { return name; }

        bool HasItem(uint32 itemId)
        {
            return std::find(ownedItems.begin(), ownedItems.end(), itemId) != ownedItems.end();
        }
        bool HasSpell(uint32 spellId)
        {
            return std::find(knownSpells.begin(), knownSpells.end(), spellId) != knownSpells.end();
        }
        bool HasBattlePetSpecies(uint32 speciesId)
        {
            return std::find(ownedBattlePetSpecies.begin(), ownedBattlePetSpecies.end(), speciesId) != ownedBattlePetSpecies.end();
        }
        bool HasSpellFromItem(uint32 itemId)
        {
            if (const ItemTemplate * proto = sObjectMgr->GetItemTemplate(itemId))
                for (uint32 i = 0; i < proto->Effects.size(); ++i)
                    if (proto->Effects[i]->SpellID && HasSpell(proto->Effects[i]->SpellID))
                        return true;

            return false;
        }
    };

    struct Product
    {
        Product(uint32 id, uint32 itemId, uint32 quantity, float price, uint32 flags, uint32 choiceType, DisplayInfoStruct displayInfo, uint32 serverSideHarcodedId = 0, uint32 customItemDeliveryId = 0, uint32 customFlags = 0, int32 customValue = 0, uint32 logType = 0)
            : ID(id), ItemID(itemId), Quantity(quantity), Flags(flags), Type(choiceType), DisplayInfo(displayInfo), HardcodedID(serverSideHarcodedId), CustomItemDeliveryId(customItemDeliveryId), CustomFlags(customFlags), CustomValue(customValue), LogType(logType)
        {
            InitializePrices(price);
        }

        float GetCost() { return float(CurrentPrice) / Misc::COST_PRECISION; }

        bool HasProduct() { return hasProduct; }
        void SetHasProduct() { hasProduct = true; }
        void InitializePrices(float price);

        void SetNotVisibleIngame() { Flags &= ~ProductFlags::VISIBLE_INGAME; }
        void SetNotBuyableIngame() { Flags &= ~ProductFlags::BUYABLE_INGAME; }
        bool IsBuyableIngame() { return !!(Flags & ProductFlags::BUYABLE_INGAME); }
        bool IsVisibleIngame() { return !!(Flags & ProductFlags::VISIBLE_INGAME); }

        uint32 ID;
        uint32 NormalPrice;
        uint32 CurrentPrice;
        uint32 ItemID;
        uint32 Quantity;
        uint8 Type = 0;
        uint32 Flags;
        uint8 PetResult = 0;
        DisplayInfoStruct DisplayInfo;

        // internal
        bool hasProduct = false;
        uint32 HardcodedID;
        uint32 CustomItemDeliveryId;
        uint32 CustomFlags;
        int32 CustomValue;
        uint32 LogType;
    };


    struct Group
    {
        Group(uint32 id, int32 ordering, std::string name, uint32 iconFileDataID, uint8 displayType)
            : GroupID(id), Ordering(ordering), Name(name), IconFileDataID(iconFileDataID), DisplayType(displayType) { }

        uint32 GroupID;
        int32 Ordering;
        int32 UnkBfa = 0;
        std::string Name;
        std::string Description ="";
        uint32 IconFileDataID;
        uint8 DisplayType;
    };

    struct ShopEntry
    {
        ShopEntry(uint32 id, uint32 groupId, uint32 productId, int32 ordering, uint8 banner, uint32 flags, DisplayInfoStruct displayInfo)
            : EntryID(id), Ordering(ordering), GroupID(groupId), ProductID(productId), Flags(flags), BannerType(banner), DisplayInfo(displayInfo) { }
        ShopEntry(uint32 id, uint32 groupId, uint32 productId, int32 ordering = 0, uint8 banner = 0, uint32 flags = 0)
            : EntryID(id), Ordering(ordering), GroupID(groupId), ProductID(productId), Flags(flags), BannerType(banner) { }

        uint32 EntryID;
        int32 Ordering;
        uint32 GroupID;
        uint32 ProductID;
        uint32 Flags;
        uint8 BannerType;
        DisplayInfoStruct DisplayInfo;
    };

    struct SalesStruct
    {
        SalesStruct()
        {
            start = 0;
            duration = 0;
        }

        bool SalesActive(WorldSession * session = NULL);
        uint32 CalculateSales(Product * product);

        uint32 start;
        uint32 duration;
        std::vector<uint32> salesForAccounts;
    };

    typedef std::list<Product> ProductList;
    typedef std::list<Group> GroupList;
    typedef std::list<ShopEntry> ShopEntryList;
    typedef std::list<Purchase*> PurchaseList;

    class Manager
    {
        public:
            static Manager* instance();

            Manager();

            // loaders
            void LoadFromDB();
            void CacheData();

            // misc

            // store status
            bool IsStoreEnabled() { return sWorld->getBoolConfig(CONFIG_BATTLEPAY_STORE_ENABLED); }
            bool IsStoreAvailable() { return sWorld->getBoolConfig(CONFIG_BATTLEPAY_STORE_AVAILABLE); }
            bool ShowAccountBalance() { return sWorld->getBoolConfig(CONFIG_BATTLEPAY_SHOW_ACCOUNT_BALANCE); }

            // purchases
            void AddPendingPurchase(Purchase * purchase);
            uint64 GeneratePurchaseID();
            Purchase * GetPurchaseByPurchaseID(uint64 purchaseId);
            void DeletePurchase(uint64 purchaseId);
            void DeletePurchase(Purchase * purchase);
            uint32 FinalizePurchase(WorldSession * session, Purchase * purchase);
            Error IsValidPurchase(WorldSession * session, Purchase * purchase, TrinityStrings& customError);

            // products
            Product * GetProductByProductID(uint32 productId);
            bool SalesActive(WorldSession * session) { return sales.SalesActive(session); }
            uint32 CalculateSales(Product * product) { return sales.CalculateSales(product); }

            // bonuses
            bool HasBonusCooldown(WorldSession * session);
            void AddBonusCooldown(WorldSession * session, uint32 currentTime = 0);
            void AddBonus(WorldSession * session, uint32 bonusType, uint32 currentTime = 0);

            // data list getters
            ProductList GetStoreProducts() { return products; }
            GroupList GetStoreGroups() { return groups; }
            ShopEntryList GetStoreEntries() { return shopEntries; }
            // actual lists, not copies
            ProductList & GetStoreActualProducts() { return products; }
            GroupList & GetStoreActualGroups() { return groups; }
            ShopEntryList & GetStoreActualEntries() { return shopEntries; }

            // player handlers
            void UpdateProductListForPlayer(WorldSession * session, ProductList & products, GroupList & groups, ShopEntryList & shopEntries);
            void UpdateProductForPlayer(WorldSession * session, Product * product, PlayerSpecificValues * playerSpecificValues = NULL);
            PlayerSpecificValues GetPlayerValues(WorldSession * session, bool getLanguage = false);
            float GetPlayerFunds(WorldSession * session);
            void SpendPlayerFunds(WorldSession * session, Product * product);

        private:
            ProductList products;
            GroupList groups;
            ShopEntryList shopEntries;
    
            uint64 lastPurchaseId;
            PurchaseList activePurchases;

            // sales
            SalesStruct sales;

            // caches
            std::vector<uint32> cacheGlyphs;
    };

    TC_GAME_API void SchedulePendingAction(uint32 guid, Actions type, uint32 param1 = 0, uint32 param2 = 0);

    #define sBattlePayMgr BattlePay::Manager::instance()
}

#endif
