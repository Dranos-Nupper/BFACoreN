UPDATE `creature_template_model` SET `CreatureDisplayID` = '1964' WHERE `CreatureID` = '3265' AND `CreatureDisplayID` = '6094'; 
UPDATE `quest_objectives` SET `ObjectID` = '34487' WHERE `ID` = '263556'; 
UPDATE `creature_template_model` SET `CreatureDisplayID` = '1964' WHERE `CreatureID` = '34503' AND `CreatureDisplayID` = '1344'; 
DELETE FROM `creature_template_model` WHERE `CreatureID` = '34503' AND `CreatureDisplayID` = '4745'; 
UPDATE `quest_objectives` SET `ObjectID` = '34503' WHERE `ID` = '264308'; 
DELETE FROM `creature_template_addon` WHERE (`entry`=34563);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (34563, 0, 0, 3, 1, 0, 78677);
UPDATE `quest_objectives` SET `ObjectID` = '34503' WHERE `ID` = '267591'; 
SET @ENTRY := 34513;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,19,0,100,0,13961,0,0,0,15,13961,0,0,0,0,0,7,0,0,0,0,0,0,0,'Quest Credit on Quest Add');
UPDATE `quest_objectives` SET `ObjectID` = '34503' WHERE `ID` = '264970'; 
UPDATE `quest_objectives` SET `Type` = '0' WHERE `ID` = '264308'; 
DELETE FROM `quest_objectives` WHERE `ID` = '264309'; 
-- Living Contamination
SET @ENTRY := 43089;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,3500,11,21067,64,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Poison Bolt'),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,63227,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Enrage at 30% HP');
-- Living Contamination
SET @ENTRY := 42185;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,3500,11,21067,64,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Poison Bolt'),
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,63227,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Enrage at 30% HP');
UPDATE `creature_template_model` SET `CreatureDisplayID` = '21131' WHERE `CreatureID` = '42185' AND `CreatureDisplayID` = '13749'; 
UPDATE `creature_template_model` SET `CreatureDisplayID` = '5492 ' WHERE `CreatureID` = '42185' AND `CreatureDisplayID` = '21131'; 
UPDATE `creature_template_model` SET `CreatureDisplayID` = '5492 ' WHERE `CreatureID` = '43089' AND `CreatureDisplayID` = '13749'; 
-- Gnomeregan Recruit
SET @ENTRY := 43092;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,2500,3000,11,85756,64,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Shoot'),
(@ENTRY,0,1,0,9,0,100,0,0,5,15000,25000,11,74413,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Attack on Close');
UPDATE `quest_objectives` SET `ObjectID` = '42494' WHERE `ID` = '265862'; 

UPDATE `creature` SET `spawndist` = 5, `MovementType` = 1 WHERE `id` IN (25844,34640,25355,25321,34503);
UPDATE `creature` SET `spawndist` = 0, `MovementType` = 0 WHERE `id` IN (34563,34259);