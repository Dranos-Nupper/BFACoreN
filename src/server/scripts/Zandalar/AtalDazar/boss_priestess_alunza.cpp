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

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "atal_dazar.h"

enum PriestessAlunzaSpells : uint32
{
    SPELL_PRE_RITUAL                    = 258386,

    SPELL_ENERGY_REGEN                  = 258681,
    SPELL_GILDED_CLAWS                  = 255579,
    SPELL_GILDED_CLAWS_TRIGGER_SPELL    = 255581,
    SPELL_TRANSFUSION                   = 260666,
    SPELL_TRANSFUSION_PERIODIC_DUMMY    = 260665,
    SPELL_TRANSFUSION_DAMAGE            = 260667,
    SPELL_TRANSFUSION_HEAL              = 260668,
    SPELL_TAINTED_BLOOD_DOT             = 255558,
    SPELL_TAINTED_BLOOD_TARGET_CAULDRON = 255592,
    SPELL_TAINTED_BLOOD_MISSILE_BUBBLE  = 260660, // TARGET_DEST_DEST
    SPELL_TAINTED_BLOOD_CREATE_AT       = 260670,

    SPELL_MOLTEN_GOLD_POOL_PRE_SELECTOR = 255615,
    SPELL_MOLTEN_GOLD_POOL_SELECTOR     = 255591,
    SPELL_MOLTEN_GOLD_TARGET_SELECT     = 255584,
    SPELL_MOLTEN_GOLD_MISSILE           = 255583,
    SPELL_MOLTEN_GOLD_DOT               = 255582,

    SPELL_CORRUPTED_GOLD_TOUCH          = 258709,
    SPELL_CORRUPTED_GOLD_AT             = 258703
};

enum PriestessAlunzaTalks : uint8
{
    TALK_AGGRO              = 0,
    TALK_GILDED_CLAWS_EMOTE = 1,
    TALK_GILDED_CLAWS       = 2,
    TALK_TRANSFUSION_EMOTE  = 3,
    TALK_TRANSFUSION        = 4,
    TALK_MOLTEN_GOLD        = 5,
    TALK_DEATH              = 6
};

enum PriestessAlunzaEvents : uint8
{
    EVENT_GILDED_CLAWS          = 1,
    EVENT_TRANSFUSION           = 2,
    EVENT_MOLTEN_GOLD           = 3,
    EVENT_TAINTED_BLOOD         = 4,
    EVENT_SPAWN_CORRUPTED_GOLD  = 5
};

enum PriestessAlunzaNPCs : uint32
{
    NPC_BLOOD_TAINTED_CAULDRON  = 128956,
    NPC_CORRUPTED_GOLD          = 130738
};

enum PriestessMisc : uint32
{
    OUT_OF_COMBAT_ANIM_ID       = 1346
};

// 122967 - Priestess Alunza
struct boss_priestess_alunza : public BossAI
{
    boss_priestess_alunza(Creature* creature) : BossAI(creature, DATA_PRIESTESS_ALUNZA) { }

    void InitializeAI() override
    {
        me->SetMaxPower(POWER_MANA, 100);
        me->SetPower(POWER_MANA, 0);
        scheduler.ClearValidator();
        taintedCounter = 0;
        BossAI::InitializeAI();
    }

    void Reset() override
    {
        AreaTriggerList areatriggers = me->SelectNearestAreaTriggers(SPELL_TAINTED_BLOOD_CREATE_AT, 100.f);
        for (AreaTrigger* at : areatriggers)
            at->Remove();

        taintedCounter = 0;

        events.Reset();
        scheduler.CancelAll();
        summons.DespawnAll();

        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        me->SetPower(POWER_MANA, 0);
        DoCastSelf(SPELL_PRE_RITUAL);
        BossAI::Reset();
    }

    void EnterCombat(Unit* who) override
    {
        Talk(TALK_AGGRO);
        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        events.ScheduleEvent(EVENT_GILDED_CLAWS, 10500);
        events.ScheduleEvent(EVENT_MOLTEN_GOLD, 16500);
        events.ScheduleEvent(EVENT_TAINTED_BLOOD, 2000);
        if (IsMythic() || IsHeroic())
        {
            events.ScheduleEvent(EVENT_SPAWN_CORRUPTED_GOLD, 2000);
            // Last event to add: Spawn add
        }

        me->RemoveAurasDueToSpell(SPELL_PRE_RITUAL);
        DoCastSelf(SPELL_ENERGY_REGEN, true);

        BossAI::EnterCombat(who);
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        _DespawnAtEvade();
        BossAI::EnterEvadeMode(why);
    }

    void JustDied(Unit* killer) override
    {
        Talk(TALK_DEATH);
        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        BossAI::JustDied(killer);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);
        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (me->GetPower(POWER_MANA) >= 100 && !events.HasEvent(EVENT_TRANSFUSION))
            events.ScheduleEvent(EVENT_TRANSFUSION, 5000);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_GILDED_CLAWS:
                    Talk(TALK_GILDED_CLAWS);
                    Talk(TALK_GILDED_CLAWS_EMOTE);
                    DoCastSelf(SPELL_GILDED_CLAWS);
                    events.ScheduleEvent(EVENT_GILDED_CLAWS, 34000);
                    break;
                case EVENT_MOLTEN_GOLD:
                    Talk(TALK_MOLTEN_GOLD);
                    DoCastSelf(SPELL_MOLTEN_GOLD_POOL_PRE_SELECTOR, true);
                    events.ScheduleEvent(EVENT_MOLTEN_GOLD, 34000);
                    break;
                case EVENT_TRANSFUSION:
                    Talk(TALK_TRANSFUSION);
                    Talk(TALK_TRANSFUSION_EMOTE);
                    DoCast(SPELL_TRANSFUSION);
                    taintedCounter = 0;
                    events.ScheduleEvent(EVENT_TAINTED_BLOOD, 9000);
                    break;
                case EVENT_TAINTED_BLOOD:
                    DoCastSelf(SPELL_TAINTED_BLOOD_TARGET_CAULDRON, true);
                    ++taintedCounter;
                    if (taintedCounter < 5)
                        events.ScheduleEvent(EVENT_TAINTED_BLOOD, urand(2000, 4000));
                    break;
                case EVENT_SPAWN_CORRUPTED_GOLD:
                {
                    scheduler.Schedule(0s, [this](TaskContext context)
                    {
                        // For this, there is no searcher spell blizz pls
                        for (Creature* cauldron : me->FindNearestCreatures(NPC_BLOOD_TAINTED_CAULDRON, 100.f))
                            DoSummon(NPC_CORRUPTED_GOLD, cauldron->GetPosition(), 40000, TEMPSUMMON_TIMED_DESPAWN);
                        context.Repeat(std::chrono::milliseconds(3500));
                    });
                    break;
                }
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    TaskScheduler scheduler;
    int8 taintedCounter;
};

enum CauldronSpells : uint32
{
    SPELL_TAINTED_BLOOD_CAULDRON_AURA = 255619,
    SPELL_TAINTED_BLOOD_CAULDRON_PURIFY = 260658
};

// 128956 - Blood Tainted Cauldron
struct npc_blood_tainted_cauldron : public ScriptedAI
{
    npc_blood_tainted_cauldron(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovement(false);
        ScriptedAI::InitializeAI();
    }

    void Reset() override
    {
        DoCastSelf(SPELL_TAINTED_BLOOD_CAULDRON_AURA);
        ScriptedAI::Reset();
    }

    void UpdateAI(uint32 diff) override
    {
        // Do nothing
        ScriptedAI::UpdateAI(diff);
    }

    void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_MOLTEN_GOLD_POOL_SELECTOR)
            DoCastSelf(SPELL_TAINTED_BLOOD_CAULDRON_PURIFY);
    }
};

// 130738 - Corrupted Gold
struct npc_corrupted_gold : public ScriptedAI
{
    npc_corrupted_gold(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovement(false);
        ScriptedAI::InitializeAI();
    }

    void Reset() override
    {
        DoCastSelf(SPELL_CORRUPTED_GOLD_AT);
        MoveForward(70.0f);
        ScriptedAI::Reset();
    }

    void MoveForward(float distance)
    {
        Position movePos;
        float ori = M_PI_2 + M_PI + frand(0.f, M_PI);
        float x = me->GetPositionX() + distance * cos(ori);
        float y = me->GetPositionY() + distance * sin(ori);
        float z = me->GetPositionZ();
        me->GetNearPoint2D(x, y, distance, ori);
        movePos = { x, y, z, ori };
        me->GetMotionMaster()->MovePoint(0, movePos, false);
    }

    void UpdateAI(uint32 diff) override
    {
        ScriptedAI::UpdateAI(diff);
    }
};

// 255575 - Tranfusion Damage
class spell_priestess_tranfusion_damage : public SpellScript
{
    PrepareSpellScript(spell_priestess_tranfusion_damage);

    void DoEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* hitUnit = GetHitUnit())
        {
            if (hitUnit->HasAura(SPELL_TAINTED_BLOOD_DOT))
                GetCaster()->CastSpell(hitUnit, SPELL_TRANSFUSION_DAMAGE, true);
            else
                GetCaster()->CastSpell(hitUnit, SPELL_TRANSFUSION_HEAL, true);
        }
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        // Nothing, yet...
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_priestess_tranfusion_damage::DoEffectHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_priestess_tranfusion_damage::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

// 255577 - Transfusion
class spell_priestess_transfusion : public AuraScript
{
    PrepareAuraScript(spell_priestess_transfusion);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->CastSpell(GetTarget(), SPELL_ENERGY_REGEN, true);
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->SetPower(POWER_MANA, 0);
    }
    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_priestess_transfusion::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectApply += AuraEffectApplyFn(spell_priestess_transfusion::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 258681 - Boss Energy Regen
class spell_priestess_energy_regen : public AuraScript
{
    PrepareAuraScript(spell_priestess_energy_regen);

    void OnPeriodic(AuraEffect const* aurEff)
    {
        GetTarget()->ModifyPower(POWER_MANA, aurEff->GetAmount() / 10);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_priestess_energy_regen::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 260658 - Cauldron Purify
class spell_npc_cauldron_purify : public AuraScript
{
    PrepareAuraScript(spell_npc_cauldron_purify);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        GetTarget()->CastSpell(GetTarget(), SPELL_MOLTEN_GOLD_TARGET_SELECT, true);
        GetAura()->Remove();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_npc_cauldron_purify::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 255592 - Pool Pre Tainted Selector
class spell_priestess_pool_tainted_selector : public SpellScript
{
    PrepareSpellScript(spell_priestess_pool_tainted_selector);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* obj) { return obj->GetEntry() != NPC_BLOOD_TAINTED_CAULDRON; });
        Trinity::Containers::RandomResize(targets, 1);
    }

    void DoEffectHitTarget(SpellEffIndex effIndex)
    {
        if (Unit* hitUnit = GetHitUnit())
            if (UnitAI* ai = GetCaster()->GetAI()) //@HACK TODO
                if (Unit* target = ai->SelectTarget(SELECT_TARGET_RANDOM, 0))
                    hitUnit->CastSpell(target, SPELL_TAINTED_BLOOD_MISSILE_BUBBLE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_priestess_pool_tainted_selector::DoEffectHitTarget, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_priestess_pool_tainted_selector::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
    }
};

// 255615 - Pool Pre Selector
class spell_priestess_pool_pre_selector : public SpellScript
{
    PrepareSpellScript(spell_priestess_pool_pre_selector);

    void DoEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* hitUnit = GetHitUnit())
            GetCaster()->CastSpell(hitUnit, SPELL_MOLTEN_GOLD_POOL_SELECTOR);
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* obj) { return obj->GetEntry() != NPC_BLOOD_TAINTED_CAULDRON; });
        Trinity::Containers::RandomResize(targets, 1);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_priestess_pool_pre_selector::DoEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_priestess_pool_pre_selector::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
    }
};

// 255584 - Molten Gold Target Selector
class spell_priestess_alunza_molten_gold : public SpellScript
{
    PrepareSpellScript(spell_priestess_alunza_molten_gold);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        std::list<WorldObject*> originalTargets = targets;
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MOLTEN_GOLD_DOT));
        if (targets.empty())
            targets = originalTargets;
    }

    void DoEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* hitUnit = GetHitUnit())
            if (InstanceScript* atalDazarScript = GetCaster()->GetInstanceScript())
                GetCaster()->CastSpell(hitUnit, SPELL_MOLTEN_GOLD_MISSILE, true, nullptr, nullptr, atalDazarScript->GetGuidData(DATA_PRIESTESS_ALUNZA));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_priestess_alunza_molten_gold::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_priestess_alunza_molten_gold::DoEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Tainted Blood - 260670
// at 12369
struct at_priestess_alunza_tainted_blood : AreaTriggerAI
{
    at_priestess_alunza_tainted_blood(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
            {
                caster->CastSpell(unit, SPELL_TAINTED_BLOOD_DOT, true);
                at->Remove();
            }
    }
};

void AddSC_boss_priestess_alunza()
{
    RegisterAreaTriggerAI(at_priestess_alunza_tainted_blood);

    RegisterCreatureAI(npc_corrupted_gold);
    RegisterCreatureAI(boss_priestess_alunza);
    RegisterCreatureAI(npc_blood_tainted_cauldron);

    RegisterSpellScript(spell_priestess_alunza_molten_gold);
    RegisterAuraScript(spell_npc_cauldron_purify);
    RegisterAuraScript(spell_priestess_energy_regen);
    RegisterAuraScript(spell_priestess_transfusion);
    RegisterSpellScript(spell_priestess_tranfusion_damage);
    RegisterSpellScript(spell_priestess_pool_pre_selector);
    RegisterSpellScript(spell_priestess_pool_tainted_selector);
}
