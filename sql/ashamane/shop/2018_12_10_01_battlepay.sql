DROP TABLE IF EXISTS `battlepay_groups`;
create table `battlepay_groups` (
	`id` int (10),
	`ordering` int (11),
	`name` varchar (60),
	`iconFileDataId` int (10),
	`displayType` tinyint (3)
); 

DROP TABLE IF EXISTS `battlepay_products`;
create table `battlepay_products` (
	`id` int (10),
	`itemId` int (10),
	`quantity` int (10),
	`groupId` int (10),
	`ordering` int (11),
	`bannerType` tinyint (4),
	`price` float ,
	`choiceType` tinyint (3),
	`serverHardcodedId` int (10),
	`displayCreature` int (10),
	`displayFileData` int (10),
	`displayItem` int (10),
	`displayCustomItemDeliveryId` int (10),
	`customFlags` int (10),
	`customValue` int (11),
	`logType` int (10),
	`name` varchar (210),
	`description` varchar (3000)
); 
