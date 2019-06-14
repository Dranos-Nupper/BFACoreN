--
-- Table structure for table `adventure_journal_locale`
--
DROP TABLE IF EXISTS `adventure_journal_locale`;
CREATE TABLE `adventure_journal_locale` ( 
	`ID` INT(10) NOT NULL,
	`locale` VARCHAR(4) NOT NULL,
	`Name_lang` TEXT, 
	`Description_lang` TEXT, 
	`ButtonText_lang` TEXT, 
	`RewardDescription_lang` TEXT, 
	`ContinueDescription_lang` TEXT,
	`VerifiedBuild` SMALLINT(6) NOT NULL,
	PRIMARY KEY (`ID`, `locale`) 
) ENGINE=MYISAM DEFAULT CHARSET=utf8;