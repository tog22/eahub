-- phpMyAdmin SQL Dump
-- version 3.5.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 20, 2014 at 02:27 PM
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
-- Table structure for table `field_revision_field_over_2013_how_much_in_tota`
--

CREATE TABLE IF NOT EXISTS `field_revision_field_over_2013_how_much_in_tota` (
  `entity_type` varchar(128) NOT NULL DEFAULT '' COMMENT 'The entity type this data is attached to',
  `bundle` varchar(128) NOT NULL DEFAULT '' COMMENT 'The field instance bundle to which this row belongs, used when deleting a field instance',
  `deleted` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'A boolean indicating whether this data item has been deleted',
  `entity_id` int(10) unsigned NOT NULL COMMENT 'The entity id this data is attached to',
  `revision_id` int(10) unsigned NOT NULL COMMENT 'The entity revision id this data is attached to',
  `language` varchar(32) NOT NULL DEFAULT '' COMMENT 'The language for this data item.',
  `delta` int(10) unsigned NOT NULL COMMENT 'The sequence number for this data item, used for multi-value fields',
  `field_over_2013_how_much_in_tota_value` varchar(255) DEFAULT NULL,
  `field_over_2013_how_much_in_tota_format` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`entity_type`,`entity_id`,`revision_id`,`deleted`,`delta`,`language`),
  KEY `entity_type` (`entity_type`),
  KEY `bundle` (`bundle`),
  KEY `deleted` (`deleted`),
  KEY `entity_id` (`entity_id`),
  KEY `revision_id` (`revision_id`),
  KEY `language` (`language`),
  KEY `field_over_2013_how_much_in_tota_format` (`field_over_2013_how_much_in_tota_format`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Revision archive storage for field 12 (field_over_2013...';

--
-- Dumping data for table `field_revision_field_over_2013_how_much_in_tota`
--

INSERT INTO `field_revision_field_over_2013_how_much_in_tota` (`entity_type`, `bundle`, `deleted`, `entity_id`, `revision_id`, `language`, `delta`, `field_over_2013_how_much_in_tota_value`, `field_over_2013_how_much_in_tota_format`) VALUES
('profile2', 'donations', 0, 6, 6, 'und', 0, '£4,800', NULL),
('profile2', 'donations', 0, 9, 9, 'und', 0, '$6000 Canadian', NULL),
('profile2', 'donations', 0, 124, 124, 'und', 0, '$4498 USD', NULL),
('profile2', 'donations', 0, 125, 125, 'und', 0, '$4498 USD', NULL),
('profile2', 'donations', 0, 5113, 5113, 'und', 0, '$2000', NULL),
('profile2', 'donations', 0, 5114, 5114, 'und', 0, '$1475', NULL),
('profile2', 'donations', 0, 5116, 5116, 'und', 0, '110 sfr', NULL),
('profile2', 'donations', 0, 5117, 5117, 'und', 0, 'USD 3600', NULL),
('profile2', 'donations', 0, 5118, 5118, 'und', 0, 'Swiss Francs 1000', NULL),
('profile2', 'donations', 0, 5119, 5119, 'und', 0, '£2050', NULL),
('profile2', 'donations', 0, 5122, 5122, 'und', 0, '$150', NULL),
('profile2', 'donations', 0, 5123, 5123, 'und', 0, '~£10 000', NULL),
('profile2', 'donations', 0, 5127, 5127, 'und', 0, '$0', NULL),
('profile2', 'donations', 0, 5128, 5128, 'und', 0, '20000', NULL),
('profile2', 'donations', 0, 5129, 5129, 'und', 0, '25000', NULL),
('profile2', 'donations', 0, 5130, 5130, 'und', 0, '$4498 USD', NULL),
('profile2', 'donations', 0, 5132, 5132, 'und', 0, '14k USD', NULL),
('profile2', 'donations', 0, 5133, 5133, 'und', 0, '6000', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 0, '$50,000', NULL),
('profile2', 'donations', 0, 5137, 5137, 'und', 0, 'approx 200 USD', NULL),
('profile2', 'donations', 0, 5138, 5138, 'und', 0, '1500', NULL),
('profile2', 'donations', 0, 5141, 5141, 'und', 0, 'USD 3000', NULL),
('profile2', 'donations', 0, 5142, 5142, 'und', 0, 'USD 3000', NULL),
('profile2', 'donations', 0, 5143, 5143, 'und', 0, '$1000', NULL),
('profile2', 'donations', 0, 5149, 5149, 'und', 0, '60000', NULL),
('profile2', 'donations', 0, 5152, 5152, 'und', 0, 'AU $4000', NULL),
('profile2', 'donations', 0, 5157, 5157, 'und', 0, '11300', NULL),
('profile2', 'donations', 0, 5158, 5158, 'und', 0, '5000', NULL),
('profile2', 'donations', 0, 5159, 5159, 'und', 0, '1715', NULL),
('profile2', 'donations', 0, 5160, 5160, 'und', 0, '$15000', NULL),
('profile2', 'donations', 0, 5161, 5161, 'und', 0, '120 € Finland', NULL),
('profile2', 'donations', 0, 5162, 5162, 'und', 0, '$0', NULL),
('profile2', 'donations', 0, 5164, 5164, 'und', 0, 'USD 240', NULL),
('profile2', 'donations', 0, 5165, 5165, 'und', 0, '7000 USD', NULL),
('profile2', 'donations', 0, 5166, 5166, 'und', 0, 'NZ$200', NULL),
('profile2', 'donations', 0, 5169, 5169, 'und', 0, '6 USD', NULL),
('profile2', 'donations', 0, 5171, 5171, 'und', 0, '~200 NZD', NULL),
('profile2', 'donations', 0, 5172, 5172, 'und', 0, '0', NULL),
('profile2', 'donations', 0, 5173, 5173, 'und', 0, 'AUS $450', NULL),
('profile2', 'donations', 0, 5177, 5177, 'und', 0, '€1,046.00', NULL),
('profile2', 'donations', 0, 5178, 5178, 'und', 0, '$9,562.50', NULL),
('profile2', 'donations', 0, 5179, 5179, 'und', 0, '6000', NULL),
('profile2', 'donations', 0, 5180, 5180, 'und', 0, 'around 25 Canadian $', NULL),
('profile2', 'donations', 0, 5181, 5181, 'und', 0, 'US $11500', NULL),
('profile2', 'donations', 0, 5184, 5184, 'und', 0, '16500 USD', NULL),
('profile2', 'donations', 0, 5186, 5186, 'und', 0, '0', NULL),
('profile2', 'donations', 0, 5187, 5187, 'und', 0, 'Australian $0', NULL),
('profile2', 'donations', 0, 5188, 5188, 'und', 0, 'AUD$6,700', NULL),
('profile2', 'donations', 0, 5189, 5189, 'und', 0, '$2,000,000+', NULL),
('profile2', 'donations', 0, 5190, 5190, 'und', 0, '£840', NULL),
('profile2', 'donations', 0, 5191, 5191, 'und', 0, '$3600', NULL),
('profile2', 'donations', 0, 5192, 5192, 'und', 0, '100', NULL),
('profile2', 'donations', 0, 5193, 5193, 'und', 0, '0', NULL),
('profile2', 'donations', 0, 5194, 5194, 'und', 0, 'US$22,000', NULL),
('profile2', 'donations', 0, 5202, 5202, 'und', 0, '$5100', NULL),
('profile2', 'donations', 0, 5203, 5203, 'und', 0, 'US $10,000', NULL),
('profile2', 'donations', 0, 5204, 5204, 'und', 0, '500', NULL),
('profile2', 'donations', 0, 5205, 5205, 'und', 0, '$100', NULL),
('profile2', 'donations', 0, 5206, 5206, 'und', 0, '£1130', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 0, '6000', NULL),
('profile2', 'donations', 0, 5210, 5210, 'und', 0, '$4000-6000AUD', NULL),
('profile2', 'donations', 0, 5212, 5212, 'und', 0, '2000', NULL),
('profile2', 'donations', 0, 5213, 5213, 'und', 0, '500', NULL),
('profile2', 'donations', 0, 5215, 5215, 'und', 0, '200', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 0, '180 EUR (Netherlands)', NULL),
('profile2', 'donations', 0, 5218, 5218, 'und', 0, '650', NULL),
('profile2', 'donations', 0, 5219, 5219, 'und', 0, '0', NULL),
('profile2', 'donations', 0, 5220, 5220, 'und', 0, '100 euro', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 0, '180', NULL),
('profile2', 'donations', 0, 5222, 5222, 'und', 0, '0', NULL),
('profile2', 'donations', 0, 5223, 5223, 'und', 0, '$100', NULL),
('profile2', 'donations', 0, 5225, 5225, 'und', 0, 'UK £2,800', NULL),
('profile2', 'donations', 0, 5229, 5229, 'und', 0, '~60k', NULL),
('profile2', 'donations', 0, 5230, 5230, 'und', 0, '3209.79', NULL);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
