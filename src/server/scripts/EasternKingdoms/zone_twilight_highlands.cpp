/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "SpellInfo.h"
#include "SceneHelper.h"

/*####
## npc_gurgthock_cata |
####*/

enum Gurgthock
{
    QUEST_THE_CRUCIBLE_OF_CARNAGE_THEBLOODEYE_BRUISER   = 27863,
    QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_H             = 27865, // second quest
    QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_A             = 27864, // second quest
    QUEST_THE_CRUCIBLE_OF_CARNAGE_CALDERS_CREATION      = 27866,
    QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_EARL_OF_EVIS      = 27867,
    QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_TWILIGHT_TERROR   = 27868,

    NPC_HURP_DERP                                       = 46944,
    NPC_SULLY_KNEECAPPER                                = 46946, // Horde Quest Boss
    NPC_TORG_DRAKEFLAYER                                = 46945, // Ally Quest Boss
    NPC_CADAVER_COLLAGE                                 = 46947,
    NPC_LORD_GEOFFERY_TULVAN                            = 46948,
    NPC_EMBERSCAR_THE_DEVOURER                          = 46949,

    // Trash
    NPC_GLOOMWING                                       = 47476,

    SAY_QUEST_ACCEPT_BLOODEYE                           = 0,
};

Position const CenterPos  = {-4190.416f, -5145.781f, -7.7363f, 2.070863f}; // CENTER

Position const SpawnPosition[] =
{
    {-4182.385f, -5111.955f, -7.7334f, 4.479527f}, // general spawnpos
    {-4194.154f, -5139.351f, -7.7364f, 1.865049f}, // direct center pos
    {-4108.251f, -5221.142f, -9.5933f, 2.296299f}, // outside arena
    {-4187.152f, -5157.176f, 8.42034f, 1.428060f} // gloomwing fly pos
};

class npc_gurgthock_cata : public CreatureScript
{
public:
    npc_gurgthock_cata() : CreatureScript("npc_gurgthock_cata") { }

    struct npc_gurgthock_cataAI : public ScriptedAI
    {
        npc_gurgthock_cataAI(Creature* creature) : ScriptedAI(creature) { }

        ObjectGuid SummonGUID;
        ObjectGuid uiPlayerGUID;

        uint32 uiTimer;
        uint32 uiPhase;
        uint32 uiRemoveFlagTimer;
        uint32 uiQuest;

        bool bRemoveFlag;

        void Reset() override
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            uiTimer = 0;
            uiPhase = 0;
            uiQuest = 0;
            uiRemoveFlagTimer = 5000;

            bRemoveFlag = false;
        }

        void SetGUID(ObjectGuid guid, int32 /*id*/) override
        {
            uiPlayerGUID = guid;
        }

        void SetData(uint32 uiId, uint32 uiValue) override
        {
            bRemoveFlag = true;
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

            switch (uiId)
            {
                case 1:
                    switch (uiValue)
                    {
                        case QUEST_THE_CRUCIBLE_OF_CARNAGE_THEBLOODEYE_BRUISER:
                            uiPhase = 1;
                            uiTimer = 4000;
                            break;
                        case QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_H:
                        case QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_A:
                            uiPhase = 3;
                            uiTimer = 3000;
                            break;
                        case QUEST_THE_CRUCIBLE_OF_CARNAGE_CALDERS_CREATION:
                            uiPhase = 6;
                            uiTimer = 3000;
                            break;
                        case QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_EARL_OF_EVIS:
                            uiPhase = 8;
                            uiTimer = 3000;
                            break;
                        case QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_TWILIGHT_TERROR:
                            uiPhase = 10;
                            uiTimer = 3000;
                            break;
                    }
                        break;
            }
        }

        void UpdateAI(uint32 uiDiff) override
        {
            ScriptedAI::UpdateAI(uiDiff);

            if (bRemoveFlag)
            {
                if (uiRemoveFlagTimer <= uiDiff)
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    bRemoveFlag = false;

                    uiRemoveFlagTimer = 10000;
                } else uiRemoveFlagTimer -= uiDiff;
            }

            if (uiPhase)
            {
                Player* player = ObjectAccessor::GetPlayer(*me, uiPlayerGUID);

                if (uiTimer <= uiDiff)
                {
                    switch (uiPhase)
                    {
                        case 1:
                            if (Creature* summon = me->SummonCreature(NPC_HURP_DERP, SpawnPosition[0], TEMPSUMMON_CORPSE_DESPAWN, 5000))
                                SummonGUID = summon->GetGUID();
                            uiPhase = 2;
                            uiTimer = 4000;
                            break;
                         case 2:
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, SummonGUID))
                                summon->GetMotionMaster()->MovePoint(0, CenterPos);
                            uiPhase = 0;
                            SummonGUID = ObjectGuid::Empty;
                            break;
                        case 3:
                            uiTimer = 3000;
                            uiPhase = 4;
                            break;
                        case 4:
                            if (player->GetTeamId() == TEAM_ALLIANCE)
                            {
                                if (Creature* summon = me->SummonCreature(NPC_TORG_DRAKEFLAYER, SpawnPosition[1], TEMPSUMMON_CORPSE_DESPAWN, 5000))
                                    SummonGUID = summon->GetGUID();
                            }
                            else
                            if (player->GetTeamId() == TEAM_HORDE)
                            {
                                if (Creature* summon = me->SummonCreature(NPC_SULLY_KNEECAPPER, SpawnPosition[1], TEMPSUMMON_CORPSE_DESPAWN, 5000))
                                    SummonGUID = summon->GetGUID();
                            }
                            uiTimer = 3000;
                            uiPhase = 0;
                            break;
                        case 6:
                            if (Creature* summon = me->SummonCreature(NPC_CADAVER_COLLAGE, SpawnPosition[0], TEMPSUMMON_CORPSE_DESPAWN, 5000))
                                SummonGUID = summon->GetGUID();
                            uiPhase = 7;
                            uiTimer = 4000;
                            break;
                         case 7:
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, SummonGUID))
                                summon->GetMotionMaster()->MovePoint(0, CenterPos);
                            uiPhase = 0;
                            SummonGUID = ObjectGuid::Empty;
                            break;
                        case 8:
                            if (Creature* summon = me->SummonCreature(NPC_LORD_GEOFFERY_TULVAN, SpawnPosition[2], TEMPSUMMON_CORPSE_DESPAWN, 5000))
                                SummonGUID = summon->GetGUID();
                            uiPhase = 9;
                            uiTimer = 4000;
                            break;
                         case 9:
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, SummonGUID))
                                summon->GetMotionMaster()->MovePoint(0, CenterPos);
                            uiPhase = 0;
                            SummonGUID = ObjectGuid::Empty;
                            break;
                        case 10:
                            if (Creature* summon = me->SummonCreature(NPC_EMBERSCAR_THE_DEVOURER, SpawnPosition[1], TEMPSUMMON_CORPSE_DESPAWN, 5000))
                                SummonGUID = summon->GetGUID();
                            uiPhase = 11;
                            uiTimer = 4000;
                            break;
                         case 11:
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, SummonGUID))
                                summon->GetMotionMaster()->MovePoint(0, CenterPos);
                            uiPhase = 0;
                            SummonGUID = ObjectGuid::Empty;
                            break;
                    }
                }else uiTimer -= uiDiff;
            }
        }
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        switch (quest->GetQuestId())
        {
            case QUEST_THE_CRUCIBLE_OF_CARNAGE_THEBLOODEYE_BRUISER:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_H:
            case QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_A:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_THE_CRUCIBLE_OF_CARNAGE_CALDERS_CREATION:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_EARL_OF_EVIS:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_TWILIGHT_TERROR:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
        }

        creature->AI()->SetGUID(player->GetGUID());

        return false;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gurgthock_cataAI(creature);
    }
};

/*####
## npc_hurp_derp
####*/

enum HurpSpells
{
    SPELL_INTIMIDATING_ROAR        = 91933,
    SPELL_OVERHEAD_SMASH           = 88482,
    SPELL_WHIRLWIND                = 83016
};

enum HurpEvents
{
    EVENT_INTIMIDATING_ROAR        = 1,
    EVENT_OVERHEAD_SMASH,
    EVENT_WHIRLWIND
};

class npc_hurp_derp : public CreatureScript
{
public:
    npc_hurp_derp() : CreatureScript("npc_hurp_derp") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hurp_derpAI (creature);
    }

    struct npc_hurp_derpAI : public ScriptedAI
    {
        npc_hurp_derpAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override { }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            me->DespawnOrUnsummon(3000);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_INTIMIDATING_ROAR, 10000);
            events.ScheduleEvent(EVENT_OVERHEAD_SMASH, 5000);
            events.ScheduleEvent(EVENT_WHIRLWIND, 15000);
        }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                player->GroupEventHappens(QUEST_THE_CRUCIBLE_OF_CARNAGE_THEBLOODEYE_BRUISER, killer);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_INTIMIDATING_ROAR:
                    DoCastVictim(SPELL_INTIMIDATING_ROAR);
                    events.ScheduleEvent(EVENT_INTIMIDATING_ROAR, urand(15*IN_MILLISECONDS, 25*IN_MILLISECONDS));
                    break;
                case EVENT_OVERHEAD_SMASH:
                    DoCastVictim(SPELL_OVERHEAD_SMASH);
                    events.ScheduleEvent(EVENT_OVERHEAD_SMASH, urand(20*IN_MILLISECONDS, 30*IN_MILLISECONDS));
                    break;
                case EVENT_WHIRLWIND:
                     if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0))
                     {
                         DoCast(target, SPELL_WHIRLWIND, true);
                     }
                    events.ScheduleEvent(EVENT_WHIRLWIND, urand(15*IN_MILLISECONDS, 25*IN_MILLISECONDS));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
    };
};

/*####
## npc_sully_kneecapper // npc_trog_drakeflayer
####*/

enum SullySpells
{
    SPELL_CHARGE             = 88288,
    SPELL_UPPERCUT           = 80182
};

enum SullyEvents
{
    EVENT_S_CHARGE           = 1,
    EVENT_UPPERCUT,
};

class npc_sully_kneecapper : public CreatureScript
{
public:
    npc_sully_kneecapper() : CreatureScript("npc_sully_kneecapper") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sully_kneecapperAI (creature);
    }

    struct npc_sully_kneecapperAI : public ScriptedAI
    {
        npc_sully_kneecapperAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            DespawnCreatures(47476);
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            me->DespawnOrUnsummon(3000);
            DespawnCreatures(47476);
        }

        void DespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);
            if (creatures.empty())
                return;
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_S_CHARGE, 10000);
            events.ScheduleEvent(EVENT_UPPERCUT, 5000);

            me->SummonCreature(NPC_GLOOMWING, SpawnPosition[3], TEMPSUMMON_CORPSE_DESPAWN, 5000);
        }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                player->GroupEventHappens(QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_H, killer);
            }
            DespawnCreatures(47476);
        }

        void UpdateAI(uint32 diff) override
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_S_CHARGE:
                    DoCastRandom(SPELL_CHARGE, 150.0f);
                    events.ScheduleEvent(EVENT_S_CHARGE, urand(10*IN_MILLISECONDS, 20*IN_MILLISECONDS));
                    break;
                case EVENT_UPPERCUT:
                    DoCastVictim(SPELL_UPPERCUT);
                    events.ScheduleEvent(EVENT_UPPERCUT, urand(15*IN_MILLISECONDS, 25*IN_MILLISECONDS));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
    };
};

class npc_torg_drakeflayer : public CreatureScript
{
public:
    npc_torg_drakeflayer() : CreatureScript("npc_torg_drakeflayer") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_torg_drakeflayerAI (creature);
    }

    struct npc_torg_drakeflayerAI : public ScriptedAI
    {
        npc_torg_drakeflayerAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            DespawnCreatures(47476);
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            me->DespawnOrUnsummon(3000);
            DespawnCreatures(47476);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_S_CHARGE, 10000);
            events.ScheduleEvent(EVENT_UPPERCUT, 5000);

            me->SummonCreature(NPC_GLOOMWING, SpawnPosition[3], TEMPSUMMON_CORPSE_DESPAWN, 5000);
        }

        void DespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);
            if (creatures.empty())
                return;
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                player->GroupEventHappens(QUEST_THE_CRUCIBLE_OF_CARNAGE_SPECIAL_A, killer);
            }
            DespawnCreatures(47476);
        }

        void UpdateAI(uint32 diff) override
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_S_CHARGE:
                    DoCastRandom(SPELL_CHARGE, 150.0f);
                    events.ScheduleEvent(EVENT_S_CHARGE, urand(10*IN_MILLISECONDS, 20*IN_MILLISECONDS));
                    break;
                case EVENT_UPPERCUT:
                    DoCastVictim(SPELL_UPPERCUT);
                    events.ScheduleEvent(EVENT_UPPERCUT, urand(15*IN_MILLISECONDS, 25*IN_MILLISECONDS));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
    };
};

/*####
## npc_cadaver_collage
####*/

enum CadaverSpells
{
    SPELL_BELCH                    = 88607,
    SPELL_INHALE                   = 88615,
    SPELL_PLAGUE_EXPLOSION         = 88614,
    SPELL_POISON_CLOUD             = 90447,
    SPELL_REPULSIVE_KICK           = 88605,
    SPELL_CADAVER_HOVER            = 95868
};

enum CadaverEvents
{
    EVENT_BELCH                    = 1,
    EVENT_INHALE,
    EVENT_PLAGUE_EXPLOSION,
    EVENT_POISON_CLOUD,
    EVENT_REPULSIVE_KICK,
    EVENT_BELOW5,
    EVENT_TAKEOFF,
    EVENT_EXPLODE
};

class npc_cadaver_collage : public CreatureScript
{
public:
    npc_cadaver_collage() : CreatureScript("npc_cadaver_collage") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_cadaver_collageAI (creature);
    }

    struct npc_cadaver_collageAI : public ScriptedAI
    {
        npc_cadaver_collageAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            DespawnTriggers(48591);
            inhaled = false;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_BELCH, 15000);
            events.ScheduleEvent(EVENT_POISON_CLOUD, 10000);
            events.ScheduleEvent(EVENT_REPULSIVE_KICK, 8000);
        }

        void DamageTaken(Unit* attacker, uint32& /*damage*/) override
        {
            if(!inhaled && !me->IsNonMeleeSpellCast(false) && HealthBelowPct(20))
            {
                if (Player* player = attacker->GetCharmerOrOwnerPlayerOrPlayerItself())
                {
                    player->GroupEventHappens(QUEST_THE_CRUCIBLE_OF_CARNAGE_CALDERS_CREATION, attacker);
                }

                inhaled = true;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras();
                me->SetReactState(REACT_PASSIVE);
                me->AttackStop();
                DoCast(SPELL_INHALE);
                events.CancelEvent(EVENT_BELCH); // just to be sure
                events.CancelEvent(EVENT_POISON_CLOUD);
                events.CancelEvent(EVENT_REPULSIVE_KICK);
                events.ScheduleEvent(EVENT_BELOW5, 6000);
            }
        }

        void DespawnTriggers(uint32 entry)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);
            if (creatures.empty())
                return;
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }

        void JustDied(Unit* /*killer*/) override { }

        void UpdateAI(uint32 diff) override
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_BELCH:
                    DoCastVictim(SPELL_BELCH);
                    events.ScheduleEvent(EVENT_BELCH, urand(15*IN_MILLISECONDS, 20*IN_MILLISECONDS));
                    break;
                case EVENT_POISON_CLOUD:
                    DoCast(SPELL_POISON_CLOUD);
                    events.ScheduleEvent(EVENT_POISON_CLOUD, urand(10*IN_MILLISECONDS, 15*IN_MILLISECONDS));
                    break;
                case EVENT_REPULSIVE_KICK:
                    DoCastVictim(SPELL_REPULSIVE_KICK);
                    events.ScheduleEvent(EVENT_REPULSIVE_KICK, urand(10*IN_MILLISECONDS, 15*IN_MILLISECONDS));
                    break;
                case EVENT_BELOW5:
                    me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    me->AddAura(SPELL_CADAVER_HOVER, me);
                    events.ScheduleEvent(EVENT_TAKEOFF, 5200);
                    break;
                case EVENT_TAKEOFF:
                    me->SetCanFly(true);
//                    me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                    me->SetDisableGravity(true);
                    me->SetSpeed(MOVE_FLIGHT, 0.5f);
                    me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+20.0f);
                    events.ScheduleEvent(EVENT_EXPLODE, 5600);
                    break;
                case EVENT_EXPLODE:
                    DoCast(SPELL_PLAGUE_EXPLOSION);
                    me->DespawnOrUnsummon(700);
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
        bool inhaled;
    };
};

/*####
## npc_lord_geoffery | TODO: Vehicle Transport npcs: wagen = 47523 ,pferd = 47522 ,anhenker = 47521
####*/

enum GeofferySpells
{
    SPELL_DEATH_BY_PEASANT        = 88619,
    SPELL_UNDYING_FRENZY           = 88616,
    SPELL_GEOF_UCUT                = 80182,
    SPELL_TRANSFORM_VISUAL         = 24085
};

enum GeofferyMisc
{
    DISPLAY_GEOF_WORGEN            = 34367
};

enum GeofferyEvents
{
    EVENT_DEATH_BY_PEASANT         = 1,
    EVENT_UNDYING_FRENZY,
    EVENT_GEOF_UCUT,
    EVENT_TRANSFORM
};

class npc_lord_geoffery : public CreatureScript
{
public:
    npc_lord_geoffery() : CreatureScript("npc_lord_geoffery") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lord_geofferyAI (creature);
    }

    struct npc_lord_geofferyAI : public ScriptedAI
    {
        npc_lord_geofferyAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            transformed = false;
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            me->DespawnOrUnsummon(3000);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_DEATH_BY_PEASANT, 15000);
            events.ScheduleEvent(EVENT_GEOF_UCUT, 5000);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/) override
        {
            if(!transformed && !me->IsNonMeleeSpellCast(false) && HealthBelowPct(20))
            {
               transformed = true;
               DoCast(me, SPELL_TRANSFORM_VISUAL);
               me->SetDisplayId(DISPLAY_GEOF_WORGEN);
               me->SetSpeed(MOVE_RUN, 2.5f); // his speed changes when transforming (Retail 1.5 | PWS: 2.5)
               events.ScheduleEvent(EVENT_UNDYING_FRENZY, 2000);
            }
        }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                player->GroupEventHappens(QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_EARL_OF_EVIS, killer);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_DEATH_BY_PEASANT:
                    DoCast(SPELL_DEATH_BY_PEASANT);
                    events.ScheduleEvent(EVENT_DEATH_BY_PEASANT, urand(30*IN_MILLISECONDS, 40*IN_MILLISECONDS));
                    break;
                case EVENT_UNDYING_FRENZY: // execute this event at 20% (needs retail info)
                    DoCastVictim(SPELL_UNDYING_FRENZY);
                    events.ScheduleEvent(EVENT_UNDYING_FRENZY, urand(10*IN_MILLISECONDS, 15*IN_MILLISECONDS));
                    break;
                case EVENT_GEOF_UCUT:
                    DoCastVictim(SPELL_UPPERCUT);
                    events.ScheduleEvent(EVENT_GEOF_UCUT, urand(15*IN_MILLISECONDS, 20*IN_MILLISECONDS));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
        bool transformed;
    };
};

/*####
## npc_emberscar_devourer
####*/

enum EmberSpells
{
    SPELL_ACTIVATE_POOLS           = 90409,
    SPELL_FIREBALL                 = 90446,
    SPELL_MAGMATIC_FAULT           = 90333
};

enum EmberEvents
{
    EVENT_ACTIVATE_POOLS           = 1,
    EVENT_FIREBALL,
    EVENT_MAG_FAULT
};

class npc_emberscar_devourer : public CreatureScript
{
public:
    npc_emberscar_devourer() : CreatureScript("npc_emberscar_devourer") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_emberscar_devourerAI (creature);
    }

    struct npc_emberscar_devourerAI : public ScriptedAI
    {
        npc_emberscar_devourerAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override { }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            me->DespawnOrUnsummon(3000);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_FIREBALL, 1000);
        }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                player->GroupEventHappens(QUEST_THE_CRUCIBLE_OF_CARNAGE_THE_TWILIGHT_TERROR, killer);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_FIREBALL:
                    DoCastVictim(SPELL_FIREBALL);
                    events.ScheduleEvent(EVENT_FIREBALL, 4000);
                    break;
                }
            }
        }
    private:
        EventMap events;
    };
};

/*####
## Arena Trash // Spellscripts
####*/

enum TrashSpells
{
    SPELL_GLOOM_BALL        = 88515,
};

enum TrashEvents
{
    EVENT_GLOOM_BALL        = 1,
};

class npc_gloomwing : public CreatureScript
{
public:
    npc_gloomwing() : CreatureScript("npc_gloomwing") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gloomwingAI (creature);
    }

    struct npc_gloomwingAI : public ScriptedAI
    {
        npc_gloomwingAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
            me->SetHover(true);
            me->SetCanFly(true);
        }

        void Reset() override
        {
            if (Unit* playersearch = me->SelectNearestPlayer(300.0f))
                AttackStartNoMove(playersearch);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_GLOOM_BALL, 2000);
        }

        void AttackStart(Unit* who) override
        {
            if (!who)
                return;

            AttackStartNoMove(who);
        }

        void UpdateAI(uint32 diff) override
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_GLOOM_BALL:
                    DoCast(SPELL_GLOOM_BALL);
                    events.ScheduleEvent(EVENT_GLOOM_BALL, urand(3*IN_MILLISECONDS, 6*IN_MILLISECONDS));
                    break;
                }
            }
        }
    private:
        EventMap events;
    };
};



// https://www.wowhead.com/spell=85287/transport-phase-aura transport shift
// shift 82239 end
// 80842 - Summon Morghor

// 80930
class spell_visual_kick : public SpellScriptLoader
{
public:
    spell_visual_kick() : SpellScriptLoader("spell_visual_kick") { }

    enum Npc {
        NPC_NEGOTIATOR = 43238,
    };

    class spell_visual_kick_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_visual_kick_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.clear();
            Unit* caster = GetCaster();
            if (!caster)
                return;
            if (Unit* target = caster->FindNearestCreature(NPC_NEGOTIATOR, 10.0f, true))
            {
                targets.push_back(target);
            }

        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_visual_kick_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_visual_kick_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_visual_kick_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_visual_kick_SpellScript();
    }
};

// 43238
struct npc_horde_negotiator : public ScriptedAI
{
    npc_horde_negotiator(Creature* pCreature) : ScriptedAI(pCreature)
    {
        first = false;
        second = false;
        third = false;
        last = false;
    }

    enum Npc
    {
        NPC_BUNNY_CHAPTER_ONE = 43483,
        NPC_WARCHIEF = 43260,
        NPC_WARCHIEF_GUARD = 43271,
    };

    enum Spell
    {
        SPELL_SUMMON_WARCHIEF = 80862,
        SPELL_WARCHIEF_STUN_PLAYER = 80920,
        SPELL_WARCHIEF_KICK = 80930,
        SPELL_WARCHIEF_KNOCKED_OUT = 80959,
        SPELL_REMOVE_NEGOTIATOR_AURA = 80950,
        SPELL_GROGGY = 81153,
    };

    enum Event
    {
        EVENT_WARCHIEF_ONE = 1,
        EVENT_BRING_HIM_ON,
        EVENT_WARCHIEF_STUN,
        EVENT_MADNESS,
        EVENT_DRAGONMAW,
        EVENT_KICK,
        EVENT_MOVE_TO_PLAYER,
        EVENT_MISSUNDERSTOOD,
        EVENT_WAS_THAT_A_THREAT,
        EVENT_KEEP_HIM_ALIVE,
        EVENT_ASSEMBLIED,
        EVENT_MOVE_NEGOTIATOR,
        EVENT_CALL_FOR_THE_OTHERS,
        EVENT_TELEPORT_DESPAWN,
    };

    enum TalkNegotiator
    {
        TALK_N_READY = 0,
        TALK_N_MEDICINE,
        TALK_N_AFTER,
        TALK_N_LARGEST,
        TALK_N_THIS,
        TALK_N_GREET_W,
        TALK_N_MISSUNDERSTOOD,
        TALK_N_ASSEMBLIED,
        TALK_N_MADNESS,
    };

    enum TalkWarchief
    {
        TALK_W_WASTING = 0,
        TALK_W_THREAT,
        TALK_W_BRING,
        TALK_W_THIS,
        TALK_W_DRAGONMAW,
        TALK_W_KEEP,
        TALK_W_CALL,
    };

    void IsSummonedBy(Unit* summoner) override
    {
        if (summoner)
        {
            me->GetMotionMaster()->MoveFollow(summoner, 0, 0);
            followingPlayer = true;
            owner = summoner;
        }
        Talk(TALK_N_READY);
    }

    void SpellHit(Unit* caster, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_WARCHIEF_KICK)
        {
            // hackfix until SPELL_EFFECT_LEAP_BACK works on creature
            me->GetMotionMaster()->MoveKnockbackFrom(caster->GetPositionX(), caster->GetPositionY(), 10.0f, 1.0f);
            AddTimedDelayedOperation(1000, [this]() -> void
            {
                /*
                if (me->IsAlive())
                    me->KillSelf();*/
                // fake death aura so updateAI still happens
                me->AddAura(89656);
            });
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == WAYPOINT_MOTION_TYPE)
        {
            switch (id)
            {
            case 7:
                Talk(TALK_N_GREET_W);
                me->GetMotionMaster()->MoveIdle();
                events.ScheduleEvent(EVENT_WARCHIEF_ONE, 500);
                if (Creature* warchief = me->FindNearestCreature(NPC_WARCHIEF, 20.0f))
                    me->FaceTargetAndStopMoving(warchief, 1);
                break;
            default:
                break;
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        // the npc got fast when the player mounts
        if (followingPlayer)
        {
            if (Unit* owner = me->GetOwner())
            {
                me->SetSpeed(MOVE_RUN, owner->GetSpeed(MOVE_RUN));
            }
        }

        if (Creature* bunny = me->FindNearestCreature(43483, 15))
        {
            float z = bunny->GetPositionZ();
            if (z > 16.0f && z < 20.0f && !first)
            {
                Talk(TALK_N_MEDICINE);
                first = true;
            }
            else if (z > 20.0f && z < 30.0f && !second)
            {
                Talk(TALK_N_AFTER);
                second = true;
            }
            else if (z > 37.0f && z < 38.0f && !third)
            {
                Talk(TALK_N_LARGEST);
                third = true;
                followingPlayer = false;
            }
            else if ((z > 38.0f && !last))
            {
                Talk(TALK_N_THIS);
                last = true;
                me->StopMoving();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePath(43238, false);
                if (Unit* owner = me->GetOwner())
                    owner->CastSpell(owner, SPELL_SUMMON_WARCHIEF, true);
            }
        }

        events.Update(diff);

        if (Creature* warchief = me->FindNearestCreature(NPC_WARCHIEF, 20.0f))
        {
            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_WARCHIEF_ONE:
                    warchief->AI()->Talk(TALK_W_WASTING);
                    events.ScheduleEvent(EVENT_MISSUNDERSTOOD, 6000);
                    break;
                case EVENT_MISSUNDERSTOOD:
                    Talk(TALK_N_MISSUNDERSTOOD);
                    events.ScheduleEvent(EVENT_WAS_THAT_A_THREAT, 1000);
                    break;
                case EVENT_WAS_THAT_A_THREAT:
                    warchief->AI()->Talk(TALK_W_THREAT);
                    events.ScheduleEvent(EVENT_ASSEMBLIED, 6000);
                    break;
                case EVENT_ASSEMBLIED:
                    Talk(TALK_N_ASSEMBLIED);
                    events.ScheduleEvent(EVENT_BRING_HIM_ON, 1000);
                    break;
                case EVENT_BRING_HIM_ON:
                    warchief->AI()->Talk(TALK_W_BRING);
                    events.ScheduleEvent(EVENT_WARCHIEF_STUN, 2000);
                    events.ScheduleEvent(EVENT_MOVE_NEGOTIATOR, 500);
                    break;
                case EVENT_MOVE_NEGOTIATOR:
                    warchief->GetMotionMaster()->MovePoint(0, warchiefPosMove);
                    //me->MovePosition(warchiefPosMove, 0, 0);
                    break;
                case EVENT_WARCHIEF_STUN:
                    warchief->AI()->Talk(TALK_W_THIS);
                    warchief->CastSpell(nullptr, SPELL_WARCHIEF_STUN_PLAYER);
                    events.ScheduleEvent(EVENT_MADNESS, 1000);
                    break;
                case EVENT_MADNESS:
                    Talk(TALK_N_MADNESS);
                    events.ScheduleEvent(EVENT_DRAGONMAW, 1000);
                    break;
                case EVENT_DRAGONMAW:
                    warchief->AI()->Talk(TALK_W_DRAGONMAW);
                    events.ScheduleEvent(EVENT_KICK, 1000);
                    break;
                case EVENT_KICK:
                    warchief->CastSpell(me, SPELL_WARCHIEF_KICK);
                    events.ScheduleEvent(EVENT_MOVE_TO_PLAYER, 3000);
                    break;
                case EVENT_MOVE_TO_PLAYER:
                    if (owner)
                        warchief->GetMotionMaster()->MovePoint(0, owner->GetPosition());
                    events.ScheduleEvent(EVENT_KEEP_HIM_ALIVE, 8000);
                    break;
                case EVENT_KEEP_HIM_ALIVE:
                    warchief->AI()->Talk(TALK_W_KEEP);
                    if (owner)
                        warchief->CastSpell(owner, SPELL_WARCHIEF_KNOCKED_OUT);
                    events.ScheduleEvent(EVENT_CALL_FOR_THE_OTHERS, 3000);
                    break;
                case EVENT_CALL_FOR_THE_OTHERS:
                    warchief->AI()->Talk(TALK_W_CALL);
                    events.ScheduleEvent(EVENT_TELEPORT_DESPAWN, 2000);
                    break;
                case EVENT_TELEPORT_DESPAWN:
                    me->DespawnCreaturesInArea(NPC_WARCHIEF);
                    me->DespawnCreaturesInArea(NPC_WARCHIEF_GUARD);
                    owner->CastSpell(owner, SPELL_GROGGY, true);
                    me->ForcedDespawn();
                    //owner->CastSpell(nullptr, SPELL_SUMMON_ZAELA);
                    //owner->CastSpell(nullptr, SPELL_SUMMON_GORTHUL);
                    break;
                default:
                    break;
                }
            }

        }
    }

private:
    bool first;
    bool second;
    bool third;
    bool last;
    bool followingPlayer;
    Position warchiefPosMove = { -4110.275f, -6415.123f, 37.72297f };
    Unit* owner;
};

// 82239 shift 3 - shift 82283
// 43190
struct npc_zaela_chapter1 : public ScriptedAI
{
    npc_zaela_chapter1(Creature* pCreature) : ScriptedAI(pCreature), sceneHelper(pCreature->GetGUID(), pCreature->GetMap())
    {
    }

    enum Talk {
        TALK_HURRY = 1,
        TALK_EQUIP,
        TALK_REMEMBER,
    };

    enum Spells {
        SPELL_QUEST_END = 81197,
    };

    enum QuestId {
        QUEST_MADNESS = 26549,
        QUEST_NEGOTIATIONS_TERMINATED = 26608,
    };

    void sQuestReward(Player* player, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->ID == QUEST_MADNESS)
        {
            player->CastSpell(player, SPELL_QUEST_END);
            Talk(TALK_REMEMBER);
        }
    }

    void sQuestAccept(Player* /*player*/, Quest const* quest)
    {
        if (quest->ID == QUEST_NEGOTIATIONS_TERMINATED)
            me->GetMotionMaster()->MovePath(4319001, false);
        me->ForcedDespawn(7000);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        if (summoner)
            if (Player* player = summoner->ToPlayer())
                player->KilledMonsterCredit(43243);

        sceneHelper.Clear();

        sceneHelper.AddSceneActionTalk(TALK_HURRY, 300);
        sceneHelper.AddSceneActionMovePath(4319000, 200);
        sceneHelper.AddSceneActionTalk(TALK_EQUIP, 7000);

        sceneHelper.Activate();

    }

    void UpdateAI(uint32 diff) override
    {
        sceneHelper.UpdateSceneHelper(diff);
    }

private:
    SceneHelper sceneHelper;
};

// 43398
struct npc_gorthul_chapter1 : public ScriptedAI
{
    npc_gorthul_chapter1(Creature* pCreature) : ScriptedAI(pCreature), sceneHelper(pCreature->GetGUID(), pCreature->GetMap())
    {
    }

    void IsSummonedBy(Unit* summoner) override
    {
        sceneHelper.Clear();

        me->HandleEmoteCommand(68);
        sceneHelper.AddSceneActionMovePath(4339800, 600);
        sceneHelper.AddSceneActionEmote(66, 9000);
        sceneHelper.AddSceneActionMovePath(4339801, 3000);
        sceneHelper.AddSceneActionDespawn(0, 7000);

        sceneHelper.Activate();
    }

    void UpdateAI(uint32 diff) override
    {
        sceneHelper.UpdateSceneHelper(diff);
    }

private:
    SceneHelper sceneHelper;
};

// 80959 - knocked out todo fix this
class spell_knocked_out : public AuraScript
{
    PrepareAuraScript(spell_knocked_out);

    enum Spell
    {
        SPELL_SUMMON_ZAELA = 81180,
        SPELL_SUMMON_GORTHUL = 81182,
    };

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* playerHit = GetTarget();
        if (!playerHit)
            return;

        playerHit->CastSpell(playerHit, SPELL_SUMMON_ZAELA, true);
        playerHit->CastSpell(playerHit, SPELL_SUMMON_GORTHUL, true);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_knocked_out::OnRemove, EFFECT_0, SPELL_EFFECT_APPLY_AURA, AURA_EFFECT_HANDLE_REAL);
    }
};

// 43578, 43577
struct npc_dragonmaw_revolutionary : public ScriptedAI
{
    npc_dragonmaw_revolutionary(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    enum Spells
    {
        SPELL_DRAGONMAW_WARRIOR_MALE = 81612,
        SPELL_DRAGONMAW_WARRIOR_FEMALE = 81647,
        SPELL_DRAGONMAW_SHAMAN_MALE = 81684,
        SPELL_DRAGONMAW_SHAMANE_FEMALE = 81686,
    };

    enum Killcredit
    {
        KILLCREDIT_ARMED = 43654,
    };

    void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId)
    {
        switch (gossipListId)
        {
        case 0:
            if (me->getGender() == GENDER_MALE)
                player->CastSpell(me, SPELL_DRAGONMAW_WARRIOR_MALE, true);
            else
                player->CastSpell(me, SPELL_DRAGONMAW_WARRIOR_FEMALE, true);
            player->KilledMonsterCredit(KILLCREDIT_ARMED);
            player->PlayerTalkClass->SendCloseGossip();
            me->ForcedDespawn();
            break;
        case 1:
            if (me->getGender() == GENDER_MALE)
                player->CastSpell(me, SPELL_DRAGONMAW_SHAMAN_MALE, true);
            else
                player->CastSpell(me, SPELL_DRAGONMAW_SHAMANE_FEMALE, true);
            player->KilledMonsterCredit(KILLCREDIT_ARMED);
            player->PlayerTalkClass->SendCloseGossip();
            me->ForcedDespawn();
            break;
        default:
            break;
        }
    }

};

// 43626, 43627
struct npc_dragonmaw_warrior : public ScriptedAI
{
    npc_dragonmaw_warrior(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    enum Events
    {
        EVENT_HARMSTRING = 1,
        EVENT_MORTAL_STRIKE,
    };

    enum Spells
    {
        SPELL_HARMSTRING = 9080,
        SPELL_MORTAL_STRIKE = 32736,
    };

    void EnterCombat(Unit* victim)
    {
        events.ScheduleEvent(EVENT_MORTAL_STRIKE, 5000);
        events.ScheduleEvent(SPELL_HARMSTRING, 9000);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_HARMSTRING:
                DoCastVictim(SPELL_HARMSTRING);
                events.ScheduleEvent(EVENT_HARMSTRING, 15000);
                break;
            case EVENT_MORTAL_STRIKE:
                DoCastVictim(SPELL_MORTAL_STRIKE);
                events.ScheduleEvent(EVENT_MORTAL_STRIKE, 7000);
                break;
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
};

// 43629, 43628
struct npc_dragonmaw_shaman : public ScriptedAI
{
    npc_dragonmaw_shaman(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    enum Events
    {
        EVENT_EARTHBIND_TOTEM = 1,
        EVENT_FROST_SHOCK,
        EVENT_HEALING_WAVE,
    };

    enum Spells
    {
        SPELL_EARTH_SHIELD = 101650,
        SPELL_EARTHBIND_TOTEM = 15786,
        SPELL_FROST_SHOCK = 79925,
        SPELL_HEALING_WAVE = 11986,
    };

    void Reset() override
    {
        if (!me->HasAura(SPELL_EARTH_SHIELD))
            DoCastSelf(SPELL_EARTH_SHIELD);
    }

    void EnterCombat(Unit* victim)
    {
        events.ScheduleEvent(EVENT_EARTHBIND_TOTEM, 6000);
        events.ScheduleEvent(EVENT_FROST_SHOCK, 3000);
        events.ScheduleEvent(EVENT_HEALING_WAVE, 1000);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_EARTHBIND_TOTEM:
                DoCastSelf(SPELL_EARTHBIND_TOTEM);
                events.ScheduleEvent(EVENT_EARTHBIND_TOTEM, 15000);
                break;
            case EVENT_FROST_SHOCK:
                DoCastVictim(SPELL_FROST_SHOCK);
                events.ScheduleEvent(EVENT_FROST_SHOCK, 8000);
                break;
            case EVENT_HEALING_WAVE:
                if (Unit* owner = me->GetOwner())
                {
                    if (owner->GetHealthPct() < 0.8)
                    {
                        me->CastSpell(owner, SPELL_HEALING_WAVE);
                        events.ScheduleEvent(EVENT_HEALING_WAVE, 15000);
                    }
                }
                events.ScheduleEvent(EVENT_HEALING_WAVE, 500);
                break;
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
};

// 43678
struct npc_dragonmaw_felblade : public ScriptedAI
{
    npc_dragonmaw_felblade(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    enum Events
    {
        EVENT_BLOODTHIRST = 1,
        EVENT_REND,
        EVENT_SHATTERING_THROW,
        EVENT_SLAM,
    };

    enum Spells
    {
        SPELL_BATTLE_SHOUT = 32064,
        SPELL_BLOODTHIRST = 79878,
        SPELL_REND = 11977,
        SPELL_SHATTERING_THROW = 79883,
        SPELL_SLAM = 79881,
    };

    void Reset() override
    {
    }

    void EnterCombat(Unit* victim)
    {
        DoCast(SPELL_BATTLE_SHOUT);
        events.ScheduleEvent(EVENT_BLOODTHIRST, 11000);
        events.ScheduleEvent(EVENT_REND, 9000);
        events.ScheduleEvent(EVENT_SHATTERING_THROW, 7000);
        events.ScheduleEvent(EVENT_SLAM, 4000);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_BLOODTHIRST:
                DoCastVictim(SPELL_BLOODTHIRST);
                events.ScheduleEvent(EVENT_BLOODTHIRST, 15000);
                break;
            case EVENT_REND:
                DoCastVictim(SPELL_REND);
                events.ScheduleEvent(EVENT_REND, 25000);
                break;
            case EVENT_SHATTERING_THROW:
                DoCastVictim(SPELL_SHATTERING_THROW);
                events.ScheduleEvent(EVENT_SHATTERING_THROW, 30000);
                break;
            case EVENT_SLAM:
                DoCastVictim(SPELL_SLAM);
                events.ScheduleEvent(EVENT_SLAM, 12000);
                break;
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
};

// 43189 todo
struct npc_warchief_moghor : public ScriptedAI
{
    npc_warchief_moghor(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    enum NpcId
    {
        NPC_ZAELA = 43939,
    };

    enum Events
    {
    };

    enum Spells
    {
    };

    void Reset() override
    {
    }

    void EnterCombat(Unit* victim)
    {
        zaela = false;
        Talk(0);
    }

    // didn't add spells cuz they might do too much dmg atm
    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->GetHealthPct() <= 50)
        {
            if (!zaela)
            {
                me->SummonCreature(NPC_ZAELA, -4099.25f, -6394.29f, 38.72333f);
                zaela = true;
            }
        }

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
private:
    bool zaela;
};

// 43939
struct npc_zaela_final : public ScriptedAI
{
    npc_zaela_final(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    void IsSummonedBy(Unit* summoner) override
    {
        Talk(0); // sound 21599 emote 5
        me->GetMotionMaster()->MovePath(4393900, false);
    }
};

// 44024
struct npc_artesh : public ScriptedAI
{
    npc_artesh(Creature* pCreature) : ScriptedAI(pCreature)
    {
        shamanTimer = 5000;
    }

    enum Quests
    {
        QUEST_MUDDIED_WATERS = 26784,
    };

    enum Npcs
    {
        NPC_DRAGONMAW_SHAMAN = 44026,
        NPC_PORTAL = 44050,
    };

    enum Spells
    {
        SPELL_CONE_OF_COLD = 82488,
        SPELL_COSMETIC_CHAIN_LIGHTNING = 82405,
    };

    void sQuestReward(Player* player, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->ID == QUEST_MUDDIED_WATERS)
        {
            if (Creature* portal = me->FindNearestCreature(NPC_PORTAL, 15.0f, true))
                me->CastSpell(portal, SPELL_CONE_OF_COLD);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (shamanTimer <= diff)
        {
            std::list<Creature*> shamans = me->FindNearestCreatures(NPC_DRAGONMAW_SHAMAN, 20.0f);
            Trinity::Containers::RandomResize(shamans, 1);
            for (Creature* shaman : shamans)
            {
                if (Creature* portal = me->FindNearestCreature(NPC_PORTAL, 15.0f, true))
                    shaman->CastSpell(portal, SPELL_COSMETIC_CHAIN_LIGHTNING);
                Talk(0);
            }
            // todo check timer
            shamanTimer = 25000;
        }
    }

private:
    int shamanTimer;
};

// 44050
struct npc_orgrimmar_portal_bunny : public ScriptedAI
{
    npc_orgrimmar_portal_bunny(Creature* pCreature) : ScriptedAI(pCreature)
    {
        me->AddAura(SPELL_PORTAL_VISUAL, me);
    }

    enum Spell
    {
        SPELL_TELEPORT = 82450,
        SPELL_PORTAL_VISUAL = 82454,
    };

    enum Quest
    {
        SAURFANG_WILL_BE_PLEASED = 26798,
    };

    void UpdateAI(uint32 diff) override
    {
        if (Player* player = me->SelectNearestPlayer(2))
        {
            if (player->HasQuest(SAURFANG_WILL_BE_PLEASED))
                me->CastSpell(player, SPELL_TELEPORT);
        }
    }
};

void AddSC_twilight_highlands()
{
    new npc_gurgthock_cata;
    new npc_hurp_derp;
    new npc_sully_kneecapper;
    new npc_torg_drakeflayer;
    new npc_cadaver_collage;
    new npc_lord_geoffery;
    new npc_emberscar_devourer;
    new npc_gloomwing();
    RegisterCreatureAI(npc_horde_negotiator);
    new spell_visual_kick();
    RegisterAuraScript(spell_knocked_out);
    RegisterCreatureAI(npc_zaela_chapter1);
    RegisterCreatureAI(npc_gorthul_chapter1);
    RegisterCreatureAI(npc_dragonmaw_revolutionary);
    RegisterCreatureAI(npc_dragonmaw_warrior);
    RegisterCreatureAI(npc_dragonmaw_shaman);
    RegisterCreatureAI(npc_dragonmaw_felblade);
    RegisterCreatureAI(npc_warchief_moghor);
    RegisterCreatureAI(npc_zaela_final);
    RegisterCreatureAI(npc_artesh);
    RegisterCreatureAI(npc_orgrimmar_portal_bunny);
}
