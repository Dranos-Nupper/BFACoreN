update `creature_template` set `gossip_menu_id` = 12129 where `entry` = 15187;

-- Cenarion Emissary Jademoon 15187 SAI
SET @ENTRY := 15187;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,12129,0,0,0,62,1,0,0,0,0,0,7,0,0,0,7802.04,-2430.96,488.675,0.296706,"Cenarion Emissary Jademoon 15187 - On Gossip Option 0 Selected - Teleport"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,15,27726,0,0,0,0,0,7,0,0,0,0,0,0,0,"Cenarion Emissary Jademoon 15187 - On Gossip Option 0 Selected - Quest Credit ''");

-- Aronus 39140 SAI
SET @ENTRY := 39140;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,73,0,100,0,0,0,0,0,12,39128,8,0,0,0,0,8,0,0,0,7791.06,-2445.54,489.563,0,"Aronus 39140 - On Spellclick - Summon Creature 'Aronus 39128'"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,85,76649,0,0,0,0,0,19,39128,50,0,0,0,0,0,"Aronus 39140 - On Spellclick - Invoker Cast 'Spell Id76649'");
