ALTER TABLE `creature_template_scaling` CHANGE `VerifiedBuild` `VerifiedBuild` SMALLINT(5) DEFAULT 28153 NULL; 

-- Nothern Barrence
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='17';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='10' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Ashenvale
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='331';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='15' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Azshara
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='16';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='10' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Bloodmyst Isle
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3525';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='10' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Darkshore
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='148';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='10' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Desolace
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='148';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='30' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Dustwallow Marsh
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='15';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='35' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Felwood
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='361';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Feralas
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='357';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='35' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Moonglade
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='493';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='1' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Mount Hyjal
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='616';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='80' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Silithus
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='1377';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Southern Barrens
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='4709';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='25' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Stonetalon Mountains
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='406';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='20' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Tanaris
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='440';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Thousand Needles
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='400';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Uldum
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='5034';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='83' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Un'Goro Crater
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='490';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Winterspring
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1' AND `zoneId`='618';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Arathi Highlands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='45';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='25' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Badlands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='3';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Blackrock Mountain
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='25';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='50' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Blasted Lands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='4';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Burning Steppes
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='46';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Deadwind Pass
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='41';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='50' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Deeprun Tram
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='369' AND `zoneId`='2257';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='1' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='100' WHERE `LevelScalingMax`='0';

-- Duskwood
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='10';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='20' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Eastern Plaguelands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='139';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Ghostlands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3433';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='10' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Hillsbrad Foothills
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='267';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='15' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Kelp'thar Forest
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='4815';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='80' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Northern Stranglethorn
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='33';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='25' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Redridge Mountains
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='44';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='15' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Searing Gorge
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='51';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Silverpine Forest
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='130';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='10' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Stranglethorn Vale
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='5339';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='30' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='50' WHERE `LevelScalingMax`='0';

-- Swamp of Sorrows
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='8';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='40' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- The Cape of Stranglethorn
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='5287';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='30' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- The Hinterlands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='47';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='30' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Twilight Highlands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='4922';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='84' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Western Plaguelands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='28';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='35' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Westfall
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='40';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='10' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Wetlands
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='11';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='25' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='60' WHERE `LevelScalingMax`='0';

-- Abyssal Depths
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='5145';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='82' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Shimmering Expanse
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='0' AND `zoneId`='5144';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='81' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Blade's Edge Mountains
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3522';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='65' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Hellfire Peninsula
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3483';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='58' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Nagrand
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3518';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='64' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Netherstorm
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3523';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='67' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Shadowmoon Valley
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3520';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='67' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Terokkar Forest
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3519';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='62' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Zangarmarsh
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='530' AND `zoneId`='3521';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='60' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Borean Tundra
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='3537';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='58' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Crystalsong Forest
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='2817';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='67' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Dragonblight
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='65';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='61' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Grizzly Hills
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='394';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='63' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Howling Fjord
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='495';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='58' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Hrothgar's Landing
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='4742';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='67' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Icecrown
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='210';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='67' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Sholazar Basin
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='3711';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='66' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- The Storm Peaks
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='67';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='67' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Wintergrasp
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='4197';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='67' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Zul'Drak
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='571' AND `zoneId`='66';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='64' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='80' WHERE `LevelScalingMax`='0';

-- Dread Wastes
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='6138';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='84' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Isle of Giants
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='6661';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='85' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Krasarang Wilds
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='6134';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='81' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Kun-Lai Summit
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='5841';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='82' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- The Jade Forest
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='5785';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='80' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Timeless Isle
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='6757';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='85' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Townlong Steppes
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='5842';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='83' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Vale of Eternal Blossoms
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='5840';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='85' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Valley of the Four Winds
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='870' AND `zoneId`='5805';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='81' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='90' WHERE `LevelScalingMax`='0';

-- Nagrand
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1116' AND `zoneId`='5805';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='98' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='100' WHERE `LevelScalingMax`='0';

-- Spires of Arak
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1116' AND `zoneId`='6722';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='96' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='100' WHERE `LevelScalingMax`='0';

-- Talador
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1116' AND `zoneId`='6662';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='94' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='100' WHERE `LevelScalingMax`='0';

-- Gorgrond
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1116' AND `zoneId`='6721';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='92' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='100' WHERE `LevelScalingMax`='0';

-- Frostfire Ridge
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1116' AND `zoneId`='6720';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='90' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='100' WHERE `LevelScalingMax`='0';

-- Shadowmoon Valley
REPLACE INTO `creature_template_scaling` (`Entry`) SELECT `id` FROM `creature` WHERE `map`='1116' AND `zoneId`='6719';
UPDATE `creature_template_scaling` SET `LevelScalingMin`='90' WHERE `LevelScalingMin`='0';
UPDATE `creature_template_scaling` SET `LevelScalingMax`='100' WHERE `LevelScalingMax`='0';