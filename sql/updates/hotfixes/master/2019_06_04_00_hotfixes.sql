/*Table structure for table `adventure_journal` */

DROP TABLE IF EXISTS `adventure_journal`;

CREATE TABLE `adventure_journal` (
  `ID` int(10) NOT NULL,
  `Name` text,
  `Description` text,
  `ButtonText` text,
  `RewardDescription` text,
  `ContinueDescription` text,
  `Type` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `PlayerCondition` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `ButtonActionType` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `TextureFileDataID` int(10) NOT NULL DEFAULT '0',
  `LfgDungeonID` smallint(6) unsigned NOT NULL DEFAULT '0',
  `QuestID` smallint(6) unsigned NOT NULL DEFAULT '0',
  `BattleMasterListID` smallint(6) unsigned NOT NULL DEFAULT '0',
  `PriorityMin` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `PriorityMax` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `ItemID` int(10) NOT NULL DEFAULT '0',
  `ItemQuantity` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyType` smallint(6) unsigned NOT NULL DEFAULT '0',
  `CurrencyQuantity` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `UIMapID` smallint(6) unsigned NOT NULL DEFAULT '0',
  `BonusPlayerConditionID1` int(10) unsigned NOT NULL DEFAULT '0',
  `BonusPlayerConditionID2` int(10) unsigned NOT NULL DEFAULT '0',
  `BonusValue1` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `BonusValue2` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` smallint(6) unsigned DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;