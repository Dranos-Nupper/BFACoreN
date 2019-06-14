/*
 * Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * Copyright (C) 2008-2014 Hellground <http://hellground.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ScriptMgr.h"
#include <iostream>
using namespace std;

enum Spells {
    SPELL_INFERNAL_SPAWN_DAMAGE = 33637,

    SPELL_SHAMAN_SHOCK = 15616,

    SPELL_THROW = 29582,

    SPELL_SHOOT = 15547,

    SPELL_EXORCISM = 33632,
    SPELL_HAMMER_OF_JUSTICE = 13005,
    SPELL_SEAL_OF_SACRIFICE = 13903,
    SPELL_STRIKE = 33626,
    SPELL_CLEAVE = 15496,
    SPELL_CUTDOWN = 32009,

    SPELL_ICEBOLT = 33463,
    SPELL_ARCANE_E = 33623,
    SPELL_BLIZZARD = 33624,

    SPELL_DIVINE_SHIELD = 33581,
    SPELL_JUDGEMENT = 33554,
    SPELL_BLESSING_MIGHT = 33564,
    SPELL_CONSECRATION = 33559,
    SPELL_FLASH_OF_LIGHT = 33641,

    SPELL_CHAIN_HEAL = 33642,
    SPELL_CHAIN_LIGHTNING = 33643,
    SPELL_MAGMA_FLOW_TOTEM = 33560,
    SPELL_STORM_TOTEM = 33570,
    SPELL_EARTH_SHOCK = 22885,
    SPELL_REVIVE_SELF = 32343,

    SPELL_CLEAVE_PITLORD = 16044,
    SPELL_RAIN_OF_FIRE = 33627,
    SPELL_SUMMON_INFERNALS = 33393,
    SPELL_INFERNALS_RAIN = 32785,
};

enum DarkPortalCreatures {

    CREATURE_WRATH_MASTER = 19005,
    CREATURE_FEL_SOLDIER = 18944,
    CREATURE_INFERNAL_SIEGEBREAKER = 18946,
    CREATURE_INFERNAL_RELAY = 19215,
    CREATURE_INFERNAL_TARGET = 21075,
};

const float runPosition[2][3] =
{
    {-240.848f, 1094.25f, 41.7500f},
    {-261.527f, 1093.32f, 41.7500f}
};

const float FirstFormation[5][4] =
{
    {-218.895f, 1502.76f, 20.7800f, 4.2106f},  // Left 1 - Fel Soldier
    {-209.949f, 1508.24f, 21.9920f, 4.4965f},  // Left 2 - Fel Soldier
    {-236.579f, 1506.04f, 21.4575f, 4.6764f},  // Right 1 - Fel Soldier
    {-241.711f, 1514.15f, 22.6739f, 4.4965f},  // Right 2 - Fel Soldier
    {-229.307f, 1497.77f, 20.1869f, 4.4832f}   // Center - Wrath Master
};

const float SecondFormation[8][4] =
{
    {-213.005f, 1496.72f, 20.9439f, 4.4745f},  // 1 1 - Fel Soldier
    {-223.101f, 1499.17f, 20.3675f, 4.4745f},  // 1 2 - Fel Soldier
    {-234.240f, 1501.86f, 20.8176f, 4.4745f},  // 1 3 - Fel Soldier
    {-243.119f, 1503.89f, 21.7681f, 4.4745f},  // 1 4 - Fel Soldier
    {-241.454f, 1514.69f, 22.7010f, 4.4745f},  // 2 1 - Fel Soldier
    {-231.970f, 1512.72f, 22.0880f, 4.4745f},  // 2 2 - Fel Soldier
    {-220.767f, 1509.81f, 21.4782f, 4.4745f},  // 2 3 - Fel Soldier
    {-210.363f, 1507.31f, 21.8889f, 4.4745f}   // 2 4 - Fel Soldier
};

// Waypoints
const uint32 FirstPathList[5] = { 98250, 98251, 98252, 98253, 98254 };
const uint32 SecondPathList[8] = { 98255, 98256, 98257, 98258, 98259, 98260, 98261, 98262 };

struct npc_pit_commander : public ScriptedAI
{
    npc_pit_commander(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        infernalTimer = 0;
        invadersTimer = 0;
        cleaveTimer = 5000;
        rainOfFireTimer = 15000;
        me->setActive(true);
    }

    void InfernalEvent()
    {
        casterLeft = me->SummonCreature(CREATURE_INFERNAL_TARGET, -266.623993f, 1154.459961f, 79.476402f, 2.5f, TEMPSUMMON_MANUAL_DESPAWN, 0);
        casterRight = me->SummonCreature(CREATURE_INFERNAL_TARGET, -292.790985f, 1143.219971f, 91.936798f, 2.5f, TEMPSUMMON_MANUAL_DESPAWN, 0);

        if (casterRight)
        {
            casterRight->CastSpell(-266.312012f, 1099.079956f, 41.791599f, SPELL_INFERNALS_RAIN, true);
            casterRight->ToCreature()->ForcedDespawn();
        }
        if (casterLeft)
        {
            casterLeft->CastSpell(-234.447998f, 1097.599976f, 41.791599f, SPELL_INFERNALS_RAIN, true);
            casterLeft->ToCreature()->ForcedDespawn();
        }
    }

    void SummonInvaders()
    {
        switch (urand(0, 1))
        {
            // First Formation
        case 0:
        {
            for (int i = 0; i < 4; i++)
            {
                if (Unit *Solider = me->SummonCreature(CREATURE_FEL_SOLDIER, FirstFormation[i][0], FirstFormation[i][1], FirstFormation[i][2], FirstFormation[i][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000))
                {
                    Solider->setActive(true);
                    Solider->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                    Solider->GetMotionMaster()->MovePath(FirstPathList[i], false);
                }
            }

            if (Unit *WrathMaster = me->SummonCreature(CREATURE_WRATH_MASTER, FirstFormation[4][0], FirstFormation[4][1], FirstFormation[4][2], FirstFormation[4][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000))
            {
                WrathMaster->setActive(true);
                WrathMaster->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                WrathMaster->GetMotionMaster()->MovePath(FirstPathList[4], false);
            }
        } break;
        // Second Formation
        case 1:
        {
            for (int i = 0; i < 8; i++)
            {
                if (Unit *Solider = me->SummonCreature(CREATURE_FEL_SOLDIER, SecondFormation[i][0], SecondFormation[i][1], SecondFormation[i][2], SecondFormation[i][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000))
                {
                    Solider->setActive(true);
                    Solider->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                    Solider->GetMotionMaster()->MovePath(SecondPathList[i], false);
                }
            }
        } break;
        }
    }

    void MoveInLineOfSight(Unit* who)
    {
        if (who->GetTypeId() == TYPEID_UNIT)
            return;
    }

    void UpdateAI(const uint32 diff)
    {
        if (infernalTimer <= diff)
        {
            DoCast(me, SPELL_SUMMON_INFERNALS);
            InfernalEvent();
            infernalTimer = 40000;
        }
        else infernalTimer -= diff;

        if (invadersTimer <= diff)
        {
            SummonInvaders();
            invadersTimer = 60000;
        }
        else invadersTimer -= diff;

        if (!UpdateVictim())
            return;

        if (cleaveTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_CLEAVE_PITLORD);
            cleaveTimer = 20000;
        }
        else cleaveTimer -= diff;

        if (rainOfFireTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_RAIN_OF_FIRE);
            rainOfFireTimer = 30000;
        }
        else rainOfFireTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 infernalTimer;
    uint32 invadersTimer;
    uint32 cleaveTimer;
    uint32 rainOfFireTimer;

    Unit* casterLeft;
    Unit* casterRight;
};

struct npc_melgromm_highmountain : public ScriptedAI
{
    npc_melgromm_highmountain(Creature* pCreature) : ScriptedAI(pCreature)
    {
        me->SetFlag(UNIT_FIELD_BOUNDINGRADIUS, 45.0f);
    }

    void EnterEvadeMode(EvadeReason why)
    {
        if (why == EVADE_REASON_NO_HOSTILES && me->FindNearestCreature(CREATURE_FEL_SOLDIER, 45.0f) == nullptr && me->FindNearestCreature(CREATURE_WRATH_MASTER, 45.0f) == nullptr)
        {
            ScriptedAI::_EnterEvadeMode();
            if (me->IsAlive())
                me->KillSelf();
        }
        /*string reason = " ";
        if (why == EVADE_REASON_NO_HOSTILES)
            reason = "no hostiles";
        else if (why == EVADE_REASON_NO_PATH)
            reason = "no_path";
        else if (why == EVADE_REASON_SEQUENCE_BREAK)
            reason = "sequence break";
        else if (why == EVADE_REASON_OTHER)
            reason = "reason other";
        cout << reason << endl;*/
    }

    void Reset()
    {
        stormTotemTimer = 15000;
        chainHealTimer = 12000;
        chainLightTimer = 10000;
        magmaFlowTimer = 5000;
        earthShockTimer = 8000;

        me->setActive(true);
        //me->SetAggroRange(45.0f);
        me->SetReactState(REACT_AGGRESSIVE);
        //me->AI()->GetBoundary()->
        //CreatureAI::CheckInRoom
        me->SetFlag(UNIT_FIELD_BOUNDINGRADIUS, 45.0f);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void JustDied(Unit* Killer)
    {
        // WoWhead: Respawns instantly if killed, so does Justinius.
        me->Respawn();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(45.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                {
                    //me->AI()->AttackStart(AliveInvader);
                    AliveInvader->SetInCombatWith(me);
                    me->AI()->AttackStart(AliveInvader);
                }
        }

        if (stormTotemTimer <= diff)
        {
            if (!me->IsInCombat())
            {
                Unit * Totem = GetClosestCreatureWithEntry(me, 19225, 20.0f);

                if (!Totem)
                    DoCast(me, SPELL_STORM_TOTEM);
            }
            stormTotemTimer = 15000;
        }
        else stormTotemTimer -= diff;

        if (!UpdateVictim())
            return;

        if (chainHealTimer <= diff)
        {
            DoCast(me, SPELL_CHAIN_HEAL);
            chainHealTimer = 12000;
        }
        else chainHealTimer -= diff;

        if (chainLightTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_CHAIN_LIGHTNING);
            chainLightTimer = 10000;
        }
        else chainLightTimer -= diff;

        if (magmaFlowTimer <= diff)
        {
            DoCast(me, SPELL_MAGMA_FLOW_TOTEM);
            magmaFlowTimer = 5000;
        }
        else magmaFlowTimer -= diff;

        if (earthShockTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_EARTH_SHOCK);
            earthShockTimer = 8000;
        }
        else earthShockTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 stormTotemTimer;
    uint32 chainHealTimer;
    uint32 chainLightTimer;
    uint32 magmaFlowTimer;
    uint32 earthShockTimer;
};

struct npc_justinus_the_harbinger : public ScriptedAI
{
    npc_justinus_the_harbinger(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        divineShieldTimer = 20000;
        judgementTimer = 5000;
        blessingMightTimer = 30000;
        consecrationTimer = 8000;
        flashofLightTimer = 12000;

        me->setActive(true);
        //me->SetAggroRange(45.0f);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void EnterCombat(Unit *who)
    {
        /*if (who->GetEntry() == CREATURE_INFERNAL_SIEGEBREAKER)
            DoYell(AGGRO_YELL, 0, 0);*/
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void JustDied(Unit* Killer)
    {
        // WoWhead: Respawns instantly if killed, so does Mulgromm.
        me->Respawn();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(45.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (blessingMightTimer <= diff)
        {
            DoCast(me, SPELL_BLESSING_MIGHT);
            blessingMightTimer = 30000;
        }
        else blessingMightTimer -= diff;

        if (!UpdateVictim())
            return;

        if (divineShieldTimer <= diff)
        {
            DoCast(me, SPELL_DIVINE_SHIELD);
            divineShieldTimer = 20000;
        }
        else divineShieldTimer -= diff;

        if (judgementTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_JUDGEMENT);
            judgementTimer = 5000;
        }
        else judgementTimer -= diff;

        if (consecrationTimer <= diff)
        {
            DoCast(me, SPELL_CONSECRATION);
            consecrationTimer = 8000;
        }
        else consecrationTimer -= diff;

        if (flashofLightTimer <= diff)
        {
            DoCast(me, SPELL_FLASH_OF_LIGHT);
            flashofLightTimer = 12000;
        }
        else flashofLightTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 divineShieldTimer;
    uint32 judgementTimer;
    uint32 blessingMightTimer;
    uint32 consecrationTimer;
    uint32 flashofLightTimer;
};

struct npc_stormwind_mage : public ScriptedAI
{
    npc_stormwind_mage(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        ReadyToCast = 3000;

        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
        SetCombatMovement(false);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void UpdateAI(uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(45.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        if (ReadyToCast <= diff)
        {
            switch (urand(0, 1))
            {
            case 0:
                DoCast(me->GetVictim(), SPELL_ICEBOLT);
                break;
            case 1:
                DoCast(me->GetVictim(), SPELL_BLIZZARD);
                break;
            }
            ReadyToCast = 3000;
        }
        else ReadyToCast -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 ReadyToCast;
};

struct npc_undercity_mage : public ScriptedAI
{
    npc_undercity_mage(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        ReadyToCast = 3000;

        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
        SetCombatMovement(false);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void UpdateAI(uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(45.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        if (ReadyToCast <= diff)
        {
            switch (urand(0, 1))
            {
            case 0:
                DoCast(me->GetVictim(), SPELL_ICEBOLT);
                break;
            case 1:
                DoCast(me->GetVictim(), SPELL_BLIZZARD);
                break;
            }
            ReadyToCast = 3000;
        }
        else ReadyToCast -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 ReadyToCast;
};

struct npc_dark_portal_invader : public ScriptedAI
{
    npc_dark_portal_invader(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        cleaveTimer = urand(3000, 5000);
        cutDownTimer = urand(6000, 8000);
        readyToInvadeTimer = 15000;

        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
        atFinalPosition = false;
    }

    void EnterEvadeMode(EvadeReason /*why*/)
    {
        if (atFinalPosition)
            return;

        ScriptedAI::EnterEvadeMode();
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type == WAYPOINT_MOTION_TYPE /*&& id == 10*/)
            if (!me->isMoving())
             atFinalPosition = true;
    }

    void UpdateAI(uint32 diff)
    {
        if (me->IsInCombat())
            return;
        if (readyToInvadeTimer <= diff)
        {
            if (atFinalPosition)
            {
                me->ClearUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                me->SetWalk(false);

                switch (urand(0, 1))
                {
                case 0:
                    me->GetMotionMaster()->MovePoint(0, runPosition[0][0], runPosition[0][1], runPosition[0][2]);
                    break;
                case 1:
                    me->GetMotionMaster()->MovePoint(0, runPosition[1][0], runPosition[1][1], runPosition[1][2]);
                    break;
                }
            }
            readyToInvadeTimer = 20000;
        }
        else readyToInvadeTimer -= diff;

        if (!UpdateVictim())
            return;

        if (me->GetEntry() == CREATURE_FEL_SOLDIER)
        {
            if (cleaveTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = urand(3000, 5000);
            }
            else cleaveTimer -= diff;

            if (cutDownTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_CUTDOWN);
                cutDownTimer = urand(6000, 8000);
            }
            else cutDownTimer -= diff;
        }

        DoMeleeAttackIfReady();
    }

private:
    uint32 cleaveTimer;
    uint32 cutDownTimer;
    uint32 readyToInvadeTimer;
    bool atFinalPosition;
};

struct npc_stormwind_soldier : public ScriptedAI
{
    npc_stormwind_soldier(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        strikeTimer = urand(3000, 5000);
        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void UpdateAI(uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(30.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        if (strikeTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_STRIKE);
            strikeTimer = urand(5000, 8000);
        }
        else strikeTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 strikeTimer;
};

struct npc_orgrimmar_grunt : public ScriptedAI
{
    npc_orgrimmar_grunt(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        strikeTimer = urand(3000, 5000);
        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void JustDied(Unit* /*killer*/) override
    {
       /* me->Respawn(true);
        me->NearTeleportTo(-161.317993f, 965.409973f, 54.373798f, 1.7f);
        me->GetMotionMaster()->MovePath(98263, false);
        me->SetWalk(false);*/
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type == WAYPOINT_MOTION_TYPE && id == 2)
        {
          //Position home = me->GetHomePosition();
          //  me->MovePosition(home, 0, 0);
            me->GetMotionMaster()->MoveTargetedHome();
        }
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void UpdateAI(uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(30.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        if (strikeTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_STRIKE);
            strikeTimer = urand(5000, 8000);
        }
        else strikeTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 strikeTimer;
};

struct npc_ironforge_paladin : public ScriptedAI
{
    npc_ironforge_paladin(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        exorcismTimer = urand(2000, 3000);
        justiceTimer = urand(7000, 9000);
        sacrificeTimer = urand(10000, 12000);
        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void UpdateAI(uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(30.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        if (exorcismTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_EXORCISM);
            exorcismTimer = urand(2000, 3000);
        }
        else exorcismTimer -= diff;

        if (justiceTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_HAMMER_OF_JUSTICE);
            justiceTimer = urand(7000, 9000);
        }
        else justiceTimer -= diff;

        if (sacrificeTimer <= diff)
        {
            DoCast(me, SPELL_SEAL_OF_SACRIFICE);
            sacrificeTimer = urand(10000, 12000);
        }
        else sacrificeTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 exorcismTimer;
    uint32 justiceTimer;
    uint32 sacrificeTimer;
};

struct npc_darnassian_archer : public ScriptedAI
{
    npc_darnassian_archer(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        shootTimer = 1500;
        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
        SetCombatMovement(false);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }


    void UpdateAI(uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(30.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        DoStartNoMovement(me->GetVictim());

        if (shootTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_SHOOT);
            shootTimer = 1500;
        }
        else shootTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 shootTimer;
};

struct npc_darkspear_axe_thrower : public ScriptedAI
{
    npc_darkspear_axe_thrower(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        throwTimer = urand(2000, 3000);
        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
        SetCombatMovement(false);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            damage = 0;
    }

    void UpdateAI(uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(30.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        DoStartNoMovement(me->GetVictim());

        if (throwTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_THROW);
            throwTimer = 1500;
        }
        else throwTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 throwTimer;
};

struct npc_orgrimmar_shaman : public ScriptedAI
{
    npc_orgrimmar_shaman(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
        shockTimer = urand(2000, 3000);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!me->IsInCombat())
        {
            if (Unit* AliveInvader = me->SelectNearestTarget(15.0f))
                if (AliveInvader->IsHostileTo(me) && !AliveInvader->IsPlayer())
                    me->AI()->AttackStart(AliveInvader);
        }

        if (!UpdateVictim())
            return;

        if (shockTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_SHAMAN_SHOCK);
            shockTimer = urand(5000, 8000);
        }
        else shockTimer -= diff;

        DoMeleeAttackIfReady();
    }

private:
    uint32 shockTimer;
};

struct npc_infernal_siegebreaker : public ScriptedAI
{
    npc_infernal_siegebreaker(Creature* pCreature) : ScriptedAI(pCreature){}

    void Reset()
    {
        me->setActive(true);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void UpdateAI(uint32 diff) override
    {
        DoMeleeAttackIfReady();
    }
};

//32785
class spell_infernal_rain : public SpellScript
{
    PrepareSpellScript(spell_infernal_rain);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        if (Creature* creature = target->ToCreature())
        {
            if (creature->GetEntry() == 19215)
            {
                caster->SummonCreature(CREATURE_INFERNAL_SIEGEBREAKER, creature->GetPosition());
                return;
            }
        }

        //todo check damage
        int32 basepoints0 = urand(200, 400);
        caster->CastCustomSpell(target, SPELL_INFERNAL_SPAWN_DAMAGE, &basepoints0, NULL, NULL, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_infernal_rain::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_stair_of_destiny()
{
    RegisterCreatureAI(npc_pit_commander);
    RegisterCreatureAI(npc_melgromm_highmountain);
    RegisterCreatureAI(npc_justinus_the_harbinger);
    RegisterCreatureAI(npc_stormwind_mage);
    RegisterCreatureAI(npc_undercity_mage);
    RegisterCreatureAI(npc_dark_portal_invader);
    RegisterCreatureAI(npc_stormwind_soldier);
    RegisterCreatureAI(npc_orgrimmar_grunt);
    RegisterCreatureAI(npc_ironforge_paladin);
    RegisterCreatureAI(npc_darnassian_archer);
    RegisterCreatureAI(npc_darkspear_axe_thrower);
    RegisterCreatureAI(npc_orgrimmar_shaman);
    RegisterCreatureAI(npc_infernal_siegebreaker);
    RegisterSpellScript(spell_infernal_rain);
}
