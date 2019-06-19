
UPDATE `creature` SET `equipment_id`='1' WHERE `id` IN(SELECT `CreatureID` FROM `creature_equip_template` WHERE `ID`='1');


