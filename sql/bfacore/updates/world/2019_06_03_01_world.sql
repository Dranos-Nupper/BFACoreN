DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_warr_execute_default' AND `spell_id`='5308';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(5308, 'spell_warr_execute_default');
DELETE FROM `spell_script_names` WHERE `spell_id` = '5308' AND `ScriptName` = ''; 