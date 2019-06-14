
UPDATE `gameobject_template` SET `ScriptName`='go_twilight_outhouse' WHERE `entry`=280948; 
DELETE FROM `scene_template` WHERE `SceneId`=1904;
INSERT INTO `scene_template` (`SceneId`, `Flags`, `ScriptPackageID`, `ScriptName`) VALUES (1904, 26, 2004, 'scene_the_power_in_our_hands');

UPDATE `creature_template` SET `ScriptName`='npc_kelsey_steelspark_130030' WHERE `entry`='130030';
UPDATE `creature_template` SET `ScriptName`='npc_tammy_tinkspinner_132606' WHERE `entry`='132606';
UPDATE `creature_template` SET `ScriptName`='npc_khargus_stonemantle_132192' WHERE `entry`='132192';
UPDATE `creature_template` SET `ScriptName`='npc_archmage_khadgar_130032' WHERE `entry`='130032';	
UPDATE `creature_template` SET `ScriptName`='npc_magni_bronzebeard_silithus' WHERE `entry`='130216';
UPDATE `creature_template` SET `ScriptName`='npc_pixni_rustbomb_132040' WHERE `entry`='132040';
UPDATE `creature_template` SET `ScriptName`='npc_gizmax_greasebolt_132045' WHERE `entry`='132045';
UPDATE `creature_template` SET `ScriptName`='npc_grol_warblade_132147' WHERE `entry`='132147';
UPDATE `creature_template` SET `ScriptName`='npc_lazy_prospector_133019' WHERE `entry`='133019';
UPDATE `creature_template` SET `ScriptName`='npc_archmage_khadgar_130033' WHERE `entry`='130033';
UPDATE `creature_template` SET `ScriptName`='npc_nathanos_blightcaller_132254' WHERE `entry`='132254';
UPDATE `creature_template` SET `ScriptName`='npc_laurette_royston_132995' WHERE `entry`='132995';
UPDATE `creature_template` SET `ScriptName`='npc_magni_bronzebeard_133387' WHERE `entry`='133387';
UPDATE `creature_template` SET `ScriptName`='npc_kaylie_benson_133254' WHERE `entry`='133254';