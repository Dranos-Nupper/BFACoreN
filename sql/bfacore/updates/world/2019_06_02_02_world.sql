UPDATE creature SET ScriptName = "npc_allied_race_infos_tauren" WHERE (`guid`='210119250');
UPDATE creature SET ScriptName = "npc_allied_race_infos_nightborne" WHERE (`guid`='210119253');

UPDATE creature SET ScriptName = "npc_allied_race_infos_draenei" WHERE (`guid`='11000002');
UPDATE creature SET ScriptName = "npc_allied_race_infos_voidelf" WHERE (`guid`='11000003');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_mark_of_nature';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(25042, 'spell_mark_of_nature');
UPDATE creature_template SET scriptname='boss_drugon_frostblood' WHERE entry=110378;
DELETE FROM spell_script_names WHERE scriptname = "spell_arti_pal_tyr_deliverance";
INSERT INTO spell_script_names VALUES (200653, "spell_arti_pal_tyr_deliverance");

UPDATE creature_template SET spell1 = 58859, spell2 = 0, spell3 = 0, spell4 = 0, ScriptName = 'npc_feral_spirit' WHERE entry = 29264;

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(50725, 'spell_warr_vigilance_trigger'),
(50720, 'spell_warr_vigilance'),
(8232, 'spell_shaman_windfury_weapon'),
(88766, 'spell_sha_fulmination'),
(55440, 'spell_sha_glyph_of_healing_wave'),
(324, 'spell_sha_lightning_shield'),
(30884, 'spell_sha_nature_guardian'),
(974, 'spell_sha_earth_shield'),
(50720, 'spell_warr_vigilance'),
(50720, 'spell_warr_vigilance'),
(61882, 'aura_sha_earthquake'),
(20230, 'spell_warr_retaliation'),
(94009, 'spell_warr_rend'),
(59725, 'spell_warr_improved_spell_reflection'),
(108501, 'spell_warl_grimoire_of_service_aura'),
(196098, 'spell_warl_soul_harvest'),
(193440, 'spell_warl_demonwrath_periodic'),
(131623, 'spell_warl_twilight_ward_s12'),
(29858, 'spell_warl_soulshatter'),
(86211, 'spell_warl_soul_swap_override'),
(86213, 'spell_warl_soul_swap_exhale'),
(92795, 'spell_warl_soul_swap_dot_marker'),
(86121, 'spell_warl_soul_swap'),
(228974, 'spell_warl_soul_leech_aura'),
(-7235, 'spell_warl_shadow_ward'),
(47960, 'spell_warl_molten_core_dot'),
(103958, 'spell_warl_metamorphosis_cost'),
(193396, 'spell_warl_demonic_empowerment'),
(114925, 'spell_warl_demonic_call'),
(686, 'spell_warl_demonic_call'),
(6353, 'spell_warl_demonic_call'),
(103964, 'spell_warl_demonic_call');