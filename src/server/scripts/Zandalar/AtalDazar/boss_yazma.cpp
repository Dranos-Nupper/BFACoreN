/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
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
#include "atal_dazar.h"

enum Spells {
    //Soulrend
    SPELL_SOULREND = 249923,
    SPELL_SOULREND_EXPLODE = 256577,
    //Basic Spells
    SPELL_WRACKING_PAIN = 250096,
    SPELL_SKEWER = 249919,
    //Echoes of Shadra
    //SPELL_TARGET_SELECTOR = 257066, //HITS ALL UNITS IN RANGE
    SPELL_ECHOES_OF_SHADOW = 250050,
    SPELL_ECHOES_OF_SHADOW_EMPOWERED = 258612,
    SPELL_ECHOES_OF_SHADOW_EMPOWERED2 = 256036,
    SPELL_ECHOES_OF_SHADOW_SPAWN = 257291,
    SPELL_ECHOES_OF_SHADOW_SPAWN_SMALL = 263092, // ?
    //SPELL_ECHOES_OF_SHAODW_AREATRIGGER = 263096, // the spiders on the stairs
    SPELL_ECHOES_OF_SHADOW_AREATRIGGER = 250022, //Bigger
};

enum Npcs {
    NPC_SOULREND = 125828,
};



enum Events {
    EVENT_SKEWER = 1,
    EVENT_WRACKING_PAIN,
    EVENT_ECHOES_OF_SHADOW,
    EVENT_SHADOWY_REMAINS,
    EVENT_SOULREND,
    EVENT_ECHOES_OF_SHADOW_SPAWN,

};

struct boss_ataldazar_yazma : public BossAI
{
    boss_ataldazar_yazma(Creature* creature) : BossAI(creature, DATA_YAZMA) { }

    void InitializeAI() override
    {
        BossAI::InitializeAI();
    }

    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_ECHOES_OF_SHADOW)
            me->CastSpell(target, SPELL_ECHOES_OF_SHADOW_SPAWN, TRIGGERED_CAN_CAST_WHILE_CASTING_MASK);
        if (spell->Id == SPELL_SOULREND)
            me->SummonCreature(NPC_SOULREND, target->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0);
    }

    void Reset() override
    {
        summons.DespawnAll();
        events.Reset();
    }

    void EnterCombat(Unit* who) override
    {

        //Talk(TALK_AGGRO);
        // Events
        events.ScheduleEvent(EVENT_WRACKING_PAIN, 3500);
        events.ScheduleEvent(EVENT_SKEWER, 5000);
        events.ScheduleEvent(EVENT_SOULREND, 10000);
        events.ScheduleEvent(EVENT_ECHOES_OF_SHADOW, 16900);

        BossAI::EnterCombat(who);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SOULREND:
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                me->CastSpell(target, SPELL_SOULREND);
                events.ScheduleEvent(EVENT_WRACKING_PAIN, 41400);
                break;
            }
            case EVENT_WRACKING_PAIN:
            {
                //Doesn't cast this on the tank
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                me->CastSpell(target, SPELL_WRACKING_PAIN);
                events.ScheduleEvent(EVENT_WRACKING_PAIN, urand (17000, 23000));
                break;
            }
            case EVENT_SKEWER:
            {
                me->CastSpell(me->GetVictim(), SPELL_SKEWER);
                events.ScheduleEvent(EVENT_SKEWER, 32800);
                break;
            }
            case EVENT_ECHOES_OF_SHADOW:
            {
                me->CastSpell(me->GetVictim(), SPELL_ECHOES_OF_SHADOW);
                events.ScheduleEvent(EVENT_ECHOES_OF_SHADOW, 12000);
                break;
            }
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }


    void JustDied(Unit* killer) override
    {
        //Talk(TALK_DEATH);
        summons.DespawnAll();
        BossAI::JustDied(killer);
    }

private:
};

struct npc_ataldazar_soulspawn : public ScriptedAI
{
    npc_ataldazar_soulspawn(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset() override
    {
        events.Reset();
        me->setActive(false);
        if (Creature* yazma = me->FindNearestCreature(NPC_YAZMA, 100))
            me->GetMotionMaster()->MoveFollow(yazma, 0, 0);
    }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovement(false);
        ScriptedAI::InitializeAI();
    }

    void DamageTaken(Unit* /*who*/, uint32& damage) override
    {
    }

    void UpdateAI(uint32 diff) override
    {
        if (Creature* yazma = me->FindNearestCreature(NPC_YAZMA, 100))
            if (me->GetDistance(yazma) < 1)
            {
                me->CastSpell(me, SPELL_SOULREND_EXPLODE);
                me->ForcedDespawn();
            }
    }
};

struct npc_ataldazar_echo_of_shadra : public ScriptedAI
{
    npc_ataldazar_echo_of_shadra(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset() override
    {
        events.Reset();
        me->setActive(false);
        me->SetWalk(false);
        me->GetMotionMaster()->MoveRandom(urand(0, 15));

        //need to check the chance
        int chance = urand(0, 3);
        if (chance == 2)
            me->AddAura(SPELL_ECHOES_OF_SHADOW_EMPOWERED);
    }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovement(false);
        ScriptedAI::InitializeAI();
    }

    void DamageTaken(Unit* /*who*/, uint32& damage) override
    {
    }

    void MovementInform(uint32 type, uint32 id) override
    {
            me->GetMotionMaster()->MoveRandom(urand(5, 15));
    }

    void UpdateAI(uint32 diff) override
    {
        if (Player* closestplayer = me->SelectNearestPlayer(50))
            if (me->GetDistance(closestplayer) < 1)
            {
                me->CastSpell(me, SPELL_ECHOES_OF_SHADOW_AREATRIGGER);
                me->KillSelf();
            }
    }
};


void AddSC_boss_yazma()
{
    RegisterCreatureAI(boss_ataldazar_yazma);
    RegisterCreatureAI(npc_ataldazar_soulspawn);
    RegisterCreatureAI(npc_ataldazar_echo_of_shadra);
}
