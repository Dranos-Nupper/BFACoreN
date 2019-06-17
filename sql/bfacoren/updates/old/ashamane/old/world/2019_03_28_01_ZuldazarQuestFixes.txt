-- Zul the Prophet 129907 SAI
SET @ENTRY := 129907;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,19,0,100,0,49905,0,0,0,206,6504,0,0,0,0,0,7,0,0,0,0,0,0,0,"Zul the Prophet 129907 - On Quest '' Taken"),
(@ENTRY,0,1,2,10,0,100,0,1,5,30000,30000,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zul the Prophet 129907 - Within 1-5 Range Out of Combat LoS - Say Line 3"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,130344,10,0,0,0,0,0,"Zul the Prophet 129907 - Within 0-0 Range Out of Combat LoS - Set Data 0 1");

-- Vol'jamba 130344 SAI
SET @ENTRY := 130344;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,0,1,0,0,67,1,3000,3000,0,0,0,1,0,0,0,0,0,0,0,"Vol'jamba 130344 - On Data Set 0 1 - Create Timed Event"),
(@ENTRY,0,1,0,59,0,100,0,1,0,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vol'jamba 130344 - On Timed Event 1 Triggered - Say Line 4");

-- Jambani Spirit Twister 129513 SAI
SET @ENTRY := 129513;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,0,0,0,0,0,11,257922,0,0,0,0,0,7,0,0,0,0,0,0,0,"Jambani Spirit Twister 129513 - On Just Died - Cast 'Spell Id257922'"),
(@ENTRY,0,1,0,11,0,100,0,0,0,0,0,11,258689,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jambani Spirit Twister 129513 - On Respawn - Cast 'Spell Id258689'"),
(@ENTRY,0,2,0,0,0,100,0,4000,6000,3000,6000,11,260162,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jambani Spirit Twister 129513 - In Combat - Cast 'Spell Id260162'"),
(@ENTRY,0,3,0,6,0,10,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jambani Spirit Twister 129513 - On Just Died - Say Line 0"),
(@ENTRY,0,4,0,6,0,10,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jambani Spirit Twister 129513 - On Just Died - Say Line 1");

-- Jambani Crusher 129487 SAI
SET @ENTRY := 129487;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,0,0,0,0,0,11,257923,0,0,0,0,0,7,0,0,0,0,0,0,0,"Jambani Crusher 129487 - On Just Died - Cast 'Spell Id257923'"),
(@ENTRY,0,1,0,0,0,100,0,4000,6000,3000,9000,11,260177,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jambani Crusher 129487 - In Combat - Cast 'Spell Id260177'");

-- Howling Voodoo Mask 128933 SAI
SET @ENTRY := 128933;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,1,0,6,0,100,0,0,0,0,0,11,257924,0,0,0,0,0,7,0,0,0,0,0,0,0,"Howling Voodoo Mask 128933 - On Just Died - Cast 'Spell Id257924'"),
(@ENTRY,0,2,0,0,0,100,0,3000,9000,4000,8000,11,260205,0,0,0,0,0,2,0,0,0,0,0,0,0,"Howling Voodoo Mask 128933 - In Combat - Cast 'Spell Id260205'");


-- Izita's Spirit 130706 SAI
SET @ENTRY := 130706;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,49491,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Izita's Spirit 130706 - On Quest '' Finished - Run Script");

-- Izita's Spirit 130706 SAI
SET @ENTRY := 130706;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,49491,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Izita's Spirit 130706 - On Quest '' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 13070600;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Izita's Spirit 130706 - On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,2000,2000,0,0,45,0,1,0,0,0,0,10,210404337,130866,0,0,0,0,0,"Izita's Spirit 130706 - On Script - Set Data 0 1"),
(@ENTRY,9,2,0,0,0,100,0,2000,2000,0,0,45,0,1,0,0,0,0,10,210404338,130866,0,0,0,0,0,"Izita's Spirit 130706 - On Script - Set Data 0 1"),
(@ENTRY,9,3,0,0,0,100,0,1000,1000,0,0,45,0,1,0,0,0,0,10,210404336,130866,0,0,0,0,0,"Izita's Spirit 130706 - On Script - Set Data 0 1"),
(@ENTRY,9,4,0,0,0,100,0,1000,1000,0,0,45,0,1,0,0,0,0,10,210404334,130866,0,0,0,0,0,"Izita's Spirit 130706 - On Script - Set Data 0 1"),
(@ENTRY,9,5,0,0,0,100,0,1000,1000,0,0,114,0,0,0,0,0,0,1,0,0,0,0,0,10,0,"Izita's Spirit 130706 - On Script"),
(@ENTRY,9,6,0,0,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Izita's Spirit 130706 - On Script - Despawn In 2000 ms");

-- Gurubashi Spirit 130866 SAI
SET @ENTRY := 130866;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,38,0,100,0,0,1,0,0,114,0,0,0,0,0,0,1,0,0,0,0,0,10,0,"Gurubashi Spirit 130866 - On Data Set 0 1"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gurubashi Spirit 130866 - On Data Set 0 0 - Despawn In 2000 ms");

-- Jambani Chosen 130221 SAI
SET @ENTRY := 130221;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,1500,1500,11,243575,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jambani Chosen 130221 - In Combat - Cast 'Spell Id243575'"),
(@ENTRY,0,1,0,6,0,10,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jambani Chosen 130221 - On Just Died - Say Line 0");

-- Mindslaved Gurubashi 129752 SAI
SET @ENTRY := 129752;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,257795,0,0,0,33,129752,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mindslaved Gurubashi 129752 - On Spellhit 'Spell Id257795' - Quest Credit 'Mindslaved Gurubashi 129752'"),
(@ENTRY,0,1,0,8,0,100,0,257795,0,0,0,28,257998,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mindslaved Gurubashi 129752 - On Spellhit 'Spell Id257795' - Remove Aura 'Spell Id257998'"),
(@ENTRY,0,2,0,8,0,100,0,257795,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mindslaved Gurubashi 129752 - On Spellhit 'Spell Id257795' - Set Faction 35"),
(@ENTRY,0,3,0,8,0,100,0,257795,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-240.64,267.005,239.631,0,"Mindslaved Gurubashi 129752 - On Spellhit 'Spell Id257795' - Move To Position"),
(@ENTRY,0,4,0,8,0,100,0,257795,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mindslaved Gurubashi 129752 - On Spellhit 'Spell Id257795' - Despawn In 10000 ms"),
(@ENTRY,0,5,0,0,0,100,0,0,3000,4000,9000,11,214575,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mindslaved Gurubashi 129752 - In Combat - Cast 'Spell Id214575'");

-- Mindslaved Berserker 130219 SAI
SET @ENTRY := 130219;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,257795,0,0,0,33,129752,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mindslaved Berserker 130219 - On Spellhit 'Spell Id257795' - Quest Credit 'Mindslaved Gurubashi 129752'"),
(@ENTRY,0,1,0,8,0,100,0,257795,0,0,0,28,257998,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mindslaved Berserker 130219 - On Spellhit 'Spell Id257795' - Remove Aura 'Spell Id257998'"),
(@ENTRY,0,2,0,8,0,100,0,257795,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mindslaved Berserker 130219 - On Spellhit 'Spell Id257795' - Set Faction 35"),
(@ENTRY,0,3,0,8,0,100,0,257795,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-240.64,267.005,239.631,0,"Mindslaved Berserker 130219 - On Spellhit 'Spell Id257795' - Move To Position"),
(@ENTRY,0,4,0,8,0,100,0,257795,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mindslaved Berserker 130219 - On Spellhit 'Spell Id257795' - Despawn In 10000 ms"),
(@ENTRY,0,5,0,0,0,100,0,6000,9000,11000,13000,11,214575,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mindslaved Berserker 130219 - In Combat - Cast 'Spell Id214575'");

update `creature_template` set `faction` = 7 where `entry` = 132213;

-- Zuvembi Brewer Zekal 130260 SAI
SET @ENTRY := 130260;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zuvembi Brewer Zekal 130260 - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,6,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zuvembi Brewer Zekal 130260 - On Just Died - Say Line 2"),
(@ENTRY,0,2,0,0,0,100,0,0,3000,5000,9000,11,260684,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zuvembi Brewer Zekal 130260 - In Combat - Cast 'Spell Id260684'"),
(@ENTRY,0,3,0,0,0,100,0,20000,25000,30000,60000,11,260617,1,0,0,0,0,19,132213,50,0,0,0,0,0,"Zuvembi Brewer Zekal 130260 - In Combat - Cast 'Spell Id260617'");

-- Weakened Sacrifice 132213 SAI
SET @ENTRY := 132213;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,34,0,100,0,8,1,0,0,11,260626,0,0,0,0,0,1,0,0,0,0,0,0,0,"Weakened Sacrifice 132213 - On Reached Point 1 - Cast 'Spell Id260626'"),
(@ENTRY,0,1,0,31,0,100,0,0,0,0,0,51,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Weakened Sacrifice 132213 - On Target Spellhit - Kill Target"),
(@ENTRY,0,2,4,8,0,100,0,260617,0,0,0,69,1,0,0,0,0,0,8,0,0,0,-139.135,219.572,234.312,0,"Weakened Sacrifice 132213 - On Spellhit 'Spell Id260617' - Move To Position"),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Weakened Sacrifice 132213 - MISSING LINK - Despawn In 1000 ms"),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Weakened Sacrifice 132213 - On Spellhit - Set Reactstate Passive");

-- Bubbling Cauldron 132217 SAI
SET @ENTRY := 132217;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,0,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Spellhit - Run Script");

-- Actionlist SAI
SET @ENTRY := 13221700;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,1,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,2,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,3,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,4,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,5,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,6,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,7,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,8,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'"),
(@ENTRY,9,9,0,0,0,100,0,1500,1500,0,0,11,260674,0,0,0,0,0,18,50,0,0,0,0,0,0,"Bubbling Cauldron 132217 - On Script - Cast 'Spell Id260674'");

-- Vol'jamba 130294 SAI
SET @ENTRY := 130294;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,11,259228,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vol'jamba 130294 - On Respawn - Cast 'Spell Id259228'");

-- Table `creature_template`
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_voljamba' WHERE (entry = 131241);

-- Zul the Prophet 129907 SAI
SET @ENTRY := 129907;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,19,0,100,0,49905,0,0,0,206,6504,0,0,0,0,0,7,0,0,0,0,0,0,0,"Zul the Prophet 129907 - On Quest '' Taken"),
(@ENTRY,0,1,2,10,0,100,0,1,5,30000,30000,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zul the Prophet 129907 - Within 1-5 Range Out of Combat LoS - Say Line 3"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,130344,10,0,0,0,0,0,"Zul the Prophet 129907 - Within 0-0 Range Out of Combat LoS - Set Data 0 1"),
(@ENTRY,0,3,4,19,0,100,0,49905,0,0,0,12,131241,4,15000,0,0,0,8,0,0,0,-372.61,150.864,257.285,0,"Zul the Prophet 129907 - On Quest '' Taken - Summon Creature 'Vol'jamba 131241'"),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,33,130294,0,0,0,0,0,7,0,0,0,0,0,0,0,"Zul the Prophet 129907 - On Quest Taken - Quest Credit 'Vol'jamba 130294'");

-- Howling Voodoo Mask 133375 SAI
SET @ENTRY := 133375;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,5000,9000,11,260205,0,0,0,0,0,2,0,0,0,0,0,0,0,"Howling Voodoo Mask 133375 - In Combat - Cast 'Spell Id260205'");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry`=258689 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=31 AND `ConditionTarget`=0 AND `ConditionValue1`=5 AND `ConditionValue2`=130706 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (13, 1, 258689, 0, 0, 31, 0, 5, 130706, 0, 0, 0, 0, '', NULL);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry`=258689 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=31 AND `ConditionTarget`=0 AND `ConditionValue1`=5 AND `ConditionValue2`=130029 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (13, 1, 258689, 0, 1, 31, 0, 5, 130029, 0, 0, 0, 0, '', NULL);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry`=258689 AND `SourceId`=0 AND `ElseGroup`=2 AND `ConditionTypeOrReference`=31 AND `ConditionTarget`=0 AND `ConditionValue1`=5 AND `ConditionValue2`=130707 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (13, 1, 258689, 0, 2, 31, 0, 5, 130707, 0, 0, 0, 0, '', NULL);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry`=258689 AND `SourceId`=0 AND `ElseGroup`=3 AND `ConditionTypeOrReference`=31 AND `ConditionTarget`=0 AND `ConditionValue1`=5 AND `ConditionValue2`=134156 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (13, 1, 258689, 0, 3, 31, 0, 5, 134156, 0, 0, 0, 0, '', NULL);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry`=258689 AND `SourceId`=0 AND `ElseGroup`=4 AND `ConditionTypeOrReference`=31 AND `ConditionTarget`=0 AND `ConditionValue1`=5 AND `ConditionValue2`=128933 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (13, 1, 258689, 0, 4, 31, 0, 5, 128933, 0, 0, 0, 0, '', NULL);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry`=259228 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=31 AND `ConditionTarget`=0 AND `ConditionValue1`=5 AND `ConditionValue2`=130308 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (13, 1, 259228, 0, 0, 31, 0, 5, 130308, 0, 0, 0, 0, '', NULL);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceGroup`=2 AND `SourceEntry`=129907 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=47 AND `ConditionTarget`=0 AND `ConditionValue1`=49490 AND `ConditionValue2`=42 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (22, 2, 129907, 0, 0, 47, 0, 49490, 42, 0, 0, 0, 0, '', NULL);

DELETE FROM `creature_text` WHERE `CreatureID`=129907 AND `GroupID`=3 AND `ID`=0;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (129907, 3, 0, 'Quit hiding behind your masks. You\'re only buying time, and not much at dat.', 12, 0, 100, 0, 0, 106237, 143195, 0, 'Zul the Prophet to Player');
DELETE FROM `creature_text` WHERE `CreatureID`=130344 AND `GroupID`=4 AND `ID`=0;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (130344, 4, 0, 'If you had seen what I have, you would do de same. Come inside. I will show you!', 12, 0, 100, 0, 0, 103520, 146601, 0, 'Vol\'jamba to Player');

DELETE FROM `spell_script_names` WHERE `spell_id`=264007 AND `ScriptName`='spell_soul_jaunt';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (264007, 'spell_soul_jaunt');
