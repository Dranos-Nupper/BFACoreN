-- ----------------------------
-- Table structure for `achats`
-- ----------------------------
DROP TABLE IF EXISTS `achats`;
CREATE TABLE `achats` (
  `account_id` int(10) unsigned NOT NULL,
  `id` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`account_id`,`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of achats
-- ----------------------------

-- ----------------------------
-- Table structure for `battlepay_groups`
-- ----------------------------
DROP TABLE IF EXISTS `battlepay_groups`;
CREATE TABLE `battlepay_groups` (
  `id` int(10) DEFAULT NULL,
  `ordering` int(11) DEFAULT NULL,
  `name` varchar(60) DEFAULT NULL,
  `iconFileDataId` int(10) DEFAULT NULL,
  `displayType` tinyint(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of battlepay_groups
-- ----------------------------

-- ----------------------------
-- Table structure for `battlepay_products`
-- ----------------------------
DROP TABLE IF EXISTS `battlepay_products`;
CREATE TABLE `battlepay_products` (
  `id` int(10) DEFAULT NULL,
  `itemId` int(10) DEFAULT NULL,
  `quantity` int(10) DEFAULT NULL,
  `groupId` int(10) DEFAULT NULL,
  `ordering` int(11) DEFAULT NULL,
  `bannerType` tinyint(4) DEFAULT NULL,
  `price` float DEFAULT NULL,
  `choiceType` tinyint(3) DEFAULT NULL,
  `serverHardcodedId` int(10) DEFAULT NULL,
  `displayCreature` int(10) DEFAULT NULL,
  `displayFileData` int(10) DEFAULT NULL,
  `displayItem` int(10) DEFAULT NULL,
  `displayCustomItemDeliveryId` int(10) DEFAULT NULL,
  `customFlags` int(10) DEFAULT NULL,
  `customValue` int(11) DEFAULT NULL,
  `logType` int(10) DEFAULT NULL,
  `name` varchar(210) DEFAULT NULL,
  `description` varchar(3000) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of battlepay_products
-- ----------------------------

-- ----------------------------
-- Table structure for `points`
-- ----------------------------
DROP TABLE IF EXISTS `points`;
CREATE TABLE `points` (
  `account_id` int(10) unsigned NOT NULL,
  `nbPoints` float(10,0) NOT NULL DEFAULT '0',
  PRIMARY KEY (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of points
-- ----------------------------

-- ----------------------------
-- Table structure for `updates`
-- ----------------------------
DROP TABLE IF EXISTS `updates`;
CREATE TABLE `updates` (
  `name` varchar(200) NOT NULL COMMENT 'filename with extension of the update.',
  `hash` char(40) DEFAULT '' COMMENT 'sha1 hash of the sql file.',
  `state` enum('RELEASED','ARCHIVED') NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if an update is released or archived.',
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'timestamp when the query was applied.',
  `speed` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'time the query takes to apply in ms.',
  PRIMARY KEY (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='List of all applied updates in this database.';

-- ----------------------------
-- Records of updates
-- ----------------------------
INSERT INTO `updates` VALUES ('2018_12_10_01_battlepay.sql', 'E8EC68DAFFEC354F401F7F55377F03FD426D408F', 'RELEASED', '2019-02-15 19:45:46', '52');

-- ----------------------------
-- Table structure for `updates_include`
-- ----------------------------
DROP TABLE IF EXISTS `updates_include`;
CREATE TABLE `updates_include` (
  `path` varchar(200) NOT NULL COMMENT 'directory to include. $ means relative to the source directory.',
  `state` enum('RELEASED','ARCHIVED') NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if the directory contains released or archived updates.',
  PRIMARY KEY (`path`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='List of directories where we want to include sql updates.';

-- ----------------------------
-- Records of updates_include
-- ----------------------------
INSERT INTO `updates_include` VALUES ('$/sql/ashamane/shop', 'RELEASED');
