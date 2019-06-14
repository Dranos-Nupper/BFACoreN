/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
 * Copyright (C) 2016 Firestorm Servers <https://firestorm-servers.com>
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
#include "ObjectMgr.h"
#include "ScriptMgr.h"

enum ScriptedTextsChiJi
{
    SAY_CHI_JI_AGGRO = 0,
    SAY_CHI_JI_DEATH = 1,
    SAY_CHI_JI_INTRO = 2,
    SAY_CHI_JI_KILL = 3,
    SAY_CHI_JI_SPELL_1 = 4,
    SAY_CHI_JI_SPELL_2 = 5,
};

enum SpellsChiJi
{
    SPELL_INSPIRING_SONG = 144468,

    SPELL_FIRESTORM_SUMMON = 144461,
    SPELL_FIRESTORM_AURA = 144463,
    SPELL_FIRESTORM_DMG = 144462,

    SPELL_BEACON_OF_HOPE_SUMMON = 144473,
    SPELL_BEACON_OF_HOPE_AURA = 144474,
    SPELL_BEACON_OF_HOPE_BUFF = 144475,

    SPELL_BLAZING_SONG = 144471,
    SPELL_BLAZING_SONG_DMG = 144472,

    SPELL_CRANE_RUSH = 144470,
    SPELL_CRANE_RUSH_SUMMON = 144495,

    SPELL_BLAZING_NOVA = 144493,
    SPELL_BLAZING_NOVA_DMG = 144494,
};

enum Events
{
    EVENT_INSPIRING_SONG,
    EVENT_FIRESTORM,
    EVENT_BEACON_OF_HOPE,
    EVENT_BLAZING_SONG,
    EVENT_CRANE_RUSH,
};

enum Creatures
{

};

struct npc_celestial_challenge_chi_ji : public ScriptedAI
{
    npc_celestial_challenge_chi_ji(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        m_NextSpellBlazingSong = false;
        m_FirstCraneRushDone = false;
        m_SecondCraneRushDone = false;
    }

    void EnterCombat(Unit* who)
    {
        Talk(SAY_CHI_JI_AGGRO);

        events.ScheduleEvent(EVENT_INSPIRING_SONG, 20000);
        events.ScheduleEvent(EVENT_FIRESTORM, urand(15000, 25000));
        events.ScheduleEvent(EVENT_BEACON_OF_HOPE, urand(30000, 40000));
    }

    void KilledUnit(Unit* who)
    {
        if (who && who->IsPlayer())
        {
            Talk(SAY_CHI_JI_KILL);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (CraneRush())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
        }

        DoMeleeAttackIfReady();
    }

    void ExecuteEvent(const uint32 eventId)
    {
        if (m_NextSpellBlazingSong && eventId != EVENT_BLAZING_SONG)
        {
            events.RescheduleEvent(eventId, urand(1000, 3000));
            return;
        }

        switch (eventId)
        {
        case EVENT_INSPIRING_SONG:
            DoCast(SPELL_INSPIRING_SONG);
            events.ScheduleEvent(EVENT_INSPIRING_SONG, 30000);
            break;
        case EVENT_FIRESTORM:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 15.0f, true))
            {
                DoCast(target, SPELL_FIRESTORM_SUMMON);
            }
            events.ScheduleEvent(EVENT_FIRESTORM, urand(25000, 30000));
            break;
        case EVENT_BEACON_OF_HOPE:
            Talk(SAY_CHI_JI_SPELL_1);
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
            {
                DoCast(target, SPELL_BEACON_OF_HOPE_SUMMON);
            }
            m_NextSpellBlazingSong = true;
            events.ScheduleEvent(EVENT_BEACON_OF_HOPE, 60000);
            events.ScheduleEvent(EVENT_BLAZING_SONG, 1);
            break;
        case EVENT_BLAZING_SONG:
            m_NextSpellBlazingSong = false;
            DoCast(me, SPELL_BLAZING_SONG);
            break;
        }
    }

protected:

    virtual void CompleteChallenge()
    {
        Talk(SAY_CHI_JI_DEATH);

        me->DespawnOrUnsummon(5000);
    }

private:

    bool CraneRush()
    {
        if (!m_FirstCraneRushDone && me->GetHealthPct() <= 66.0f)
        {
            m_FirstCraneRushDone = true;

            Talk(SAY_CHI_JI_SPELL_2);

            DoCast(SPELL_CRANE_RUSH);
            return true;
        }

        if (!m_SecondCraneRushDone && me->GetHealthPct() <= 33.0f)
        {
            m_SecondCraneRushDone = true;

            Talk(SAY_CHI_JI_SPELL_2);

            DoCast(SPELL_CRANE_RUSH);
            return true;
        }

        return false;
    }

private:

    bool m_NextSpellBlazingSong;
    bool m_FirstCraneRushDone;
    bool m_SecondCraneRushDone;
};

struct npc_celestial_challenge_chi_ji_firestorm : public ScriptedAI
{
    npc_celestial_challenge_chi_ji_firestorm(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
        me->SetReactState(REACT_PASSIVE);
        me->AddAura(SPELL_FIRESTORM_AURA, me);
    }

    void IsSummonedBy(Unit* owner)
    {
        me->GetMotionMaster()->MoveRandom(5.0f);
    }
};

struct npc_celestial_challenge_chi_ji_becon_of_hope : public ScriptedAI
{
    npc_celestial_challenge_chi_ji_becon_of_hope(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
        me->SetReactState(REACT_PASSIVE);
        me->AddAura(SPELL_BEACON_OF_HOPE_AURA, me);
    }

    // prevents evade mode
    void EnterEvadeMode(EvadeReason /*why*/) { }
};

struct npc_celestial_challenge_chi_ji_child : public ScriptedAI
{
    npc_celestial_challenge_chi_ji_child(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        me->AddAura(SPELL_BLAZING_NOVA, me);
    }
};

class spell_celestial_challenge_chi_ji_blazing_song: public SpellScriptLoader
{
    public:
        spell_celestial_challenge_chi_ji_blazing_song() : SpellScriptLoader("spell_celestial_challenge_chi_ji_blazing_song") { }

        class spell_celestial_challenge_chi_ji_blazing_song_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_celestial_challenge_chi_ji_blazing_song_SpellScript);

            

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                for (WorldObject* target : targets)
                {
                    if (target->ToUnit())
                        if (target->GetAreaId() == caster->GetAreaId())
                            targets.remove(target);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_celestial_challenge_chi_ji_blazing_song_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_celestial_challenge_chi_ji_blazing_song_SpellScript();
        }
};

void AddSC_boss_chi_ji()
{
    RegisterCreatureAI(npc_celestial_challenge_chi_ji);
    RegisterCreatureAI(npc_celestial_challenge_chi_ji_firestorm);
    RegisterCreatureAI(npc_celestial_challenge_chi_ji_becon_of_hope);
    RegisterCreatureAI(npc_celestial_challenge_chi_ji_child);
    new spell_celestial_challenge_chi_ji_blazing_song();        // 144472
}
