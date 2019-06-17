/*
SQLyog Community v13.1.1 (64 bit)
MySQL - 5.5.9-log : Database - shop
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`shop` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `shop`;

/*Table structure for table `achats` */

DROP TABLE IF EXISTS `achats`;

CREATE TABLE `achats` (
  `account_id` int(10) unsigned NOT NULL,
  `id` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`account_id`,`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `achats` */

/*Table structure for table `battlepay_groups` */

DROP TABLE IF EXISTS `battlepay_groups`;

CREATE TABLE `battlepay_groups` (
  `id` int(10) DEFAULT NULL,
  `ordering` int(11) DEFAULT NULL,
  `name` varchar(60) DEFAULT NULL,
  `iconFileDataId` int(10) DEFAULT NULL,
  `displayType` tinyint(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `battlepay_groups` */

/*Table structure for table `battlepay_products` */

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

/*Data for the table `battlepay_products` */

/*Table structure for table `points` */

DROP TABLE IF EXISTS `points`;

CREATE TABLE `points` (
  `account_id` int(10) unsigned NOT NULL,
  `nbPoints` float(10,0) NOT NULL DEFAULT '0',
  PRIMARY KEY (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `points` */

/*Table structure for table `updates` */

DROP TABLE IF EXISTS `updates`;

CREATE TABLE `updates` (
  `name` varchar(200) NOT NULL COMMENT 'filename with extension of the update.',
  `hash` char(40) DEFAULT '' COMMENT 'sha1 hash of the sql file.',
  `state` enum('RELEASED','ARCHIVED') NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if an update is released or archived.',
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'timestamp when the query was applied.',
  `speed` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'time the query takes to apply in ms.',
  PRIMARY KEY (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='List of all applied updates in this database.';

/*Data for the table `updates` */

insert  into `updates`(`name`,`hash`,`state`,`timestamp`,`speed`) values 
('2018_12_10_01_battlepay.sql','E8EC68DAFFEC354F401F7F55377F03FD426D408F','RELEASED','2019-02-15 21:45:46',52);

/*Table structure for table `updates_include` */

DROP TABLE IF EXISTS `updates_include`;

CREATE TABLE `updates_include` (
  `path` varchar(200) NOT NULL COMMENT 'directory to include. $ means relative to the source directory.',
  `state` enum('RELEASED','ARCHIVED') NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if the directory contains released or archived updates.',
  PRIMARY KEY (`path`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='List of directories where we want to include sql updates.';

/*Data for the table `updates_include` */

insert  into `updates_include`(`path`,`state`) values 
('$/sql/ashamane/shop','RELEASED');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
