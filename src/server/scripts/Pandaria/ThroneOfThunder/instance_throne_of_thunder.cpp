#include "throne_of_thunder.h"
#include "GameObject.h"
#include "MoveSplineInit.h"
#include "GameObjectAI.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"

DoorData const doorData[] =
{
    {GO_JIN_ROKH_FRONT_DOOR,    DATA_JIN_ROKH_BREAKER,      DOOR_TYPE_ROOM        },
    {GO_JIN_ROKH_BACK_DOOR,     DATA_JIN_ROKH_BREAKER,      DOOR_TYPE_PASSAGE     },
    {GO_HORRIDON_FRONT_DOOR,    DATA_HORRIDON,              DOOR_TYPE_ROOM        },
    {GO_HORRIDON_BACK_DOOR,     DATA_HORRIDON,              DOOR_TYPE_PASSAGE     },
    {GO_ZANDALARI_COUNCIL_LEFT, DATA_COUNCIL_OF_ELDERS,     DOOR_TYPE_ROOM        },
    {GO_ZANDALARI_COUNCIL_RIGHT,DATA_COUNCIL_OF_ELDERS,     DOOR_TYPE_ROOM        },
    {GO_ZANDALARI_COUNCIL_EXIT, DATA_COUNCIL_OF_ELDERS,     DOOR_TYPE_PASSAGE     },
    {GO_TORTOS_EXIT,            DATA_TORTOS,                DOOR_TYPE_PASSAGE     },
    {GO_MEGAERA_EXIT,           DATA_MEGAERA,               DOOR_TYPE_PASSAGE     },
    {GO_JI_KUN_EXIT_DOOR,       DATA_JI_KUN,                DOOR_TYPE_PASSAGE     },
    {GO_PRIMORDIUS_ENTRY_GATE,  DATA_PRIMORDIUS,            DOOR_TYPE_ROOM        },
    {GO_PRIMORDIUS_EXIT_GATE,   DATA_PRIMORDIUS,            DOOR_TYPE_PASSAGE     },
    {GO_SEWER_GATE,             DATA_IRON_QON,              DOOR_TYPE_ROOM        },
    {GO_WIND_WALL,              DATA_IRON_QON,              DOOR_TYPE_ROOM        },
    {GO_DOOR_TO_THE_QUEENS_CHAMBER_1, DATA_IRON_QON,        DOOR_TYPE_PASSAGE     },
    {GO_DOOR_TO_THE_QUEENS_CHAMBER_2, DATA_IRON_QON,        DOOR_TYPE_PASSAGE     },
    {GO_CHAMBER_OF_THE_TWIN_CONSORTS, DATA_TWIN_CONSORTS,   DOOR_TYPE_ROOM        },
    {GO_TWIN_CONSORTS_PASSAGE,  DATA_TWIN_CONSORTS,         DOOR_TYPE_PASSAGE     },
    {GO_RA_DEN_ENTRANCE,        DATA_LEI_SHEN,              DOOR_TYPE_PASSAGE     },
    {GO_RA_DEN_EXIT,            DATA_RA_DEN,                DOOR_TYPE_ROOM        },
    {0,                         0,                          DOOR_TYPE_ROOM        }, // END
};


struct instance_throne_of_thunder : public InstanceScript
{
    instance_throne_of_thunder(InstanceMap* map) : InstanceScript(map)
    {
        Initialize();
    }

    void Initialize()
    {
        SetBossNumber(MAX_ENCOUNTERS);
        LoadDoorData(doorData);

        // creatures
        jinrokhBreakerGUID = ObjectGuid::Empty;
        horridonGUID = ObjectGuid::Empty;
        kazrajinGUID = ObjectGuid::Empty;
        sulTheSandCrawlerGUID = ObjectGuid::Empty;
        frostKingMalakkGUID = ObjectGuid::Empty;
        highPriestessMarliGUID = ObjectGuid::Empty;
        garazhalTheSpiritBinderGUID = ObjectGuid::Empty;
        tortosGUID = ObjectGuid::Empty;
        megaeraGUID = ObjectGuid::Empty;
        jiKunGUID = ObjectGuid::Empty;
        durumuTheForgottenGUID = ObjectGuid::Empty;
        primordiusGUID = ObjectGuid::Empty;
        darkAnimusGUID = ObjectGuid::Empty;
        ironQonGUID = ObjectGuid::Empty;
        roshakGUID = ObjectGuid::Empty;
        quetzalGUID = ObjectGuid::Empty;
        damrenGUID = ObjectGuid::Empty;
        luLinGUID = ObjectGuid::Empty;
        suenGUID = ObjectGuid::Empty;
        leiShenGUID = ObjectGuid::Empty;
        raDenGUID = ObjectGuid::Empty;

        // gameObjects
        firstDoorguid = ObjectGuid::Empty;
        moguFountainNEguid = ObjectGuid::Empty;
        moguFountainNWguid = ObjectGuid::Empty;
        moguFountainSEguid = ObjectGuid::Empty;
        moguFountainSWguid = ObjectGuid::Empty;
        lightningSpanGuid = ObjectGuid::Empty;
        memset(megaeraChestGuids, 0, sizeof(megaeraChestGuids));
        durumuPlatform1 = ObjectGuid::Empty;
        durumuPlatform2 = ObjectGuid::Empty;
        chargingStationGUID = ObjectGuid::Empty;
        southPillarGUID = ObjectGuid::Empty;
        eastPillarGUID = ObjectGuid::Empty;
        westPillarGUID = ObjectGuid::Empty;
        northPillarGUID = ObjectGuid::Empty;
        floorSouthGUID = ObjectGuid::Empty;
        floorEastGUID = ObjectGuid::Empty;
        floorWestGUID = ObjectGuid::Empty;
        floorNorthGUID = ObjectGuid::Empty;
        windowNorthWestGUID = ObjectGuid::Empty;
        windowSouthWestGUID = ObjectGuid::Empty;
        windowNorthEastGUID = ObjectGuid::Empty;
        windowSouthEastGUID = ObjectGuid::Empty;
        memset(cacheOfStormsGUIDs, 0, sizeof(cacheOfStormsGUIDs));

        horridonIntro = NOT_STARTED;
        craziedStormCallerEvent = NOT_STARTED;
        lightningSpanEvent = NOT_STARTED;

        for (uint32 i = 0; i < MAX_ENCOUNTERS; ++i)
            SetBossState(i, NOT_STARTED);

        jiKunFallCatcherTimer = 1000;

        radenCounts = 0;
    }

    void OnPlayerEnter(Player* who)
    {
        if (GetBossState(DATA_DARK_ANIMUS) == DONE)
        {
            who->NearTeleportTo(nearIronQonPos.GetPositionX(), nearIronQonPos.GetPositionY(), nearIronQonPos.GetPositionZ(), nearIronQonPos.GetOrientation());
            return;
        }

        if (GetBossState(DATA_JI_KUN) == DONE)
        {
            who->NearTeleportTo(jikunExitPos.GetPositionX(), jikunExitPos.GetPositionY(), jikunExitPos.GetPositionZ(), jikunExitPos.GetOrientation());
            return;
        }

        if (GetData(DATA_LIGHTNING_SPAN_EVENT) == DONE)
        {
            who->NearTeleportTo(tortosLairPos.GetPositionX(), tortosLairPos.GetPositionY(), tortosLairPos.GetPositionZ(), tortosLairPos.GetOrientation());
            return;
        }

        SendRadenTries(who);
    }

    bool IsEncounterInProgress() const
    {
        for (uint32 i = 0; i < MAX_ENCOUNTERS; ++i)
            if (GetBossState(i) == IN_PROGRESS)
                return true;

        return false;
    }

    void OnCreatureCreate(Creature* creature)
    {
        switch (creature->GetEntry())
        {
        case NPC_JIN_ROKH_BREAKER:
            jinrokhBreakerGUID = creature->GetGUID();
            break;
        case NPC_HORRIDON:
            horridonGUID = creature->GetGUID();
            break;
        case NPC_KAZRAJIN:
            kazrajinGUID = creature->GetGUID();
            break;
        case NPC_SUL_THE_SANDCRAWLER:
            sulTheSandCrawlerGUID = creature->GetGUID();
            break;
        case NPC_FROST_KING_MALAKK:
            frostKingMalakkGUID = creature->GetGUID();
            break;
        case NPC_HIGH_PRIESTESS_MARLI:
            highPriestessMarliGUID = creature->GetGUID();
            break;
        case NPC_GARAJAL_THE_SPIRITBINDER:
            garazhalTheSpiritBinderGUID = creature->GetGUID();
            break;
        case NPC_TORTOS:
            tortosGUID = creature->GetGUID();
            break;
        case NPC_MEGAERA:
            megaeraGUID = creature->GetGUID();
            break;
        case NPC_JI_KUN:
            jiKunGUID = creature->GetGUID();
            break;
        case NPC_DURUMU_THE_FORGOTTEN:
            durumuTheForgottenGUID = creature->GetGUID();
            break;
        case NPC_PRIMORDIUS:
            primordiusGUID = creature->GetGUID();
            break;
        case NPC_DARK_ANIMUS:
            darkAnimusGUID = creature->GetGUID();
            break;
        case NPC_IRON_QON:
            ironQonGUID = creature->GetGUID();
            break;
        case NPC_ROSHAK:
            roshakGUID = creature->GetGUID();
            break;
        case NPC_QUETZAL:
            quetzalGUID = creature->GetGUID();
            break;
        case NPC_DAMREN:
            damrenGUID = creature->GetGUID();
            break;
        case NPC_LULIN:
            luLinGUID = creature->GetGUID();
            break;
        case NPC_SUEN:
            suenGUID = creature->GetGUID();
            break;
        case NPC_LEI_SHEN:
            leiShenGUID = creature->GetGUID();
            break;
        case NPC_RA_DEN:
            raDenGUID = creature->GetGUID();
            break;

        default: break;
        }
    }

    void OnGameObjectCreate(GameObject* go)
    {
        switch (go->GetEntry())
        {
        case GO_FIRST_DOOR:
            firstDoorguid = go->GetGUID();
            if (craziedStormCallerEvent == DONE)
                HandleGameObject(go->GetGUID(), true, go);
            break;
        case GO_MOGU_FOUNTAIN_NE:
            moguFountainNEguid = go->GetGUID();
            break;
        case GO_MOGU_FOUNTAIN_NW:
            moguFountainNWguid = go->GetGUID();
            break;
        case GO_MOGU_FOUNTAIN_SE:
            moguFountainSEguid = go->GetGUID();
            break;
        case GO_MOGU_FOUNTAIN_SW:
            moguFountainSWguid = go->GetGUID();
            break;
        case GO_HORRIDON_FARRAKI_DOOR:
            horridonFarrakiDoorGuid = go->GetGUID();
            break;
        case GO_HORRIDON_GURUBASHI_DOOR:
            horridonGurubashiDoorGuid = go->GetGUID();
            break;
        case GO_HORRIDON_DRAKKARI_DOOR:
            horridonDrakkariDoorGuid = go->GetGUID();
            break;
        case GO_HORRIDON_AMANI_DOOR:
            horridonAmaniDoorGuid = go->GetGUID();
            break;
        case GO_LIGHTNING_SPAN:
            lightningSpanGuid = go->GetGUID();
            if (lightningSpanEvent == DONE)
            {
                go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
            }
            break;
        case GO_MEGAERA_CHEST_10_NORMAL:
            megaeraChestGuids[0] = go->GetGUID();
            break;
        case GO_MEGAERA_CHEST_25_NORMAL:
            megaeraChestGuids[1] = go->GetGUID();
            break;
        case GO_MEGAERA_CHEST_10_HEROIC:
            megaeraChestGuids[2] = go->GetGUID();
            break;
        case GO_MEGAERA_CHEST_25_HEROIC:
            megaeraChestGuids[3] = go->GetGUID();
            break;
        case GO_DURUMU_PLATFORM_1:
            durumuPlatform1 = go->GetGUID();
            go->SetGoState(GetBossState(DATA_DURUMU_THE_FORGOTTEN) == IN_PROGRESS ? GO_STATE_ACTIVE : GO_STATE_READY);
            break;
        case GO_DURUMU_PLATFORM_2:
            durumuPlatform2 = go->GetGUID();
            go->SetGoState(GetBossState(DATA_DURUMU_THE_FORGOTTEN) == DONE ? GO_STATE_READY : GO_STATE_ACTIVE);
            break;
        case GO_CHARGING_STATION:
            chargingStationGUID = go->GetGUID();
            break;
        case GO_SOUTH_PILLAR:
            southPillarGUID = go->GetGUID();
            break;
        case GO_EAST_PILLAR:
            eastPillarGUID = go->GetGUID();
            break;
        case GO_WEST_PILLAR:
            westPillarGUID = go->GetGUID();
            break;
        case GO_NORTH_PILLAR:
            northPillarGUID = go->GetGUID();
            break;
        case GO_FLOOR_FX_SOUTH:
            floorSouthGUID = go->GetGUID();
            break;
        case GO_FLOOR_FX_EAST:
            floorEastGUID = go->GetGUID();
            break;
        case GO_FLOOR_FX_WEST:
            floorWestGUID = go->GetGUID();
            break;
        case GO_FLOOR_FX_NORTH:
            floorNorthGUID = go->GetGUID();
            break;
        case GO_NW_WINDOW:
            windowNorthWestGUID = go->GetGUID();
            break;
        case GO_SW_WINDOW:
            windowSouthWestGUID = go->GetGUID();
            break;
        case GO_NE_WINDOW:
            windowNorthEastGUID = go->GetGUID();
            break;
        case GO_SE_WINDOW:
            windowSouthEastGUID = go->GetGUID();
            break;
        case GO_CACHE_OF_STORMS_10_HEROIC:
            cacheOfStormsGUIDs[0] = go->GetGUID();
            break;
        case GO_CACHE_OF_STORMS_25_HEROIC:
            cacheOfStormsGUIDs[1] = go->GetGUID();
            break;
        case GO_JIN_ROKH_FRONT_DOOR:
        case GO_JIN_ROKH_BACK_DOOR:
        case GO_HORRIDON_FRONT_DOOR:
        case GO_HORRIDON_BACK_DOOR:
        case GO_ZANDALARI_COUNCIL_LEFT:
        case GO_ZANDALARI_COUNCIL_RIGHT:
        case GO_ZANDALARI_COUNCIL_EXIT:
        case GO_TORTOS_EXIT:
        case GO_MEGAERA_EXIT:
        case GO_JI_KUN_EXIT_DOOR:
        case GO_PRIMORDIUS_ENTRY_GATE:
        case GO_PRIMORDIUS_EXIT_GATE:
        case GO_SEWER_GATE:
        case GO_WIND_WALL:
        case GO_DOOR_TO_THE_QUEENS_CHAMBER_1:
        case GO_DOOR_TO_THE_QUEENS_CHAMBER_2:
        case GO_CHAMBER_OF_THE_TWIN_CONSORTS:
        case GO_TWIN_CONSORTS_PASSAGE:
            AddDoor(go, true);
            break;

        default:
            break;
        }
    }

    void SetData(uint32 type, uint32 data)
    {
        switch (type)
        {
        case DATA_HORRIDON_INTRO:
            horridonIntro = data;
            return; // dont save
        case DATA_CRAZIED_STORM_CALLER:
            craziedStormCallerEvent = data;
            if (data == DONE)
            {
                HandleGameObject(firstDoorguid, true);
            }
            break;
        case DATA_LIGHTNING_SPAN_EVENT:
            lightningSpanEvent = data;
            break;
        case DATA_RADEN_TRIES_COUNT:
            radenCounts = data;
            SendRadenTries();
            SaveToDB();
            break;
        }

        if (data == DONE)
            SaveToDB();
    }

    bool SetBossState(uint32 data, EncounterState state)
    {
        if (!InstanceScript::SetBossState(data, state))
            return false;

        if (data == DATA_DURUMU_THE_FORGOTTEN)
        {
            if (GameObject* pGo = instance->GetGameObject(durumuPlatform1))
            {
                pGo->SetGoState(state == IN_PROGRESS ? GO_STATE_ACTIVE : GO_STATE_READY);
            }

            if (GameObject* pGo = instance->GetGameObject(durumuPlatform2))
            {
                pGo->SetGoState(state == DONE ? GO_STATE_READY : GO_STATE_ACTIVE);
            }
        }
        else if (data == DATA_LEI_SHEN)
        {
            if (state != IN_PROGRESS)
            {
                if (GameObject* pFloor = instance->GetGameObject(floorNorthGUID))
                    pFloor->SetGoState(GO_STATE_READY);

                if (GameObject* pFloor = instance->GetGameObject(floorSouthGUID))
                    pFloor->SetGoState(GO_STATE_READY);

                if (GameObject* pFloor = instance->GetGameObject(floorWestGUID))
                    pFloor->SetGoState(GO_STATE_READY);

                if (GameObject* pFloor = instance->GetGameObject(floorEastGUID))
                    pFloor->SetGoState(GO_STATE_READY);

                if (GameObject* pStation = instance->GetGameObject(chargingStationGUID))
                    pStation->SetGoState(GO_STATE_READY);
            }
        }

        return true;
    }

    uint32 GetData(uint32 type) const override
    {
        switch (type)
        {
        case DATA_HORRIDON_INTRO: return horridonIntro;
        case DATA_CRAZIED_STORM_CALLER: return craziedStormCallerEvent;
        case DATA_LIGHTNING_SPAN_EVENT: return lightningSpanEvent;
        case DATA_RADEN_TRIES_COUNT: return radenCounts;
        }

        return 0;
    }

    ObjectGuid GetObjectGuid(uint32 type)
    {
        switch (type)
        {
        case DATA_JIN_ROKH_BREAKER:     return jinrokhBreakerGUID;
        case DATA_HORRIDON:             return horridonGUID;
        case DATA_KAZRAJIN:             return kazrajinGUID;
        case DATA_SUL_THE_SANDCRAWLER:  return sulTheSandCrawlerGUID;
        case DATA_FROST_KING_MALAKK:    return frostKingMalakkGUID;
        case DATA_HIGH_PRIESTESS_MARLI: return highPriestessMarliGUID;
        case DATA_GARAZHAL_THE_SPIRITBINDER: return garazhalTheSpiritBinderGUID;
        case DATA_TORTOS:               return tortosGUID;
        case DATA_MEGAERA:              return megaeraGUID;
        case DATA_JI_KUN:               return jiKunGUID;
        case DATA_DURUMU_THE_FORGOTTEN: return durumuTheForgottenGUID;
        case DATA_PRIMORDIUS:           return primordiusGUID;
        case DATA_DARK_ANIMUS:          return darkAnimusGUID;
        case DATA_IRON_QON:             return ironQonGUID;
        case DATA_ROSHAK:               return roshakGUID;
        case DATA_QUETZAL:              return quetzalGUID;
        case DATA_DAMREN:               return damrenGUID;
        case DATA_LULIN:               return luLinGUID;
        case DATA_SUEN:                 return suenGUID;
        case DATA_LEI_SHEN:             return leiShenGUID;
        case DATA_RA_DEN:               return raDenGUID;

        case DATA_MOGU_FOUNTAIN_NE:     return moguFountainNEguid;
        case DATA_MOGU_FOUNTAIN_NW:     return moguFountainNWguid;
        case DATA_MOGU_FOUNTAIN_SE:     return moguFountainSEguid;
        case DATA_MOGU_FOUNTAIN_SW:     return moguFountainSWguid;
        case DATA_HORRIDON_FARRAKI_DOOR: return horridonFarrakiDoorGuid;
        case DATA_HORRIDON_GURUBASHI_DOOR: return horridonGurubashiDoorGuid;
        case DATA_HORRIDON_DRAKKARI_DOOR: return horridonDrakkariDoorGuid;
        case DATA_HORRIDON_AMANI_DOOR: return horridonAmaniDoorGuid;
        case DATA_LIGHTNING_SPAN:       return lightningSpanGuid;
        case DATA_MEGAERA_CHEST_10_NORMAL:  return megaeraChestGuids[0];
        case DATA_MEGAERA_CHEST_25_NORMAL: return megaeraChestGuids[1];
        case DATA_MEGAERA_CHEST_10_HEROIC: return megaeraChestGuids[2];
        case DATA_MEGAERA_CHEST_25_HEROIC: return megaeraChestGuids[3];
        case DATA_CHARGING_STATION: return chargingStationGUID;
        case DATA_SOUTH_PILLAR: return southPillarGUID;
        case DATA_EAST_PILLAR: return eastPillarGUID;
        case DATA_WEST_PILLAR: return westPillarGUID;
        case DATA_NORTH_PILLAR: return northPillarGUID;
        case DATA_FLOOR_SOUTH: return floorSouthGUID;
        case DATA_FLOOR_EAST: return floorEastGUID;
        case DATA_FLOOR_WEST: return floorWestGUID;
        case DATA_FLOOR_NORTH: return floorNorthGUID;
        case DATA_WINDOW_NORTH_EAST: return windowNorthEastGUID;
        case DATA_WINDOW_NORTH_WEST: return windowNorthWestGUID;
        case DATA_WINDOW_SOUTH_EAST: return windowSouthEastGUID;
        case DATA_WINDOW_SOUTH_WEST: return windowSouthWestGUID;
        case DATA_CACHE_OF_STORMS_10_HEROIC: return cacheOfStormsGUIDs[0];
        case DATA_CACHE_OF_STORMS_25_HEROIC: return cacheOfStormsGUIDs[1];
        }

        return ObjectGuid::Empty;
    }

    /*std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "T T " << GetBossSaveData() << craziedStormCallerEvent << ' '
            << lightningSpanEvent << ' ' << radenCounts;

        OUT_SAVE_INST_DATA_COMPLETE;
        return saveStream.str();
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(in);

        char dataHead1, dataHead2;

        std::istringstream loadStream(in);
        loadStream >> dataHead1 >> dataHead2;

        if (dataHead1 == 'T' && dataHead2 == 'T')
        {
            for (uint32 i = 0; i < MAX_ENCOUNTERS; ++i)
            {
                uint32 tmpState;
                loadStream >> tmpState;

                if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                    tmpState = NOT_STARTED;

                SetBossState(i, EncounterState(tmpState));
            }

            uint32 tempEvent = 0;
            loadStream >> tempEvent;
            craziedStormCallerEvent = (tempEvent == DONE) ? DONE : NOT_STARTED;

            loadStream >> tempEvent;
            lightningSpanEvent = (tempEvent == DONE) ? DONE : NOT_STARTED;

            uint32 counts = 0;
            loadStream >> counts;
            radenCounts = counts > 0 ? counts : 0;

        }
        else OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }*/

    void Update(uint32 diff)
    {
        ProcessJiKunFallCatcher(diff);
    }

private:

    // creatures
    ObjectGuid jinrokhBreakerGUID;
    ObjectGuid horridonGUID;
    ObjectGuid kazrajinGUID;
    ObjectGuid sulTheSandCrawlerGUID;
    ObjectGuid frostKingMalakkGUID;
    ObjectGuid highPriestessMarliGUID;
    ObjectGuid garazhalTheSpiritBinderGUID;
    ObjectGuid tortosGUID;
    ObjectGuid megaeraGUID;
    ObjectGuid jiKunGUID;
    ObjectGuid durumuTheForgottenGUID;
    ObjectGuid primordiusGUID;
    ObjectGuid darkAnimusGUID;
    ObjectGuid ironQonGUID;
    ObjectGuid roshakGUID;
    ObjectGuid quetzalGUID;
    ObjectGuid damrenGUID;
    ObjectGuid luLinGUID;
    ObjectGuid suenGUID;
    ObjectGuid leiShenGUID;
    ObjectGuid raDenGUID;

    // gameObjects
    ObjectGuid firstDoorguid;
    ObjectGuid moguFountainNEguid;
    ObjectGuid moguFountainNWguid;
    ObjectGuid moguFountainSEguid;
    ObjectGuid moguFountainSWguid;
    ObjectGuid horridonFarrakiDoorGuid;
    ObjectGuid horridonGurubashiDoorGuid;
    ObjectGuid horridonDrakkariDoorGuid;
    ObjectGuid horridonAmaniDoorGuid;
    ObjectGuid lightningSpanGuid;
    ObjectGuid megaeraChestGuids[4];
    ObjectGuid durumuPlatform1;
    ObjectGuid durumuPlatform2;
    ObjectGuid chargingStationGUID;
    ObjectGuid southPillarGUID;
    ObjectGuid eastPillarGUID;
    ObjectGuid westPillarGUID;
    ObjectGuid northPillarGUID;
    ObjectGuid floorSouthGUID;
    ObjectGuid floorEastGUID;
    ObjectGuid floorWestGUID;
    ObjectGuid floorNorthGUID;
    ObjectGuid windowNorthWestGUID;
    ObjectGuid windowSouthWestGUID;
    ObjectGuid windowNorthEastGUID;
    ObjectGuid windowSouthEastGUID;
    ObjectGuid cacheOfStormsGUIDs[2];

    uint32 horridonIntro;
    uint32 craziedStormCallerEvent;
    uint32 lightningSpanEvent;

    uint32 jiKunFallCatcherTimer;

    uint32 radenCounts;

private:

    void ProcessJiKunFallCatcher(uint32 diff)
    {
        if (instance->GetPlayers().isEmpty())
            return;

        if (jiKunFallCatcherTimer <= diff)
        {
            jiKunFallCatcherTimer = 300;

            for (Map::PlayerList::const_iterator itr = instance->GetPlayers().begin(); itr != instance->GetPlayers().end(); ++itr)
            {
                Player* player = itr->GetSource();

                if (!player)
                    continue;

                if (!player->IsFalling() || player->GetPositionZ() >= -115.0f)
                    continue;

                if (Creature* pCatcher = player->FindNearestCreature(69839, 130.0f))
                {
                    if (GetBossState(DATA_JI_KUN) == IN_PROGRESS)
                    {
                        player->GetMotionMaster()->MoveJump(pCatcher->GetPositionX(), pCatcher->GetPositionY(), pCatcher->GetPositionZ(), 0, 10.0f, 10.0f);
                    }
                    else
                    {
                        player->NearTeleportTo(jikunNonCombatPos.GetPositionX(), jikunNonCombatPos.GetPositionY(), jikunNonCombatPos.GetPositionZ(), jikunNonCombatPos.GetOrientation());
                    }
                }
            }
        }
        else
        {
            jiKunFallCatcherTimer -= diff;
        }
    }

    void SendRadenTries(Player* forPlayer = NULL)
    {
        uint32 count = RADEN_MAX_TRIES > radenCounts ? RADEN_MAX_TRIES - radenCounts : 0;

        if (forPlayer)
        {
            forPlayer->SendUpdateWorldState(RADEN_TRIES_WORLDSTATE, count);
        }
        else
        {
            DoUpdateWorldState(RADEN_TRIES_WORLDSTATE, count);
        }
    }
};

void AddSC_instance_throne_of_thunder()
{
    RegisterInstanceScript(instance_throne_of_thunder, 1098);
}
