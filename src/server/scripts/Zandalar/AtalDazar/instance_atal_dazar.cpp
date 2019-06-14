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
#include "Player.h"
#include "InstanceScript.h"
#include "atal_dazar.h"

struct instance_atal_dazar : public InstanceScript
{
    instance_atal_dazar(InstanceMap* map) : InstanceScript(map)
    {
        SetHeaders(DataHeader);
        SetBossNumber(EncounterCount);
    }

    void OnCreatureCreate(Creature* creature) override
    {
        switch (creature->GetEntry())
        {
        case NPC_PRIESTESS_ALUNZA:
            PriestressGUID = creature->GetGUID();
            break;
        default:
            break;
        }
    };

    ObjectGuid GetGuidData(uint32 type) const override
    {
        switch (type)
        {
        case DATA_PRIESTESS_ALUNZA:
            return PriestressGUID;
        default:
            break;
        }
        return ObjectGuid::Empty;
    }

protected:
    ObjectGuid PriestressGUID;
};

void AddSC_instance_atal_dazar()
{
    RegisterInstanceScript(instance_atal_dazar, 1763);
}
