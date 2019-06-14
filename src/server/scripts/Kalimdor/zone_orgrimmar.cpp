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

#include "GameObject.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "LFGMgr.h"
#include "SceneHelper.h"

enum OrgrimmarQuests
{
    QUEST_MISSION_ORDERS                    = 51443,
    QUEST_STORMWIND_EXTRACTION              = 50769,

    OBJECTIVE_STORMWIND_EXTRACTION_POTION   = 333785,
};

enum OrgrimmarGameObjects
{
    GOB_BLIGHTCALLER_EASY_DEATH = 289645
};

enum OrgrimmarQuestObjectives
{
    OBJECTIVE_MISSION_ORDERS_TAlk_SYLVANAS  = 335883,
};

enum OrgrimmarSpells
{
    SPELL_SCENE_SECRET_WEAPON   = 281294,
    SPELL_TALK_TO_SYLVANAS_KC   = 265586,

    // invisibility_detection_27 100616
    SPELL_START_SE_SCENARIO     = 265595,
};

enum OrgrimmarConversations
{
    CONVERSATION_MISSION_STATEMENT_ALL_HERE     = 7170,
    CONVERSATION_STORMWIND_EXTRACTION_LETS_MOVE = 8399,
};

 // 135201 - Talk to Sylvanas
struct npc_orgri_mission_orders_speak_sylvanas : public ScriptedAI
{
    npc_orgri_mission_orders_speak_sylvanas(Creature* creature) : ScriptedAI(creature) { }

    void MoveInLineOfSight(Unit* unit) override
    {
        if (Player* player = unit->ToPlayer())
            if (player->GetQuestStatus(QUEST_MISSION_ORDERS) == QUEST_STATUS_INCOMPLETE)
                if (player->GetQuestObjectiveCounter(OBJECTIVE_MISSION_ORDERS_TAlk_SYLVANAS) == 0)
                    if (player->GetDistance(me) < 40.f)
                        player->CastSpell(player, SPELL_SCENE_SECRET_WEAPON);
    }
};

// 2136
class scene_orgri_secret_weapon : public SceneScript
{
public:
    scene_orgri_secret_weapon() : SceneScript("scene_orgri_secret_weapon") { }

    void OnSceneEnd(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        player->CastSpell(player, SPELL_TALK_TO_SYLVANAS_KC, true);
    }
};

// 134202 - Meet your team
struct  npc_orgri_mission_orders_meet_team : public ScriptedAI
{
    npc_orgri_mission_orders_meet_team(Creature* creature) : ScriptedAI(creature) { }

    void MoveInLineOfSight(Unit* unit) override
    {
        if (Player* player = unit->ToPlayer())
            if (player->GetQuestStatus(QUEST_MISSION_ORDERS) == QUEST_STATUS_INCOMPLETE)
                if (player->GetQuestObjectiveCounter(OBJECTIVE_MISSION_ORDERS_TAlk_SYLVANAS) == 1)
                    if (player->GetDistance(me) < 5.0f)
                    {
                        player->PlayConversation(CONVERSATION_MISSION_STATEMENT_ALL_HERE);
                        KillCreditMe(player);
                    }
    }
};

// 135205 - Nathanos (At team meeting)
struct  npc_nathanos_team_meeting : public ScriptedAI
{
    npc_nathanos_team_meeting(Creature* creature) : ScriptedAI(creature) { }

    void sQuestAccept(Player* player, Quest const* /*quest*/) override
    {
        Talk(0);
        player->SummonGameObject(GOB_BLIGHTCALLER_EASY_DEATH, 1577.965f, -4455.622f, 16.55939f, 0.f, QuaternionData(0.f, 0.f, 0.f, 1.f), 0, true);
    }
};

// 50769
struct quest_stormwind_extraction : public QuestScript
{
    quest_stormwind_extraction() : QuestScript("quest_stormwind_extraction") { }

    // Called when a quest objective data change
    void OnQuestObjectiveChange(Player* player, Quest const* /*quest*/, QuestObjective const& objective, int32 /*oldAmount*/, int32 /*newAmount*/) override
    {
        if (objective.ID == OBJECTIVE_STORMWIND_EXTRACTION_POTION)
            player->PlayConversation(CONVERSATION_STORMWIND_EXTRACTION_LETS_MOVE);
    }
};

// 135211 - Stormwind Extraction skyhorn eagle
struct npc_skyhorn_eagle : public ScriptedAI
{
    npc_skyhorn_eagle(Creature* creature) : ScriptedAI(creature) { }

    void OnSpellClick(Unit* clicker, bool& result) override
    {
        Player* player = clicker->ToPlayer();
        if (!player || player->GetQuestStatus(QUEST_STORMWIND_EXTRACTION) != QUEST_STATUS_INCOMPLETE)
        {
            result = false;
            return;
        }

        KillCreditMe(player);
        player->CastSpell(player, SPELL_START_SE_SCENARIO);
    }
};

//todo add missing cinematic
class spell_waters_of_farseeing_94687 : public SpellScriptLoader
{
public:
    spell_waters_of_farseeing_94687() : SpellScriptLoader("spell_waters_of_farseeing_94687") { }

    class spell_waters_of_farseeing_94687_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_waters_of_farseeing_94687_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
        {
            if (Unit* caster = GetCaster())
                if (Player* player = caster->ToPlayer())
                    if (player->GetQuestStatus(28805) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(28826) == QUEST_STATUS_INCOMPLETE)
                        player->KilledMonsterCredit(50054);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_waters_of_farseeing_94687_AuraScript::OnApply, EFFECT_0, SPELL_AURA_SCREEN_EFFECT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_waters_of_farseeing_94687_AuraScript();
    }
};

// 79545 - Inspection
class spell_quest_inspection : public SpellScript
{
    PrepareSpellScript(spell_quest_inspection);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Creature* demolisher = caster->FindNearestCreature(42673, 10.0f);
        Creature* engineer = caster->FindNearestCreature(42671, 10.0f);

        if (!demolisher || !engineer)
            return;

        if (engineer->GetPositionZ() > 130)
        {
            engineer->AI()->Talk(1);
        }
        else if (engineer->GetPositionZ() > 126.5)
        {
            engineer->AI()->Talk(3);
        }
        else
        {
            demolisher->KillSelf();
            engineer->AI()->Talk(5);
            engineer->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            if (Player* player = caster->ToPlayer())
                player->KilledMonsterCredit(42674);
        }

    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_quest_inspection::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class areatrigger_demolisher_orgrimmar : public AreaTriggerScript
{
public:

    areatrigger_demolisher_orgrimmar() : AreaTriggerScript("areatrigger_demolisher_orgrimmar") { }

    enum Quest
    {
        QUEST_WEAPONS_OF_MASS_DYSFUNCTION = 26294,
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* at, bool /*entered*/) override
    {
        if (!player->HasQuest(QUEST_WEAPONS_OF_MASS_DYSFUNCTION))
            return false;

        switch (at->ID)
        {
        case 5995:
            if (Creature* engineer = GetClosestCreatureWithEntry(player, 42671, 10.0f, true))
                engineer->AI()->Talk(0);
            break;
        case 5996:
            if (Creature* engineer = GetClosestCreatureWithEntry(player, 42671, 10.0f, true))
                engineer->AI()->Talk(2);
            break;
        case 5997:
            if(Creature* engineer = GetClosestCreatureWithEntry(player, 42671, 10.0f, true))
                engineer->AI()->Talk(4);
            break;
        default:
            break;
        }

        return false;
    }
};

class npc_orgrimmar_isabella : public CreatureScript
{
public:
    npc_orgrimmar_isabella() : CreatureScript("npc_orgrimmar_isabella") { }


    enum ScenarioLfgIds
    {
        scenario_battle_for_lordaeron_horde_id = 1759,
    };

    enum Credits
    {
        npc_credit_id = 139178,
    };

    // moved to gossip hello for testing
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        newDungeons.insert(ScenarioLfgIds::scenario_battle_for_lordaeron_horde_id);
        sLFGMgr->JoinLfg(player, ROLE_DAMAGE, newDungeons);

        player->KilledMonsterCredit(Credits::npc_credit_id);
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction) override
    {
        newDungeons.clear();
        switch (uiAction)
        {
            newDungeons.insert(ScenarioLfgIds::scenario_battle_for_lordaeron_horde_id);
            sLFGMgr->JoinLfg(player, ROLE_DAMAGE, newDungeons);

            player->KilledMonsterCredit(Credits::npc_credit_id);
            break;
        default:
            break;

        }
        return true;
    }
private:
    lfg::LfgDungeonSet newDungeons;
};

// 44160
struct npc_suspicious_peon : public ScriptedAI
{
    npc_suspicious_peon(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    enum NpcIds
    {
        NPC_SAURANOK = 44120,
    };

    enum KillCredits
    {
        NPC_TALK_CREDIT = 44132,
    };

    void sGossipSelect(Player* player, uint32 menuId, uint32 /*gossipListId*/)
    {
        /*if (menuId < 11807)
        {
            player->PlayerTalkClass->SendGossipMenu(menuId + 1, me->GetGUID());
        }*/
        if (menuId == 11807)
        {
            //remove gossip
            me->RemoveFlag(UNIT_NPC_FLAGS, 1);
            me->SummonCreature(NPC_SAURANOK, 1735.44f, -4284.23f, 101.413f);
            player->KilledMonsterCredit(NPC_TALK_CREDIT);
            player->PlayerTalkClass->SendCloseGossip();
        }
    }
};

// 44120
struct npc_sauranok : public ScriptedAI
{
    npc_sauranok(Creature* pCreature) : ScriptedAI(pCreature), sceneHelper(pCreature->GetGUID(), pCreature->GetMap())
    {
    }

    enum Events
    {
        EVENT_VENGEFULL_STRIKE = 1,
    };

    enum Spells
    {
        SPELL_KILL_PEON = 82611,
        SPELL_ENVELOPING_DARKNESS = 82531,
        SPELL_VENGEFULL_STRIKE = 82611,
        SPELL_VISUAL = 82545, // target
    };

    void EnterCombat(Unit* victim)
    {
        healed = false;
        events.ScheduleEvent(EVENT_VENGEFULL_STRIKE, 5000);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        me->GetMotionMaster()->MovePath(4412000, false);
        sceneHelper.Clear();

        // fix spell target selection
        sceneHelper.AddSceneActionCastTarget(SPELL_KILL_PEON, true, summoner, 2400);
        sceneHelper.AddSceneActionTalk(0, 1);
        sceneHelper.AddSceneActionTalk(1, 1300);
        sceneHelper.AddSceneActionAI(1, 400);
        sceneHelper.AddSceneActionRemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC, 400);

        sceneHelper.Activate();
    }

    void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/) override
    {
        if (me->GetHealthPct() <= 50 && !healed)
        {
            //todo add flying
            DoCastSelf(SPELL_ENVELOPING_DARKNESS);
            Talk(2);
            healed = true;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        sceneHelper.UpdateSceneHelper(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_VENGEFULL_STRIKE:
                DoCastVictim(SPELL_VENGEFULL_STRIKE);
                events.ScheduleEvent(EVENT_VENGEFULL_STRIKE, 8000);
                break;
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
private:
    SceneHelper sceneHelper;
    bool healed;
};


void AddSC_orgrimmar()
{
    RegisterCreatureAI(npc_orgri_mission_orders_speak_sylvanas);
    RegisterSceneScript(scene_orgri_secret_weapon);
    RegisterCreatureAI(npc_orgri_mission_orders_meet_team);
    RegisterCreatureAI(npc_nathanos_team_meeting);
    RegisterQuestScript(quest_stormwind_extraction);
    RegisterCreatureAI(npc_skyhorn_eagle);
    new spell_waters_of_farseeing_94687();
    RegisterSpellScript(spell_quest_inspection);
    new areatrigger_demolisher_orgrimmar();
    new npc_orgrimmar_isabella();
    RegisterCreatureAI(npc_suspicious_peon);
    RegisterCreatureAI(npc_sauranok);
}
