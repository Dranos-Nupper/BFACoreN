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

#include "DB2DatabaseLoader.h"
#include "Common.h"
#include "DatabaseEnv.h"
#include "DB2Meta.h"
#include "Errors.h"
#include "Log.h"

DB2LoadInfo::DB2LoadInfo() : DB2FileLoadInfo(), Statement(MAX_HOTFIXDATABASE_STATEMENTS)
{
}

DB2LoadInfo::DB2LoadInfo(DB2FieldMeta const* fields, std::size_t fieldCount, DB2Meta const* meta, HotfixDatabaseStatements statement)
    : DB2FileLoadInfo(fields, fieldCount, meta), Statement(statement)
{
}

static char const* nullStr = "";
char* DB2DatabaseLoader::LoadW(uint32& records, char**& indexTable, uint32 type, uint32& EndEntry, char*& stringHolders, std::vector<char*>& stringPool)
{
    QueryResult result;
    switch (type)
    {
    case 1://sItemSparseStore
        result = WorldDatabase.Query("SELECT ID, AllowableRace, Name, '', '', '', Description, Flags1, Flags2, Flags3, Flags4, PriceRandomValue, PriceVariance, BuyCount, BuyPrice, SellPrice, RequiredSpell, MaxCount, Stackable, ItemStatAllocation1, ItemStatAllocation2, ItemStatAllocation3, ItemStatAllocation4, ItemStatAllocation5, ItemStatAllocation6, ItemStatAllocation7, ItemStatAllocation8, ItemStatAllocation9, ItemStatAllocation10, ItemStatSocketCostMultiplier1, ItemStatSocketCostMultiplier2, ItemStatSocketCostMultiplier3, ItemStatSocketCostMultiplier4, ItemStatSocketCostMultiplier5, ItemStatSocketCostMultiplier6, ItemStatSocketCostMultiplier7, ItemStatSocketCostMultiplier8, ItemStatSocketCostMultiplier9, ItemStatSocketCostMultiplier10, ItemRange, BagFamily, QualityModifier, Duration, DmgVariance, AllowableClass, ItemLevel, RequiredSkill, RequiredSkillRank, RequiredReputationFaction, ItemStatValue1, ItemStatValue2, ItemStatValue3, ItemStatValue4, ItemStatValue5, ItemStatValue6, ItemStatValue7, ItemStatValue8, ItemStatValue9, ItemStatValue10, ScalingStatDistribution, ItemDelay, PageID, StartQuestID, LockID, RandomProperty, RandomSuffix, ItemSet, Area, `Map`, TotemCategory, SocketBonus, GemProperties, LimitCategory, RequiredHoliday, RequiredTransmogHoliday, ItemNameDescriptionID, Quality, InventoryType, RequiredLevel, RequiredPVPRank, RequiredPVPMedal, RequiredReputationRank, ContainerSlots, ItemStatType1, ItemStatType2, ItemStatType3, ItemStatType4, ItemStatType5, ItemStatType6, ItemStatType7, ItemStatType8, ItemStatType9, ItemStatType10, DamageType, Bonding, LanguageID, PageMaterialID, Material, SheatheType, SocketType1, SocketType2, SocketType3, SpellWeightCategory, SpellWeight, ArtifactID, ExpansionID FROM item_template ORDER BY ID DESC");
        break;
    case 2://sItemStore
        result = WorldDatabase.Query("SELECT ID, IconFileDataID, ClassID, SubclassID, SoundOverrideSubclass, Material, InventoryType, SheatheType, GroupSoundsID FROM item_template ORDER BY ID DESC");
        break;
    case 3://sItemEffectStore
        result = WorldDatabase.Query("SELECT 0 as ID, SpellID_1, Cooldown_1, CategoryCooldown_1, Charges_1, Category_1, ChrSpecializationID_1, 0 as OrderIndex, Trigger_1, ID as ItemID FROM item_template where SpellID_1 > 0 UNION ALL "
            "SELECT 0, SpellID_2, Cooldown_2, CategoryCooldown_2, Charges_2, Category_2, ChrSpecializationID_2, 1, Trigger_2, ID FROM item_template where SpellID_2 > 0 UNION ALL "
            "SELECT 0, SpellID_3, Cooldown_3, CategoryCooldown_3, Charges_3, Category_3, ChrSpecializationID_3, 2, Trigger_3, ID FROM item_template where SpellID_3 > 0 UNION ALL "
            "SELECT 0, SpellID_4, Cooldown_4, CategoryCooldown_4, Charges_4, Category_4, ChrSpecializationID_4, 3, Trigger_4, ID FROM item_template where SpellID_4 > 0 UNION ALL "
            "SELECT 0, SpellID_5, Cooldown_5, CategoryCooldown_5, Charges_5, Category_5, ChrSpecializationID_5, 4, Trigger_5, ID FROM item_template where SpellID_5 > 0");
        break;
    case 4://sItemModifiedAppearanceStore
        result = WorldDatabase.Query("SELECT ID, 0, 0, AppearanceID, 0, TransmogSourceTypeEnum FROM item_template where AppearanceID <> 0");
        break;
    }
    if (!result)
        return nullptr;

    if (_loadInfo->Meta->GetDbFieldCount() != result->GetFieldCount())
        return nullptr;

    // get struct size and index pos
    uint32 indexField = _loadInfo->Meta->GetDbIndexField();
    uint32 recordSize = _loadInfo->Meta->GetRecordSize();

    // we store flat holders pool as single memory block
    std::size_t stringFields = _loadInfo->GetStringFieldCount(false);
    std::size_t localizedStringFields = _loadInfo->GetStringFieldCount(true);

    // each string field at load have array of string for each locale
    std::size_t stringHoldersRecordPoolSize = localizedStringFields * sizeof(LocalizedString) + (stringFields - localizedStringFields) * sizeof(char*);

    if (stringFields)
    {
        std::size_t stringHoldersPoolSize = stringHoldersRecordPoolSize * result->GetRowCount();
        stringHolders = new char[stringHoldersPoolSize];

        // DB2 strings expected to have at least empty string
        for (std::size_t i = 0; i < stringHoldersPoolSize / sizeof(char*); ++i)
            ((char const**)stringHolders)[i] = nullStr;
    }
    else
        stringHolders = nullptr;

    // Resize index table
    // database query *MUST* contain ORDER BY `index_field` DESC clause
    uint32 indexTableSize = (*result)[indexField].GetUInt32() + 1;
    if (type > 2)
        indexTableSize = records + result->GetRowCount();

    if (indexTableSize < records)
        indexTableSize = records;

    if (indexTableSize > records)
    {
        char** tmpIdxTable = new char*[indexTableSize];
        memset(tmpIdxTable, 0, indexTableSize * sizeof(char*));
        memcpy(tmpIdxTable, indexTable, records * sizeof(char*));
        delete[] indexTable;
        indexTable = tmpIdxTable;
    }

    char* tempDataTable = new char[result->GetRowCount() * recordSize];
    uint32* newIndexes = new uint32[result->GetRowCount()];
    memset(tempDataTable, 0, result->GetRowCount() * recordSize);
    memset(newIndexes, 0, result->GetRowCount() * sizeof(uint32));
    uint32 rec = 0;
    uint32 newRecords = 0;

    do
    {
        Field* fields = result->Fetch();
        uint32 offset = 0;
        uint32 stringFieldOffset = 0;

        uint32 indexValue = fields[indexField].GetUInt32();
        if (type > 2)
            indexValue = records + rec;

        // Attempt to overwrite existing data
        char* dataValue = indexTable[indexValue];
        if (!dataValue)
        {
            newIndexes[newRecords] = indexValue;
            dataValue = &tempDataTable[newRecords++ * recordSize];
        }

        uint32 f = 0;
        if (!_loadInfo->Meta->HasIndexFieldInData())
        {
            *((uint32*)(&dataValue[offset])) = indexValue;
            offset += 4;
            ++f;
        }

        for (uint32 x = 0; x < _loadInfo->Meta->FieldCount; ++x)
        {
            for (uint32 z = 0; z < _loadInfo->Meta->Fields[x].ArraySize; ++z)
            {
                switch (_loadInfo->TypesString[f])
                {
                case FT_FLOAT:
                    *((float*)(&dataValue[offset])) = fields[f].GetFloat();
                    offset += 4;
                    break;
                case FT_INT:
                    *((int32*)(&dataValue[offset])) = fields[f].GetInt32();
                    if (type > 2 && indexField == f)
                        *((int32*)(&dataValue[offset])) = indexValue;
                    offset += 4;
                    break;
                case FT_BYTE:
                    *((int8*)(&dataValue[offset])) = fields[f].GetInt8();
                    offset += 1;
                    break;
                case FT_SHORT:
                    *((int16*)(&dataValue[offset])) = fields[f].GetInt16();
                    offset += 2;
                    break;
                case FT_LONG:
                    *((int64*)(&dataValue[offset])) = fields[f].GetInt64();
                    offset += 8;
                    break;
                case FT_STRING:
                {
                    LocalizedString** slot = (LocalizedString**)(&dataValue[offset]);
                    *slot = (LocalizedString*)(&stringHolders[stringHoldersRecordPoolSize * rec + stringFieldOffset]);
                    ASSERT(*slot);

                    // Value in database in main table field must be for enUS locale
                    if (char* str = AddString(&(*slot)->Str[LOCALE_enUS], fields[f].GetString()))
                        stringPool.push_back(str);

                    stringFieldOffset += sizeof(LocalizedString);
                    offset += sizeof(char*);
                    break;
                }
                case FT_STRING_NOT_LOCALIZED:
                {
                    char const** slot = (char const**)(&dataValue[offset]);
                    *slot = (char*)(&stringHolders[stringHoldersRecordPoolSize * rec + stringFieldOffset]);
                    ASSERT(*slot);

                    // Value in database in main table field must be for enUS locale
                    if (char* str = AddString(slot, fields[f].GetString()))
                        stringPool.push_back(str);

                    stringFieldOffset += sizeof(char*);
                    offset += sizeof(char*);
                    break;
                }
                default:
                    ASSERT(false, "Unknown format character '%c' found in %s meta for field %s",
                        _loadInfo->TypesString[f], _storageName.c_str(), _loadInfo->Fields[f].Name);
                    break;
                }
                ++f;
            }
        }

        ASSERT(offset == recordSize);
        ++rec;
    } while (result->NextRow());

    if (!newRecords)
    {
        delete[] tempDataTable;
        delete[] newIndexes;
        return nullptr;
    }

    // Compact new data table to only contain new records not previously loaded from file
    char* dataTable = new char[newRecords * recordSize];
    memcpy(dataTable, tempDataTable, newRecords * recordSize);

    // insert new records to index table
    for (uint32 i = 0; i < newRecords; ++i)
        indexTable[newIndexes[i]] = &dataTable[i * recordSize];

    delete[] tempDataTable;
    delete[] newIndexes;

    records = indexTableSize;
    EndEntry = indexTableSize;

    return dataTable;
}

char* DB2DatabaseLoader::Load(uint32& records, char**& indexTable, char*& stringHolders, std::vector<char*>& stringPool)
{
    // Even though this query is executed only once, prepared statement is used to send data from mysql server in binary format
    PreparedQueryResult result = HotfixDatabase.Query(HotfixDatabase.GetPreparedStatement(_loadInfo->Statement));
    if (!result)
        return nullptr;

    if (_loadInfo->Meta->GetDbFieldCount() != result->GetFieldCount())
        return nullptr;

    // get struct size and index pos
    uint32 indexField = _loadInfo->Meta->GetDbIndexField();
    uint32 recordSize = _loadInfo->Meta->GetRecordSize();

    // we store flat holders pool as single memory block
    std::size_t stringFields = _loadInfo->GetStringFieldCount(false);
    std::size_t localizedStringFields = _loadInfo->GetStringFieldCount(true);

    // each string field at load have array of string for each locale
    std::size_t stringHoldersRecordPoolSize = localizedStringFields * sizeof(LocalizedString) + (stringFields - localizedStringFields) * sizeof(char*);

    if (stringFields)
    {
        std::size_t stringHoldersPoolSize = stringHoldersRecordPoolSize * result->GetRowCount();
        stringHolders = new char[stringHoldersPoolSize];

        // DB2 strings expected to have at least empty string
        for (std::size_t i = 0; i < stringHoldersPoolSize / sizeof(char*); ++i)
            ((char const**)stringHolders)[i] = nullStr;
    }
    else
        stringHolders = nullptr;

    // Resize index table
    // database query *MUST* contain ORDER BY `index_field` DESC clause
    uint32 indexTableSize = (*result)[indexField].GetUInt32() + 1;
    if (indexTableSize < records)
        indexTableSize = records;

    if (indexTableSize > records)
    {
        char** tmpIdxTable = new char*[indexTableSize];
        memset(tmpIdxTable, 0, indexTableSize * sizeof(char*));
        memcpy(tmpIdxTable, indexTable, records * sizeof(char*));
        delete[] indexTable;
        indexTable = tmpIdxTable;
    }

    char* tempDataTable = new char[result->GetRowCount() * recordSize];
    uint32* newIndexes = new uint32[result->GetRowCount()];
    uint32 rec = 0;
    uint32 newRecords = 0;

    do
    {
        Field* fields = result->Fetch();
        uint32 offset = 0;
        uint32 stringFieldOffset = 0;

        uint32 indexValue = fields[indexField].GetUInt32();

        // Attempt to overwrite existing data
        char* dataValue = indexTable[indexValue];
        if (!dataValue)
        {
            newIndexes[newRecords] = indexValue;
            dataValue = &tempDataTable[newRecords++ * recordSize];
        }

        uint32 f = 0;
        if (!_loadInfo->Meta->HasIndexFieldInData())
        {
            *((uint32*)(&dataValue[offset])) = indexValue;
            offset += 4;
            ++f;
        }

        for (uint32 x = 0; x < _loadInfo->Meta->FieldCount; ++x)
        {
            for (uint32 z = 0; z < _loadInfo->Meta->Fields[x].ArraySize; ++z)
            {
                switch (_loadInfo->TypesString[f])
                {
                    case FT_FLOAT:
                        *((float*)(&dataValue[offset])) = fields[f].GetFloat();
                        offset += 4;
                        break;
                    case FT_INT:
                        *((int32*)(&dataValue[offset])) = fields[f].GetInt32();
                        offset += 4;
                        break;
                    case FT_BYTE:
                        *((int8*)(&dataValue[offset])) = fields[f].GetInt8();
                        offset += 1;
                        break;
                    case FT_SHORT:
                        *((int16*)(&dataValue[offset])) = fields[f].GetInt16();
                        offset += 2;
                        break;
                    case FT_LONG:
                        *((int64*)(&dataValue[offset])) = fields[f].GetInt64();
                        offset += 8;
                        break;
                    case FT_STRING:
                    {
                        LocalizedString** slot = (LocalizedString**)(&dataValue[offset]);
                        *slot = (LocalizedString*)(&stringHolders[stringHoldersRecordPoolSize * rec + stringFieldOffset]);
                        ASSERT(*slot);

                        // Value in database in main table field must be for enUS locale
                        if (char* str = AddString(&(*slot)->Str[LOCALE_enUS], fields[f].GetString()))
                            stringPool.push_back(str);

                        stringFieldOffset += sizeof(LocalizedString);
                        offset += sizeof(char*);
                        break;
                    }
                    case FT_STRING_NOT_LOCALIZED:
                    {
                        char const** slot = (char const**)(&dataValue[offset]);
                        *slot = (char*)(&stringHolders[stringHoldersRecordPoolSize * rec + stringFieldOffset]);
                        ASSERT(*slot);

                        // Value in database in main table field must be for enUS locale
                        if (char* str = AddString(slot, fields[f].GetString()))
                            stringPool.push_back(str);

                        stringFieldOffset += sizeof(char*);
                        offset += sizeof(char*);
                        break;
                    }
                    default:
                        ASSERT(false, "Unknown format character '%c' found in %s meta for field %s",
                            _loadInfo->TypesString[f], _storageName.c_str(), _loadInfo->Fields[f].Name);
                        break;
                }
                ++f;
            }
        }

        ASSERT(offset == recordSize);
        ++rec;
    } while (result->NextRow());

    if (!newRecords)
    {
        delete[] tempDataTable;
        delete[] newIndexes;
        return nullptr;
    }

    // Compact new data table to only contain new records not previously loaded from file
    char* dataTable = new char[newRecords * recordSize];
    memcpy(dataTable, tempDataTable, newRecords * recordSize);

    // insert new records to index table
    for (uint32 i = 0; i < newRecords; ++i)
        indexTable[newIndexes[i]] = &dataTable[i * recordSize];

    delete[] tempDataTable;
    delete[] newIndexes;

    records = indexTableSize;

    return dataTable;
}

void DB2DatabaseLoader::LoadStrings(uint32 locale, uint32 records, char** indexTable, std::vector<char*>& stringPool)
{
    PreparedStatement* stmt = HotfixDatabase.GetPreparedStatement(HotfixDatabaseStatements(_loadInfo->Statement + 1));
    stmt->setString(0, localeNames[locale]);
    PreparedQueryResult result = HotfixDatabase.Query(stmt);
    if (!result)
        return;

    std::size_t stringFields = _loadInfo->GetStringFieldCount(true);
    if (result->GetFieldCount() != stringFields + 1 /*ID*/)
        return;

    uint32 fieldCount = _loadInfo->Meta->FieldCount;
    uint32 recordSize = _loadInfo->Meta->GetRecordSize();

    do
    {
        Field* fields = result->Fetch();
        uint32 offset = 0;
        uint32 stringFieldNumInRecord = 0;
        uint32 indexValue = fields[0].GetUInt32();

        if (indexValue >= records)
            continue;

        // Attempt to overwrite existing data
        if (char* dataValue = indexTable[indexValue])
        {
            uint32 fieldIndex = 0;
            if (!_loadInfo->Meta->HasIndexFieldInData())
            {
                offset += 4;
                ++fieldIndex;
            }

            for (uint32 x = 0; x < fieldCount; ++x)
            {
                for (uint32 z = 0; z < _loadInfo->Meta->Fields[x].ArraySize; ++z)
                {
                    switch (_loadInfo->TypesString[fieldIndex])
                    {
                        case FT_FLOAT:
                        case FT_INT:
                            offset += 4;
                            break;
                        case FT_BYTE:
                            offset += 1;
                            break;
                        case FT_SHORT:
                            offset += 2;
                            break;
                        case FT_LONG:
                            offset += 8;
                            break;
                        case FT_STRING:
                        {
                            // fill only not filled entries
                            LocalizedString* db2str = *(LocalizedString**)(&dataValue[offset]);
                            if (db2str->Str[locale] == nullStr)
                                if (char* str = AddString(&db2str->Str[locale], fields[1 + stringFieldNumInRecord].GetString()))
                                    stringPool.push_back(str);

                            ++stringFieldNumInRecord;
                            offset += sizeof(LocalizedString*);
                            break;
                        }
                        case FT_STRING_NOT_LOCALIZED:
                            offset += sizeof(char*);
                            break;
                        default:
                            ASSERT(false, "Unknown format character '%c' found in %s meta for field %s",
                                _loadInfo->TypesString[fieldIndex], _storageName.c_str(), _loadInfo->Fields[fieldIndex].Name);
                            break;
                    }
                    ++fieldIndex;
                }
            }

            ASSERT(offset == recordSize);
        }
        else
            TC_LOG_ERROR("sql.sql", "Hotfix locale table for storage %s references row that does not exist %u locale %s!", _storageName.c_str(), indexValue, localeNames[locale]);

    } while (result->NextRow());

    return;
}

char* DB2DatabaseLoader::AddString(char const** holder, std::string const& value)
{
    if (!value.empty())
    {
        std::size_t existingLength = strlen(*holder);
        if (existingLength >= value.length())
        {
            // Reuse existing storage if there is enough space
            char* str = const_cast<char*>(*holder);
            memcpy(str, value.c_str(), value.length());
            str[value.length()] = '\0';
            return nullptr;
        }

        char* str = new char[value.length() + 1];
        memcpy(str, value.c_str(), value.length());
        str[value.length()] = '\0';
        *holder = str;
        return str;
    }

    return nullptr;
}
