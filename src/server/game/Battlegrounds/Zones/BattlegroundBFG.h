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

#ifndef __BATTLEGROUNDBFG_H
#define __BATTLEGROUNDBFG_H

#include "Battleground.h"
#include "BattlegroundScore.h"

enum BG_BG_WorldStates {
    BG_BFG_OP_OCCUPIED_BASES_HORDE = 1778,
    BG_BFG_OP_OCCUPIED_BASES_ALLY = 1779,
    BG_BFG_OP_RESOURCES_ALLY = 1776,
    BG_BFG_OP_RESOURCES_HORDE = 1777,
    BG_BFG_OP_RESOURCES_MAX = 1780,
    BG_BFG_OP_RESOURCES_WARNING = 1955
};

enum BG_BFG_BroadcastTexts
{
    BG_BFG_TEXT_START_ONE_MINUTE = 10015,
    BG_BFG_TEXT_START_HALF_MINUTE = 10016,
    BG_BFG_TEXT_BATTLE_HAS_BEGUN = 10014
};

//const uint32 BG_BG_OP_NODESTATES[3] = { 1767, 1782, 1772 };
const uint32 BG_BFG_OP_NODESTATES[3] =
{
    8851,   // Lighthouse
    8852,   // Waterworks
    8853    // Mine
};

//2412 - Faro			        8851
//2405 - Estacion de bombeo	    8852
//2404 - Minas			        8853

//const uint32 BG_BG_OP_NODEICONS[3] = { 1842, 1846, 1845 };
const uint32 BG_BFG_OP_NODEICONS[3] = {
    2412,   // Lighthouse
    2405,   // Waterworks
    2404    // Mine
};

enum BG_BFG_NodeObjectId
{
    BG_BG_OBJECTID_NODE_BANNER_0 = 208779,      // Lighthouse banner
    BG_BG_OBJECTID_NODE_BANNER_1 = 208780,      // Waterworks banner
    BG_BG_OBJECTID_NODE_BANNER_2 = 208781       // Mine banner
};

enum BG_BFG_ObjectType
{
    BG_BG_OBJECT_BANNER_NEUTRAL = 0,
    BG_BG_OBJECT_BANNER_CONT_A = 1,
    BG_BG_OBJECT_BANNER_CONT_H = 2,
    BG_BG_OBJECT_BANNER_ALLY = 3,
    BG_BG_OBJECT_BANNER_HORDE = 4,
    BG_BG_OBJECT_AURA_ALLY = 5,
    BG_BG_OBJECT_AURA_HORDE = 6,
    BG_BG_OBJECT_AURA_CONTESTED = 7,
    BG_BG_OBJECT_GATE_A = 25,
    BG_BG_OBJECT_GATE_H = 26,
    //buffs
    BG_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE = 27,
    BG_BG_OBJECT_REGENBUFF_LIGHTHOUSE = 28,
    BG_BG_OBJECT_BERSERKBUFF_LIGHTHOUSE = 29,
    BG_BG_OBJECT_SPEEDBUFF_MINE = 30,
    BG_BG_OBJECT_REGENBUFF_MINE = 31,
    BG_BG_OBJECT_BERSERKBUFF_MINE = 32,
    BG_BG_OBJECT_SPEEDBUFF_WATERWORKS = 33,
    BG_BG_OBJECT_REGENBUFF_WATERWORKS = 34,
    BG_BG_OBJECT_BERSERKBUFF_WATERWORKS = 35,
    BG_BG_OBJECT_MAX = 36
};

/* Object id templates from DB */
enum BG_BFG_ObjectTypes
{
    BG_BFG_OBJECTID_BANNER_A = 208676,
    BG_BFG_OBJECTID_BANNER_CONT_A = 208763,
    BG_BFG_OBJECTID_BANNER_H = 208682,
    BG_BFG_OBJECTID_BANNER_CONT_H = 208769,

    BG_BFG_OBJECTID_AURA_A = 180100,
    BG_BFG_OBJECTID_AURA_H = 180101,
    BG_BFG_OBJECTID_AURA_C = 180102,

    BG_BFG_OBJECTID_GATE_A = 207177,
    BG_BFG_OBJECTID_GATE_H = 207178
};

enum BG_BFG_Timers
{
    BG_BFG_FLAG_CAPTURING_TIME = 60000,
};

enum BG_BFG_Score
{
    BG_BFG_WARNING_NEAR_VICTORY_SCORE = 1400,
    BG_BFG_MAX_TEAM_SCORE = 1500
};

/* do NOT change the order, else wrong behaviour */
enum BG_BFG_BattlegroundNodes
{
    BG_BFG_NODE_LIGHTHOUSE = 0,
    BG_BFG_NODE_WATERWORKS = 1,
    BG_BFG_NODE_MINE = 2,

    /// dynamic nodes that can be captured(it's normally 4)
    BG_BFG_DYNAMIC_NODES_COUNT = 3,

    /// spirit guides
    BG_BFG_SPIRIT_ALIANCE = 3,
    BG_BFG_SPIRIT_HORDE = 4,

    /// all nodes (dynamic and static)
    BG_BFG_ALL_NODES_COUNT = 5,
};

enum BG_BG_NodeStatus
{
    BG_BFG_NODE_TYPE_NEUTRAL = 0,
    BG_BFG_NODE_TYPE_CONTESTED = 1,
    BG_BFG_NODE_STATUS_ALLY_CONTESTED = 5,
    BG_BFG_NODE_STATUS_HORDE_CONTESTED = 4,
    BG_BFG_NODE_TYPE_OCCUPIED = 3,
    BG_BFG_NODE_STATUS_ALLY_OCCUPIED = 3,
    BG_BFG_NODE_STATUS_HORDE_OCCUPIED = 2
};

enum BG_BG_Sounds
{
    BG_BFG_SOUND_NODE_CLAIMED = 8192,
    BG_BFG_SOUND_NODE_CAPTURED_ALLIANCE = 8173,
    BG_BFG_SOUND_NODE_CAPTURED_HORDE = 8213,
    BG_BFG_SOUND_NODE_ASSAULTED_ALLIANCE = 8212,
    BG_BFG_SOUND_NODE_ASSAULTED_HORDE = 8174,
    BG_BFG_SOUND_NEAR_VICTORY = 8456
};

enum BG_BFG_Objectives
{
    BG_OBJECTIVE_ASSAULT_BASE = 122,
    BG_OBJECTIVE_DEFEND_BASE = 123
};

#define BG_BFG_NotBGBGWeekendHonorTicks      330
#define BG_BFG_BGBGWeekendHonorTicks         200
#define BG_BFG_NotBGBGWeekendReputationTicks 200
#define BG_BFG_BGBGWeekendReputationTicks    150

// x, y, z, o
const float BG_BFG_NodePositions[BG_BFG_DYNAMIC_NODES_COUNT][4] = {
    { 1057.7800f, 1278.260010f, 3.192400f, 1.864820f }, // Lighthouse
    { 980.09f, 948.74f, 12.67f, 5.9015f },              // Waterwork
    { 1251.110f, 958.3639f, 5.680f, 2.7698f }           // Mine
};

// x, y, z, o, rot0, rot1, rot2, rot3
const float BG_BFG_DoorPositions[2][8] = {
    { 918.876f, 1336.56f, 27.6195f, 2.77481f, 0.0f, 0.0f, 0.983231f, 0.182367f },
    { 1396.15f, 977.014f, 7.43169f, 6.27043f, 0.0f, 0.0f, 0.006378f, -0.99998f }
};

const uint32 BG_BFG_TickIntervals[4] = { 0, 12000, 6000, 1000 };
const uint32 BG_BFG_TickPoints[4] = { 0, 10, 10, 30 };

// WorldSafeLocs ids for 3 nodes, and for ally, and horde starting location
const uint32 BG_BFG_GraveyardIds[BG_BFG_ALL_NODES_COUNT] = { 1736, 1738, 1735, 1740, 1739 };

// x, y, z, o
const float BG_BFG_BuffPositions[BG_BFG_DYNAMIC_NODES_COUNT][4] = {
    { 1063.39f, 1309.09f, 4.91f, 3.98f },   // Lighthouse
    { 990.95f, 984.46f, 13.01f, 4.57f },    // Waterworks
    { 1196.65f, 1020.01f, 7.97f, 5.74f },   // Mine
    //{ 1107.57f, 912.18f, 27.54f, 5.53f } To be named
};

// x, y, z, o
Position const BG_BFG_SpiritGuidePos[BG_BFG_ALL_NODES_COUNT] = {
    { 1036.32f, 1341.61f, 11.55f, 4.78f },  // Lighthouse
    { 886.44f, 938.06f, 24.13f, 0.53f },    // Waterworks
    { 1252.39f, 831.77f, 27.78f, 1.59f },   // Mine
    { 898.15f, 1341.58f, 27.66f, 6.06f },   // alliance starting base
    { 1408.16f, 977.34f, 7.44f, 3.18f }     // horde starting base
};

struct BG_BFG_BannerTimer
{
    uint32      timer;
    uint8       type;
    uint8       teamIndex;
};
