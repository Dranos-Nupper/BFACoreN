UPDATE `creature_template` SET `npcflag`=`npcflag`|1|2|128 WHERE `entry` = 130216;

DELETE FROM `npc_vendor` WHERE `entry` = '130216';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`, `PlayerConditionID`) VALUES
('130216', '16', '160537', '0', '0', '0', '1', '0'),
('130216', '19', '160544', '0', '0', '0', '1', '0'),
('130216', '1', '161555', '0', '0', '0', '1', '0'),
('130216', '5', '161557', '0', '0', '0', '1', '0'),
('130216', '3', '161560', '0', '0', '0', '1', '0'),
('130216', '1', '161563', '0', '0', '0', '1', '0'),
('130216', '0', '163515', '0', '0', '0', '1', '0'),
('130216', '0', '163555', '0', '0', '0', '1', '0');


DELETE FROM `spell_script_names` WHERE `spell_id` IN (274281,274282,274283,164812,164815,202342,279621,279709,78674,274837);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (274281, 'spell_dru_newmoon');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (274282, 'spell_dru_newmoon');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (274283, 'spell_dru_newmoon');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (164812, 'spell_dru_shooting_stars_proc');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (164815, 'spell_dru_shooting_stars_proc');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (202342, 'spell_dru_shooting_stars_proc');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (279621, 'spell_dru_twin_moon');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (279709, 'spell_dru_starlord');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (78674, 'spell_dru_starsurge');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (274837, 'spell_dru_feral_frenzy');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (5308);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (5308, 'spell_warr_execute_default');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (118779);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (118779, 'spell_warr_victory_rush_heal');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (202168);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (202168, 'spell_warr_impending_victory');

UPDATE `playercreateinfo` SET `orientation`= 0 WHERE `race`= 2 AND `class` IN (1, 3, 4, 7, 8, 9, 10);

DELETE FROM `creature_queststarter` WHERE `id` = 2077 AND `quest` = 28713;
INSERT INTO `creature_queststarter` VALUES
(2077, 28713);

DELETE FROM `creature_questender` WHERE `id` = 2077 AND `quest` = 28713;
INSERT INTO `creature_questender` VALUES
(2077, 28713);
