DELETE FROM `spell_script_names` WHERE `spell_id` IN (408,154953,137619);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (408, 'spell_rog_internal_bleeding');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (154953, 'spell_rog_internal_bleeding_damage');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (137619, 'spell_rog_marked_for_death');

DELETE FROM `spell_script_names` WHERE spell_id = 703;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (703, 'spell_rog_garrote');

