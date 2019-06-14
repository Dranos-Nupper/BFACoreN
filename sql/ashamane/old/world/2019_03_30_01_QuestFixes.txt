-- Wardruid Loti 134132 SAI
SET @ENTRY := 134132;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,54,0,100,0,0,0,0,0,11,263510,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wardruid Loti 134132 - On Just Summoned - Cast 'Spell Id263510'"),
(@ENTRY,0,1,5,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wardruid Loti 134132 - On Just Summoned - Say Line 0"),
(@ENTRY,0,3,7,40,0,100,0,46,134132,0,0,28,46598,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wardruid Loti 134132 - On Waypoint 46 Reached - Remove Aura 'Ride Vehicle Hardcoded 46598'"),
(@ENTRY,0,4,0,40,0,100,0,48,134132,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wardruid Loti 134132 - On Waypoint 48 Reached - Despawn Instant"),
(@ENTRY,0,5,6,61,0,100,0,0,0,0,0,62,1642,0,0,0,0,0,1,0,0,0,-773.13,1093.22,321.146,0,"Wardruid Loti 134132 - On Just Summoned - Teleport"),
(@ENTRY,0,6,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-768.591,1116.03,321.494,0,"Wardruid Loti 134132 - On Just Summoned - Move To Position"),
(@ENTRY,0,7,0,61,0,100,0,0,0,0,0,33,129740,0,0,0,0,0,21,5,0,0,0,0,0,0,"Wardruid Loti 134132 - On Waypoint 0 Reached - Quest Credit 'Gonk 129740'"),
(@ENTRY,0,8,10,73,0,100,0,0,0,0,0,85,259567,0,0,0,0,0,7,0,0,0,0,0,0,0,"Wardruid Loti 134132 - On Spellclick - Invoker Cast 'Spell Id259567'"),
(@ENTRY,0,10,0,38,0,100,0,0,1,0,0,53,1,134132,0,0,0,0,1,0,0,0,0,0,0,0,"Wardruid Loti 134132 - On Data Set 0 1 - Start Waypoint");

-- Disciple of Zul 129504 SAI
SET @ENTRY := 129504;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,11,256652,0,0,0,0,0,19,55370,21,0,0,0,0,0,"Disciple of Zul 129504 - On Respawn - Cast 'Spell Id256652'"),
(@ENTRY,0,1,0,0,0,100,0,4000,6000,5000,9000,11,266146,0,0,0,0,0,2,0,0,0,0,0,0,0,"Disciple of Zul 129504 - In Combat - Cast 'Spell Id266146'"),
(@ENTRY,0,2,0,2,0,100,0,0,60,15000,20000,11,15586,0,0,0,0,0,1,0,0,0,0,0,0,0,"Disciple of Zul 129504 - Between 0-60% Health - Cast 'Heal 15586'");

-- Rezan 131049 SAI
SET @ENTRY := 131049;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,19,0,100,0,49426,0,0,0,85,274060,0,0,0,0,0,7,0,0,0,0,0,0,0,"Rezan 131049 - On Quest '' Taken - Invoker Cast 'Spell Id274060'");

-- Zayoos 131476 SAI
SET @ENTRY := 131476;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zayoos 131476 - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,0,0,100,0,6000,9000,5000,15000,11,263692,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zayoos 131476 - In Combat - Cast 'Spell Id263692'"),
(@ENTRY,0,2,0,0,0,100,0,16000,19000,15000,25000,11,263696,0,0,0,0,0,5,0,0,0,0,0,0,0,"Zayoos 131476 - In Combat - Cast 'Spell Id263696'"),
(@ENTRY,0,3,0,0,0,100,0,10000,25000,15000,30000,11,263684,0,0,0,0,0,5,0,0,0,0,0,0,0,"Zayoos 131476 - In Combat - Cast 'Spell Id263684'");

-- King Da'ka 130948 SAI
SET @ENTRY := 130948;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"King Da'ka 130948 - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,0,0,100,0,15000,19000,18000,22000,11,263991,0,0,0,0,0,2,0,0,0,0,0,0,0,"King Da'ka 130948 - In Combat - Cast 'Spell Id263991'"),
(@ENTRY,0,2,0,0,0,100,0,9000,19000,15000,22000,11,262069,0,0,0,0,0,5,0,0,0,0,0,0,0,"King Da'ka 130948 - In Combat - Cast 'Spell Id262069'");

-- Rokhan 126549 SAI
SET @ENTRY := 126549;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,10,0,100,0,1,5,0,0,15,47103,0,0,0,0,0,7,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)");

-- Paku'ai Rokota 122689 SAI
SET @ENTRY := 122689;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,22290,1,0,0,33,122689,0,0,0,0,0,7,0,0,0,0,0,0,0,"Paku'ai Rokota 122689 - On Gossip Option 1 Selected - Quest Credit 'Paku'ai Rokota 122689'"),
-- todo fix wrong taxi and add dialouge (need sniffs)
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,52,2043,0,0,0,0,0,7,0,0,0,0,0,0,0,"Paku'ai Rokota 122689 - On Gossip Option 0 Selected - Activate Taxi Path 2043");

-- Princess Talanji 120904 SAI
SET @ENTRY := 120904;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,10,0,100,0,1,10,0,0,33,120904,0,0,0,0,0,7,0,0,0,0,0,0,0,"Princess Talanji 120904 - Within 1-10 Range Out of Combat LoS - Quest Credit 'Princess Talanji 120904'"),
(@ENTRY,0,1,0,19,0,100,0,47105,0,0,0,85,241832,0,0,0,0,0,7,0,0,0,0,0,0,0,"Princess Talanji 120904 - On Quest '' Taken - Invoker Cast 'Spell Id241832'");

-- Princess Talanji 121241 SAI
SET @ENTRY := 121241;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,75,0,100,1,0,121437,10,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Distance To Creature - Run Script (No Repeat)"),
(@ENTRY,0,1,3,19,0,100,0,47262,0,0,0,53,1,@ENTRY*100+00,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Quest '' Taken - Start Waypoint"),
(@ENTRY,0,2,0,58,0,100,0,19,@ENTRY*100+00,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Waypoint Finished - Despawn Instant"),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Quest Taken - Say Line 1");

-- Actionlist SAI
SET @ENTRY := 12124100;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,0,0,0,0,53,1,121241,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Script - Start Waypoint"),
(@ENTRY,9,2,0,0,0,100,0,0,0,0,0,33,121437,0,0,0,0,0,23,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Script - Quest Credit 'Entered First Camp 121437'"),
(@ENTRY,9,3,0,0,0,100,0,5000,5000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Script - Say Line 1"),
(@ENTRY,9,4,0,0,0,100,0,1000,1000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 121241 - On Script - Despawn Instant");

-- Blood Troll Brutalizer 120607 SAI
SET @ENTRY := 120607;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,6000,5000,9000,11,256607,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blood Troll Brutalizer 120607 - In Combat - Cast 'Spell Id256607'"),
(@ENTRY,0,1,0,4,0,100,0,0,0,0,0,28,281885,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blood Troll Brutalizer 120607 - On Aggro - Remove Aura 'Spell Id281885'");

-- Dead Zandalari 121296 SAI
SET @ENTRY := 121296;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,241992,0,0,0,33,121296,0,0,0,0,0,7,0,0,0,0,0,0,0,"Dead Zandalari 121296 - On Spellhit 'Spell Id241992' - Quest Credit 'Dead Zandalari 121296'"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dead Zandalari 121296 - On Spellhit - Despawn In 2000 ms");

-- Blood Troll Hexxer 120606 SAI
SET @ENTRY := 120606;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,9000,15000,20000,11,255366,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blood Troll Hexxer 120606 - In Combat - Cast 'Spell Id255366'");

-- Grand Ma'da Ateena 121504 SAI
SET @ENTRY := 121504;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,500,1000,2000,2000,11,256099,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grand Ma'da Ateena 121504 - In Combat - Cast 'Spell Id256099'"),
(@ENTRY,0,1,0,0,0,100,0,1500,21000,20000,23000,11,272672,1,0,0,0,0,2,0,0,0,0,0,0,0,"Grand Ma'da Ateena 121504 - In Combat - Cast 'Spell Id272672'"),
(@ENTRY,0,2,3,2,0,100,0,0,65,0,0,33,121504,0,0,0,0,0,18,50,0,0,0,0,0,0,"Grand Ma'da Ateena 121504 - Between 0-65% Health - Quest Credit 'Grand Ma'da Ateena 121504'"),
(@ENTRY,0,3,4,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grand Ma'da Ateena 121504 - Between 0-0% Health - Despawn Instant"),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,129730,50,0,0,0,0,0,"Grand Ma'da Ateena 121504 - Between 0-0% Health - Set Data 0 1");

-- Actionlist SAI
SET @ENTRY := 12973000;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 129730 - On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,5000,5000,0,0,69,1,0,0,0,0,0,8,0,0,0,1039.10,1071.56,26.74,0,"Princess Talanji 129730 - On Script - Move To Position"),
(@ENTRY,9,2,0,0,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 129730 - On Script - Say Line 1");

-- Princess Talanji 129730 SAI
SET @ENTRY := 129730;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,74,0,100,0,0,50,0,0,11,271670,0,0,0,0,0,21,60,0,0,0,0,0,0,"Princess Talanji 129730 - On Friendly Between 0-50% Health - Cast 'Spell Id271670'"),
(@ENTRY,0,1,0,38,0,100,0,0,1,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 129730 - On Data Set 0 1 - Run Script"),
(@ENTRY,0,2,0,11,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 129730 - On Respawn - Set Run On"),
(@ENTRY,0,3,0,34,0,100,0,8,1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 129730 - On Reached Point 1 - Despawn Instant");

-- Princess Talanji 130844 SAI
SET @ENTRY := 130844;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,19,0,100,0,47263,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 130844 - On Quest '' Taken - Say Line 0"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,53,1,130844,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 130844 - On Quest Taken - Start Waypoint"),
(@ENTRY,0,2,3,58,0,100,0,0,130844,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 130844 - On Waypoint Finished - Say Line 1"),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Princess Talanji 130844 - On Waypoint Finished - Despawn Instant");

-- Princess Talanji 131146 SAI
SET @ENTRY := 131146;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,62,0,100,0,21814,0,0,0,85,257255,0,0,0,0,0,7,0,0,0,0,0,0,0,"Princess Talanji 131146 - On Gossip Option 0 Selected - Invoker Cast 'Spell Id257255'");

UPDATE `creature_template` SET `npcflag` = 16777216,`VehicleId` = 5390, `unit_flags` = 33554440, `unit_flags2` = 133120 WHERE (entry = 121530);#
-- todo check correct speed
UPDATE `creature_template` SET `speed_run` = 1.5 WHERE (entry = 121530);

-- Actionlist SAI
SET @ENTRY := 12153000;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,500,500,0,0,85,46598,2,0,0,0,0,1,0,0,0,0,0,0,0,"Tze'na 121530 - On Script - Invoker Cast 'Ride Vehicle Hardcoded 46598'"),
(@ENTRY,9,1,0,0,0,100,0,500,500,0,0,75,263750,0,0,0,0,0,7,0,0,0,0,0,0,0,"Tze'na 121530 - On Script - Add Aura 'Spell Id263750'");

-- Tze'na 121530 SAI
SET @ENTRY := 121530;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Tze'na 121530 - On Just Summoned - Run Script"),
(@ENTRY,0,1,3,27,0,100,513,0,0,0,0,53,1,121530,0,0,0,0,1,0,0,0,0,0,0,0,"Tze'na 121530 - On Passenger Boarded - Start Waypoint (No Repeat) (While Charmed)"),
(@ENTRY,0,2,3,58,0,100,0,0,121530,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tze'na 121530 - On Waypoint Finished - Despawn Instant");

-- Princess Talanji 130717 SAI
SET @ENTRY := 130717;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,11,46598,1,0,0,0,0,23,0,0,0,0,0,0,0,"Princess Talanji 130717 - On Just Summoned - Cast 'Ride Vehicle Hardcoded 46598'");

UPDATE `creature_template` SET `speed_walk` = 1, `speed_run` = 2.1 WHERE (entry = 134132);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=121530 AND `spell_id`=46598;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (121530, 46598, 1, 0);

DELETE FROM `spell_script_names` WHERE `spell_id`=257255 AND `ScriptName`='spell_play_chapter_1';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (257255, 'spell_play_chapter_1');

INSERT IGNORE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `comment`) VALUES
(121241, 0, 0, 'My people... slaughtered! You see now de evil we are fighting, $n. De blood trolls are monsters!', 12, 0, 100, 22, 0, 101779, 130485, 'Princess Talanji to Player'),
(121241, 1, 0, 'Best if I stay hidden until de time comes to strike. We will bring down Ateena together!', 12, 0, 100, 0, 0, 101748, 140936, 'Princess Talanji to Player');

DELETE FROM `waypoints` WHERE `entry` = 12124100;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,1,908.3568,1048.32,6.887704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,2,908.8568,1048.32,7.137704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,3,909.3568,1048.57,7.137704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,4,910.6068,1048.57,6.887704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,5,910.8568,1048.57,7.137704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,6,914.3568,1048.32,7.137704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,7,914.6068,1048.32,7.137704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,8,915.3568,1048.32,7.137704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,9,918.8568,1048.07,7.387704,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,10,922.8568,1048.07,7.637704,null);

INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,11,919.0225,1048.188,7.650141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,12,923.2725,1048.188,7.900141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,13,923.7725,1047.938,7.900141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,14,924.7725,1048.188,8.150141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,15,926.5225,1048.938,8.150141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,16,927.2725,1049.188,8.400141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,17,929.2725,1049.938,8.650141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,18,932.0225,1050.688,8.900141,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (12124100,19,933.0225,1051.188,9.150141,null);

DELETE FROM `waypoints` WHERE `entry` = 130844;

INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,1,1041.435,1071.668,27.01378,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,2,1043.435,1071.418,27.26378,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,3,1051.435,1071.418,27.01378,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,4,1054.435,1071.418,26.76378,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,5,1056.435,1071.418,26.51378,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,6,1058.435,1071.418,26.26378,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,7,1062.185,1071.418,26.01378,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,8,1084.185,1071.418,26.26378,null);

INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,9,1091.168,1069.14,25.87381,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,10,1093.168,1068.64,25.37381,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,11,1094.168,1068.39,25.12381,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,12,1096.668,1067.39,24.87381,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,13,1098.418,1066.89,24.87381,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,14,1101.668,1063.39,24.62381,null);

INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,15,1101.969,1063.128,24.5108,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,16,1103.969,1060.878,24.2608,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,17,1107.719,1059.878,24.0108,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,18,1110.719,1059.378,24.0108,null);

INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,19,1107.903,1059.764,24.17693,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,20,1110.903,1059.014,23.92693,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,21,1114.403,1058.264,23.67693,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,22,1116.903,1056.514,23.42693,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,23,1119.403,1055.014,23.42693,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (130844,24,1121.903,1053.264,23.17693,null);

DELETE FROM `waypoints` WHERE `entry` = 130844;

DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=1;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 1, 1122.47, 1052.72, 23.1423, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=2;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 2, 1111.22, 1061.97, 24.1423, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=3;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 3, 1111.14, 1080.17, 17.7855, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=4;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 4, 1112.08, 1091.22, 14.6626, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=5;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 5, 1110.44, 1098.12, 14.2489, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=6;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 6, 1107.74, 1105.59, 13.8983, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=7;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 7, 1098.74, 1113.09, 14.1483, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=8;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 8, 1092.58, 1117.96, 13.9784, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=9;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 9, 1078.31, 1131.72, 12.8417, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=10;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 10, 1068.43, 1138.76, 11.3178, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=11;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 11, 1056.92, 1145.95, 9.63842, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=12;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 12, 1043.74, 1153.49, 8.43429, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=13;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 13, 1031.85, 1165.15, 7.21017, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=14;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 14, 1020.55, 1183.61, 5.22663, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=15;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 15, 1003.14, 1202.12, 1.80339, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=16;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 16, 998.615, 1207.75, 1.58124, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=17;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 17, 987.493, 1224.03, 1.72253, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=18;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 18, 980.694, 1234.52, 0.982649, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=19;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 19, 976.07, 1241.02, 0.429828, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=20;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 20, 973.807, 1244.14, 0.177309, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=21;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 21, 958.334, 1266.94, 0.0652942, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=22;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 22, 949.73, 1278.95, 1.88866, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=23;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 23, 939.419, 1295.46, 0.463457, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=24;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 24, 936.97, 1299.33, 0.1512, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=25;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 25, 916.002, 1333.51, 0.172559, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=26;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 26, 902.868, 1350.47, 1.57322, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=27;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 27, 884.811, 1367.28, 2.38494, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=28;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 28, 872.666, 1375.37, 5.41949, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=29;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 29, 860.386, 1377.64, 8.09631, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=30;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 30, 841.711, 1376.09, 15.2707, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=31;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 31, 836.548, 1359.42, 16.1635, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=32;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 32, 832.151, 1349.72, 16.0522, NULL);
DELETE FROM `waypoints` WHERE `entry`=121530 AND `pointid`=33;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121530, 33, 830.481, 1347.78, 15.9612, NULL);

DELETE FROM `waypoints` WHERE `entry` = 121241;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,1,714.027,993.678,1.124916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,2,712.277,992.928,1.124916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,3,715.527,985.678,0.874916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,4,716.527,983.928,0.624916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,5,718.027,980.178,0.624916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,6,719.527,979.178,1.124916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,7,721.027,977.928,1.374916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,8,723.527,975.928,1.624916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,9,727.777,972.178,1.624916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,10,728.527,971.428,2.374916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,11,729.277,970.928,2.624916,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (121241,12,734.777,966.428,2.624916,null);


DELETE FROM `waypoints` WHERE `entry` = 139649;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (139649,1,-739.1703,2156.17,705.6909,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (139649,2,-743.9203,2140.67,706.1909,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (139649,3,-742.9203,2129.17,706.6909,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (139649,4,-742.4203,2120.67,710.6909,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (139649,5,-742.6703,2109.92,717.4409,null);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (139649,6,-739.4203,2096.42,717.4409,null);
