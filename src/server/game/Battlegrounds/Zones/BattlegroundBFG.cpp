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

#include "BattlegroundBFG.h"
#include "BattlegroundMgr.h"
#include "DB2Stores.h"
#include "GameObject.h"
#include "Log.h"
#include "Map.h"
#include "Object.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "SpellInfo.h"
#include "WorldStatePackets.h"

// these variables aren't used outside of this file, so declare them only here
uint32 BG_BG_HonorScoreTicks[BG_HONOR_MODE_NUM] = {
    330, // normal honor
    200  // holiday
};

BattlegroundBFG::BattlegroundBFG()
{
    m_BuffChange = true;
    BgObjects.resize(BG_BG_OBJECT_MAX);
    BgCreatures.resize(BG_BFG_ALL_NODES_COUNT + 5); // +5 for aura triggers

    //StartMessageIds[BG_STARTING_EVENT_FIRST] = LANG_BG_BG_START_TWO_MINUTES;
    //StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_BG_BG_START_ONE_MINUTE;
    //StartMessageIds[BG_STARTING_EVENT_THIRD] = LANG_BG_BG_START_HALF_MINUTE;
    //StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_BG_BG_HAS_BEGUN;
}

BattlegroundBFG::~BattlegroundBFG()
{
}

void BattlegroundBFG::PostUpdateImpl(uint32 diff)
{
    if (GetStatus() == STATUS_IN_PROGRESS)
    {
        int team_points[BG_TEAMS_COUNT] = { 0, 0 };

        for (int node = 0; node < BG_BFG_DYNAMIC_NODES_COUNT; ++node)
        {
            // 3 sec delay to spawn new banner instead previous despawned one
            if (m_BannerTimers[node].timer)
            {
                if (m_BannerTimers[node].timer > diff)
                    m_BannerTimers[node].timer -= diff;
                else
                {
                    m_BannerTimers[node].timer = 0;
                    _CreateBanner(node, m_BannerTimers[node].type, m_BannerTimers[node].teamIndex, false);
                }
            }

            // 1-minute to occupy a node from contested state
            if (m_NodeTimers[node])
            {
                if (m_NodeTimers[node] > diff)
                    m_NodeTimers[node] -= diff;
                else
                {
                    m_NodeTimers[node] = 0;
                    // Change from contested to occupied !
                    uint8 teamIndex = m_Nodes[node] - 1;
                    m_prevNodes[node] = m_Nodes[node];
                    m_Nodes[node] += 2;
                    // burn current contested banner
                    _DelBanner(node, BG_BFG_NODE_TYPE_CONTESTED, teamIndex);
                    // create new occupied banner
                    _CreateBanner(node, BG_BFG_NODE_TYPE_OCCUPIED, teamIndex, true);
                    _SendNodeUpdate(node);
                    _NodeOccupied(node, (teamIndex == 0) ? ALLIANCE : HORDE);
                    // Message to chatlog

                    if (teamIndex == 0)
                    {
                        // FIXME: team and node names not localized
                        //SendMessage2ToAll(LANG_BG_AB_NODE_TAKEN, CHAT_MSG_BG_SYSTEM_ALLIANCE, NULL, LANG_BG_AB_ALLY, _GetNodeNameId(node));
                        PlaySoundToAll(BG_BFG_SOUND_NODE_CAPTURED_ALLIANCE);
                    }
                    else
                    {
                        // FIXME: team and node names not localized
                        //SendMessage2ToAll(LANG_BG_AB_NODE_TAKEN, CHAT_MSG_BG_SYSTEM_HORDE, NULL, LANG_BG_AB_HORDE, _GetNodeNameId(node));
                        PlaySoundToAll(BG_BFG_SOUND_NODE_CAPTURED_HORDE);
                    }
                }
            }

            for (int team = 0; team < BG_TEAMS_COUNT; ++team)
                if (m_Nodes[node] == team + BG_BFG_NODE_TYPE_OCCUPIED)
                    ++team_points[team];
        }

        // Accumulate points
        for (int team = 0; team < BG_TEAMS_COUNT; ++team)
        {
            int points = team_points[team];
            if (!points)
                continue;
            m_lastTick[team] += diff;
            if (m_lastTick[team] > BG_BFG_TickIntervals[points])
            {
                m_lastTick[team] -= BG_BFG_TickIntervals[points];
                m_TeamScores[team] += BG_BFG_TickPoints[points];
                m_HonorScoreTics[team] += BG_BFG_TickPoints[points];
                if (!m_IsInformedNearVictory && m_TeamScores[team] > BG_BFG_WARNING_NEAR_VICTORY_SCORE)
                {
                    /*if (team == TEAM_ALLIANCE)
                    SendMessageToAll(LANG_BG_AB_A_NEAR_VICTORY, CHAT_MSG_BG_SYSTEM_NEUTRAL);
                    else
                    SendMessageToAll(LANG_BG_AB_H_NEAR_VICTORY, CHAT_MSG_BG_SYSTEM_NEUTRAL);*/
                    PlaySoundToAll(BG_BFG_SOUND_NEAR_VICTORY);
                    m_IsInformedNearVictory = true;
                }

                if (m_TeamScores[team] > BG_BFG_MAX_TEAM_SCORE)
                    m_TeamScores[team] = BG_BFG_MAX_TEAM_SCORE;
                if (team == TEAM_ALLIANCE)
                    UpdateWorldState(BG_BFG_OP_RESOURCES_ALLY, m_TeamScores[team]);
                if (team == TEAM_HORDE)
                    UpdateWorldState(BG_BFG_OP_RESOURCES_HORDE, m_TeamScores[team]);
                // update achievement flags
                // we increased m_TeamScores[team] so we just need to check if it is 500 more than other teams resources
                uint8 otherTeam = (team + 1) % BG_TEAMS_COUNT;
                if (m_TeamScores[team] > m_TeamScores[otherTeam] + 500)
                    m_TeamScores500Disadvantage[otherTeam] = true;
            }
        }

        // Test win condition
        if (m_TeamScores[TEAM_ALLIANCE] >= BG_BFG_MAX_TEAM_SCORE)
            EndBattleground(ALLIANCE);
        if (m_TeamScores[TEAM_HORDE] >= BG_BFG_MAX_TEAM_SCORE)
            EndBattleground(HORDE);
    }
}

void BattlegroundBFG::StartingEventCloseDoors()
{
    // despawn banners, auras and buffs
    for (int obj = BG_BG_OBJECT_BANNER_NEUTRAL; obj < BG_BFG_DYNAMIC_NODES_COUNT * 8; ++obj)
        SpawnBGObject(obj, RESPAWN_ONE_DAY);
    for (int i = 0; i < BG_BFG_DYNAMIC_NODES_COUNT * 3; ++i)
        SpawnBGObject(BG_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE + i, RESPAWN_ONE_DAY);

    // Starting doors
    DoorClose(BG_BG_OBJECT_GATE_A);
    DoorClose(BG_BG_OBJECT_GATE_H);
    SpawnBGObject(BG_BG_OBJECT_GATE_A, RESPAWN_IMMEDIATELY);
    SpawnBGObject(BG_BG_OBJECT_GATE_H, RESPAWN_IMMEDIATELY);

    // Starting base spirit guides
    _NodeOccupied(BG_BFG_SPIRIT_ALIANCE, ALLIANCE);
    _NodeOccupied(BG_BFG_SPIRIT_HORDE, HORDE);
}

void BattlegroundBFG::StartingEventOpenDoors()
{
    // spawn neutral banners
    for (int banner = BG_BG_OBJECT_BANNER_NEUTRAL, i = 0; i < 3; banner += 8, ++i)
        SpawnBGObject(banner, RESPAWN_IMMEDIATELY);
    for (int i = 0; i < BG_BFG_DYNAMIC_NODES_COUNT; ++i)
    {
        //randomly select buff to spawn
        uint8 buff = urand(0, 2);
        SpawnBGObject(BG_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE + buff + i * 3, RESPAWN_IMMEDIATELY);
    }
    DoorOpen(BG_BG_OBJECT_GATE_A);
    DoorOpen(BG_BG_OBJECT_GATE_H);
}

void BattlegroundBFG::AddPlayer(Player* player)
{
    Battleground::AddPlayer(player);
    //create score and add it to map, default values are set in the constructor
    BattlegroundBFGScore* sc = new BattlegroundBFGScore(player->GetGUID(), player->GetBGTeam());

    PlayerScores[player->GetGUID()] = sc;
}

void BattlegroundBFG::RemovePlayer(Player* /*player*/, ObjectGuid /*guid*/, uint32 /*team*/)
{
}

void BattlegroundBFG::HandleAreaTrigger(Player* player, uint32 trigger, bool entered)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;
    //Area triggers are not handled yet!
    return;

    switch (trigger)
    {
    case 3866:                                          // Lighthouse
    case 3869:                                          // Watterwork
    case 3867:                                          // Mine
    case 4020:                                          // Unk1
    case 4021:                                          // Unk2
                                                        //break;
    default:
        Battleground::HandleAreaTrigger(player, trigger, entered);
        break;
    }
}
