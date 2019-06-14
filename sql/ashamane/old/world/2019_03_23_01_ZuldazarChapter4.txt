-- Conducting Rod 132155 SAI
SET @ENTRY := 132155;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Conducting Rod 132155 - On Respawn - Set Reactstate Passive");

-- Jao-Ti the Thunderous 128474 SAI
SET @ENTRY := 128474;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jao-Ti the Thunderous 128474 - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,28,255625,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jao-Ti the Thunderous 128474 - On Aggro - Remove Aura 'Spell Id255625'"),
(@ENTRY,0,2,0,0,0,100,0,4000,4500,20000,25000,11,259750,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jao-Ti the Thunderous 128474 - In Combat - Cast 'Spell Id259750'"),
(@ENTRY,0,3,0,0,0,100,0,6000,6500,8000,10000,11,259744,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jao-Ti the Thunderous 128474 - In Combat - Cast 'Spell Id259744'"),
(@ENTRY,0,4,0,0,0,100,0,9000,13000,18000,20000,11,224839,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jao-Ti the Thunderous 128474 - In Combat - Cast 'Spell Id224839'"),
(@ENTRY,0,5,0,6,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jao-Ti the Thunderous 128474 - On Just Died - Say Line 1");

-- Subjugator Zheng 128472 SAI
SET @ENTRY := 128472;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Subjugator Zheng 128472 - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,0,0,100,0,4000,5000,9000,90000,11,260065,0,0,0,0,0,2,0,0,0,0,0,0,0,"Subjugator Zheng 128472 - In Combat - Cast 'Spell Id260065'"),
(@ENTRY,0,2,0,0,0,100,0,7000,8000,11000,13000,11,224664,0,0,0,0,0,2,0,0,0,0,0,0,0,"Subjugator Zheng 128472 - In Combat - Cast 'Spell Id224664'"),
(@ENTRY,0,3,0,6,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Subjugator Zheng 128472 - On Just Died - Say Line 1");

-- Zolani 129088 SAI
SET @ENTRY := 129088;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,10,0,100,0,1,3,0,30000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zolani 129088 - Within 1-3 Range Out of Combat LoS - Say Line 0");

-- Warlord Kao 127766 SAI
SET @ENTRY := 127766;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,143253,50,0,0,0,0,0,"Warlord Kao 127766 - On Aggro - Set Data 0 1"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,11000,23000,11,260068,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warlord Kao 127766 - In Combat - Cast 'Spell Id260068'"),
(@ENTRY,0,2,0,0,0,100,0,8000,10000,11000,23000,11,260075,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warlord Kao 127766 - In Combat - Cast 'Spell Id260075'"),
(@ENTRY,0,3,0,38,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warlord Kao 127766 - On Data Set 0 0 - Say Line 0");

-- Warlord Kao 127766 SAI
SET @ENTRY := 127766;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,143253,50,0,0,0,0,0,"Warlord Kao 127766 - On Aggro - Set Data 0 1"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,11000,23000,11,260068,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warlord Kao 127766 - In Combat - Cast 'Spell Id260068'"),
(@ENTRY,0,2,0,0,0,100,0,8000,10000,11000,23000,11,260075,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warlord Kao 127766 - In Combat - Cast 'Spell Id260075'"),
(@ENTRY,0,3,0,38,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warlord Kao 127766 - On Data Set 0 0 - Say Line 0");

UPDATE `creature_template` SET `npcflag` = 16777216 WHERE (entry = 133960);
UPDATE `creature_template` SET `vehicleId` = 5664 WHERE (entry = 133961);
UPDATE `creature_template` SET  `unit_flags` = 33544 WHERE (entry = 133961);

-- Scarbeak 133960 SAI
SET @ENTRY := 133960;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,0,0,0,0,28,263139,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarbeak 133960 - Out of Combat - Remove Aura 'Spell Id263139'"),
(@ENTRY,0,1,2,73,0,100,0,0,0,0,0,33,129417,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarbeak 133960 - On Spellclick - Quest Credit 'Scarbeak 129417'"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,28,263139,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarbeak 133960 - On Spellclick - Remove Aura 'Spell Id263139'");

-- Scarbeak 133961 SAI
SET @ENTRY := 133961;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,2,54,0,100,0,0,0,0,0,85,98709,1,0,0,0,0,1,0,0,0,0,0,0,0,"Scarbeak 133961 - On Just Summoned - Invoker Cast 'Spell Id98709'"),
(@ENTRY,0,1,0,27,0,100,0,0,0,0,0,53,1,133961,0,0,0,0,1,0,0,0,0,0,0,0,"Scarbeak 133961 - On Passenger Boarded - Start Waypoint"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarbeak 133961 - On Just Summoned - Set Fly On"),
(@ENTRY,0,3,4,58,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarbeak 133961 - On Waypoint Finished - Despawn Instant"),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,28,263139,0,0,0,0,0,18,5,0,0,0,0,0,0,"Scarbeak 133961 - On Waypoint Finished - Remove Aura 'Spell Id263139'");

UPDATE `creature_template` SET `entry` = 133961, `speed_walk` = 2.5, `speed_run` = 8 WHERE (entry = 133961);

DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=1;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 1, -2242.6, 1527.34, 15.0698, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=2;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 2, -2225.31, 1522.4, 15.0698, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=3;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 3, -2194.33, 1511.87, 21.6117, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=4;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 4, -2158.52, 1501.64, 29.7292, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=5;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 5, -2112.52, 1492.55, 36.0286, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=6;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 6, -2013.65, 1481.48, 54.0446, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=7;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 7, -1963.06, 1483.59, 73.7169, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=8;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 8, -1916.49, 1476.05, 96.3743, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=9;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 9, -1889.59, 1465.87, 105.721, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=10;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 10, -1857.63, 1448.34, 115.601, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=11;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 11, -1832.53, 1433.81, 118.448, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=12;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 12, -1803.18, 1416.15, 116.585, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=13;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 13, -1786.04, 1404.96, 118.021, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=14;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 14, -1772.33, 1388.12, 127.616, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=15;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 15, -1744.64, 1362.45, 147.626, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=16;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 16, -1688.59, 1345.11, 168.853, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=17;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 17, -1589.64, 1286.68, 185.118, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=18;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 18, -1530.24, 1257.01, 203.959, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=19;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 19, -1486.32, 1248.11, 226.798, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=20;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 20, -1383.78, 1224.38, 281.397, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=21;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 21, -1283.09, 1197.68, 325.787, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=22;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 22, -1144.13, 1157.42, 346.133, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=23;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 23, -1035.17, 1126.89, 356.808, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=24;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 24, -972.366, 1095.21, 362.017, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=25;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 25, -891.332, 1040.89, 369.093, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=26;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 26, -824.085, 978.347, 378.584, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=27;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 27, -762.58, 887.812, 391.428, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=28;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 28, -744.488, 781.505, 405.236, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=29;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 29, -760.132, 667.755, 415.373, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=30;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 30, -833.08, 583.342, 431.165, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=31;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 31, -947.087, 564.804, 448.502, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=32;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 32, -1046.23, 614.658, 461.802, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=33;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 33, -1078.71, 670.373, 480.255, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=34;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 34, -1088.3, 711.221, 492.627, NULL);
DELETE FROM `waypoints` WHERE `entry`=133961 AND `pointid`=35;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (133961, 35, -1091.13, 750.035, 491.156, NULL);

DELETE FROM `spell_script_names` WHERE `spell_id`=224839 AND `ScriptName`='spell_call_the_storm';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (224839, 'spell_call_the_storm');
DELETE FROM `spell_script_names` WHERE `spell_id`=260075 AND `ScriptName`='spell_lightning_rod';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (260075, 'spell_lightning_rod');
DELETE FROM `spell_script_names` WHERE `spell_id`=254904 AND `ScriptName`='spell_quest_revitalize_spirit_obelisk';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (254904, 'spell_quest_revitalize_spirit_obelisk');
DELETE FROM `spell_script_names` WHERE `spell_id`=263018 AND `ScriptName`='spell_rastari_skull_whistle';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (263018, 'spell_rastari_skull_whistle');
