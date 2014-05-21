-- phpMyAdmin SQL Dump
-- version 3.5.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 20, 2014 at 02:21 PM
-- Server version: 5.5.33-31.1
-- PHP Version: 5.4.23

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `sant0317_ea`
--

-- --------------------------------------------------------

--
-- Table structure for table `profile`
--

CREATE TABLE IF NOT EXISTS `profile` (
  `pid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Primary Key: Unique profile item ID.',
  `type` varchar(32) NOT NULL DEFAULT '' COMMENT 'The profile_type.type of this profile.',
  `uid` int(10) unsigned DEFAULT NULL COMMENT 'The users.uid of the associated user.',
  `label` varchar(255) NOT NULL DEFAULT '' COMMENT 'A human-readable label for this profile.',
  `created` int(11) DEFAULT NULL COMMENT 'The Unix timestamp when the profile was created.',
  `changed` int(11) DEFAULT NULL COMMENT 'The Unix timestamp when the profile was most recently saved.',
  PRIMARY KEY (`pid`),
  KEY `uid` (`uid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Stores profile items.' AUTO_INCREMENT=5951 ;

--
-- Dumping data for table `profile`
--

INSERT INTO `profile` (`pid`, `type`, `uid`, `label`, `created`, `changed`) VALUES
(6, 'donations', 1, 'Donations', 1398713293, 1398714665),
(9, 'donations', 21, 'Donations', 1398716440, 1398718471),
(121, 'donations', NULL, 'Donations', 1399429084, 1399429084),
(124, 'donations', NULL, 'Donations', 1399503976, 1399503976),
(125, 'donations', NULL, 'Donations', 1399524375, 1399524375),
(5111, 'donations', 984, 'Donations', 1400541666, 1400541666),
(5112, 'donations', 985, 'Donations', 1400541666, 1400541666),
(5113, 'donations', 986, 'Donations', 1400541666, 1400541666),
(5114, 'donations', 987, 'Donations', 1400541666, 1400541666),
(5115, 'donations', 988, 'Donations', 1400541666, 1400541666),
(5116, 'donations', 989, 'Donations', 1400541666, 1400541666),
(5117, 'donations', 990, 'Donations', 1400541666, 1400541666),
(5118, 'donations', 991, 'Donations', 1400541666, 1400541666),
(5119, 'donations', 992, 'Donations', 1400541666, 1400541666),
(5120, 'donations', 993, 'Donations', 1400541666, 1400541666),
(5121, 'donations', 994, 'Donations', 1400541666, 1400541666),
(5122, 'donations', 995, 'Donations', 1400541666, 1400541666),
(5123, 'donations', 996, 'Donations', 1400541666, 1400541666),
(5124, 'donations', 997, 'Donations', 1400541666, 1400541666),
(5125, 'donations', 998, 'Donations', 1400541666, 1400541666),
(5126, 'donations', 999, 'Donations', 1400541666, 1400541666),
(5127, 'donations', 1000, 'Donations', 1400541666, 1400541666),
(5128, 'donations', 1001, 'Donations', 1400541666, 1400541666),
(5129, 'donations', 1002, 'Donations', 1400541666, 1400541666),
(5130, 'donations', 1003, 'Donations', 1400541666, 1400541666),
(5131, 'donations', 1004, 'Donations', 1400541666, 1400541666),
(5132, 'donations', 1005, 'Donations', 1400541666, 1400541666),
(5133, 'donations', 1006, 'Donations', 1400541666, 1400541666),
(5134, 'donations', 1007, 'Donations', 1400541666, 1400541666),
(5135, 'donations', 1008, 'Donations', 1400541666, 1400541666);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
