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
-- Table structure for table `field_data_field_over_2013_which_charities_`
--

CREATE TABLE IF NOT EXISTS `field_data_field_over_2013_which_charities_` (
  `entity_type` varchar(128) NOT NULL DEFAULT '' COMMENT 'The entity type this data is attached to',
  `bundle` varchar(128) NOT NULL DEFAULT '' COMMENT 'The field instance bundle to which this row belongs, used when deleting a field instance',
  `deleted` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'A boolean indicating whether this data item has been deleted',
  `entity_id` int(10) unsigned NOT NULL COMMENT 'The entity id this data is attached to',
  `revision_id` int(10) unsigned DEFAULT NULL COMMENT 'The entity revision id this data is attached to, or NULL if the entity type is not versioned',
  `language` varchar(32) NOT NULL DEFAULT '' COMMENT 'The language for this data item.',
  `delta` int(10) unsigned NOT NULL COMMENT 'The sequence number for this data item, used for multi-value fields',
  `field_over_2013_which_charities__value` varchar(255) DEFAULT NULL,
  `field_over_2013_which_charities__format` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`entity_type`,`entity_id`,`deleted`,`delta`,`language`),
  KEY `entity_type` (`entity_type`),
  KEY `bundle` (`bundle`),
  KEY `deleted` (`deleted`),
  KEY `entity_id` (`entity_id`),
  KEY `revision_id` (`revision_id`),
  KEY `language` (`language`),
  KEY `field_over_2013_which_charities__format` (`field_over_2013_which_charities__format`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Data storage for field 14 (field_over_2013_which_charities_)';

--
-- Dumping data for table `field_data_field_over_2013_which_charities_`
--

INSERT INTO `field_data_field_over_2013_which_charities_` (`entity_type`, `bundle`, `deleted`, `entity_id`, `revision_id`, `language`, `delta`, `field_over_2013_which_charities__value`, `field_over_2013_which_charities__format`) VALUES
('profile2', 'donations', 0, 6, 6, 'und', 0, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 9, 9, 'und', 0, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 9, 9, 'und', 1, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 9, 9, 'und', 2, 'Effective fundraising', NULL),
('profile2', 'donations', 0, 124, 124, 'und', 0, 'Animal Charity Evaluators (formerly Effective Animal Activism), The Humane League, Vegan Outreach', NULL),
('profile2', 'donations', 0, 125, 125, 'und', 0, 'Animal Charity Evaluators, The Humane League, Vegan Outreach', NULL),
('profile2', 'donations', 0, 5113, 5113, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5113, 5113, 'und', 1, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5113, 5113, 'und', 2, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5113, 5113, 'und', 3, 'The Humane League', NULL),
('profile2', 'donations', 0, 5113, 5113, 'und', 4, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5114, 5114, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5114, 5114, 'und', 1, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5116, 5116, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5116, 5116, 'und', 1, 'The Humane League', NULL),
('profile2', 'donations', 0, 5116, 5116, 'und', 2, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5117, 5117, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5118, 5118, 'und', 0, 'Effective Altruism Switzerland (EACH)', NULL),
('profile2', 'donations', 0, 5119, 5119, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5122, 5122, 'und', 0, 'Animal Ethics', NULL),
('profile2', 'donations', 0, 5123, 5123, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5123, 5123, 'und', 1, 'Project Healthy Children', NULL),
('profile2', 'donations', 0, 5123, 5123, 'und', 2, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5123, 5123, 'und', 3, 'Global poverty via trusts. Also donation to CEA for research.', NULL),
('profile2', 'donations', 0, 5128, 5128, 'und', 0, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5128, 5128, 'und', 1, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5128, 5128, 'und', 2, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5129, 5129, 'und', 0, 'Animal Charity Evaluators', NULL),
('profile2', 'donations', 0, 5130, 5130, 'und', 0, 'Animal Charity Evaluators', NULL),
('profile2', 'donations', 0, 5130, 5130, 'und', 1, 'The Humane League', NULL),
('profile2', 'donations', 0, 5130, 5130, 'und', 2, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5132, 5132, 'und', 0, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5132, 5132, 'und', 1, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5132, 5132, 'und', 2, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5133, 5133, 'und', 0, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5133, 5133, 'und', 1, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 0, '80,000 Hours', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 1, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 2, 'The Centre for Effective Altruism (unrestricted donation)', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 3, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 4, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 5, 'Giving What We Can (itself)', NULL),
('profile2', 'donations', 0, 5135, 5135, 'und', 6, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5137, 5137, 'und', 0, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5138, 5138, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5138, 5138, 'und', 1, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5138, 5138, 'und', 2, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5138, 5138, 'und', 3, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5141, 5141, 'und', 0, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5141, 5141, 'und', 1, 'Dispensers for Safe Water', NULL),
('profile2', 'donations', 0, 5142, 5142, 'und', 0, 'Animal Charity Evaluators', NULL),
('profile2', 'donations', 0, 5142, 5142, 'und', 1, 'Giving What We Can (itself)', NULL),
('profile2', 'donations', 0, 5143, 5143, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5143, 5143, 'und', 1, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5143, 5143, 'und', 2, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5149, 5149, 'und', 0, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5152, 5152, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5152, 5152, 'und', 1, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5152, 5152, 'und', 2, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5157, 5157, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5157, 5157, 'und', 1, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5157, 5157, 'und', 2, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5157, 5157, 'und', 3, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5158, 5158, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5159, 5159, 'und', 0, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5160, 5160, 'und', 0, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5160, 5160, 'und', 1, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5161, 5161, 'und', 0, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5161, 5161, 'und', 1, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5164, 5164, 'und', 0, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5164, 5164, 'und', 1, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5164, 5164, 'und', 2, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5165, 5165, 'und', 0, '80,000 Hours', NULL),
('profile2', 'donations', 0, 5165, 5165, 'und', 1, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5165, 5165, 'und', 2, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5165, 5165, 'und', 3, 'Leverage Research', NULL),
('profile2', 'donations', 0, 5165, 5165, 'und', 4, 'Project Healthy Children', NULL),
('profile2', 'donations', 0, 5165, 5165, 'und', 5, 'TAM TAM', NULL),
('profile2', 'donations', 0, 5166, 5166, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5169, 5169, 'und', 0, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5171, 5171, 'und', 0, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5171, 5171, 'und', 1, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5173, 5173, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5173, 5173, 'und', 1, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5173, 5173, 'und', 2, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5176, 5176, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5176, 5176, 'und', 1, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5176, 5176, 'und', 2, 'FHI', NULL),
('profile2', 'donations', 0, 5177, 5177, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5177, 5177, 'und', 1, 'UNICEF', NULL),
('profile2', 'donations', 0, 5178, 5178, 'und', 0, 'Animal Charity Evaluators', NULL),
('profile2', 'donations', 0, 5178, 5178, 'und', 1, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5178, 5178, 'und', 2, 'The Humane League', NULL),
('profile2', 'donations', 0, 5178, 5178, 'und', 3, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5178, 5178, 'und', 4, 'Alliance for Animals and the Environment, New Harvest', NULL),
('profile2', 'donations', 0, 5179, 5179, 'und', 0, 'OXFAM', NULL),
('profile2', 'donations', 0, 5180, 5180, 'und', 0, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5180, 5180, 'und', 1, 'Mars-One', NULL),
('profile2', 'donations', 0, 5181, 5181, 'und', 0, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5181, 5181, 'und', 1, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5184, 5184, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5188, 5188, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5188, 5188, 'und', 1, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5188, 5188, 'und', 2, 'Project Healthy Children', NULL),
('profile2', 'donations', 0, 5188, 5188, 'und', 3, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5188, 5188, 'und', 4, 'Oxfam, Bush Heritage, Fred Hollows', NULL),
('profile2', 'donations', 0, 5189, 5189, 'und', 0, 'See GreenbaumFoundation website', NULL),
('profile2', 'donations', 0, 5190, 5190, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5191, 5191, 'und', 0, 'The Humane League', NULL),
('profile2', 'donations', 0, 5191, 5191, 'und', 1, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5192, 5192, 'und', 0, 'wikipedia', NULL),
('profile2', 'donations', 0, 5194, 5194, 'und', 0, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5194, 5194, 'und', 1, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5194, 5194, 'und', 2, 'Future of Humanity Institute', NULL),
('profile2', 'donations', 0, 5202, 5202, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5202, 5202, 'und', 1, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5203, 5203, 'und', 0, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5203, 5203, 'und', 1, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5204, 5204, 'und', 0, 'Animal Charity Evaluators', NULL),
('profile2', 'donations', 0, 5204, 5204, 'und', 1, 'Earthics Foundation', NULL),
('profile2', 'donations', 0, 5205, 5205, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5206, 5206, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5206, 5206, 'und', 1, 'The Centre for Effective Altruism (unrestricted donation)', NULL),
('profile2', 'donations', 0, 5206, 5206, 'und', 2, 'Giving What We Can (itself)', NULL),
('profile2', 'donations', 0, 5206, 5206, 'und', 3, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5206, 5206, 'und', 4, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5206, 5206, 'und', 5, 'Oxfam, The Life You Can Save, Peace Direct, UNICEF, Save the Children, Global Poverty Project, Tackle Africa, Care USA, Martlets Hospice, Compassion in World Farming. RAG Oxford, Medical Aid Films, Helen Bamber Foundation, Kawempe Home Care', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 1, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 2, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 3, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 4, 'Giving What We Can (itself)', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 5, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 6, 'Project Healthy Children', NULL),
('profile2', 'donations', 0, 5208, 5208, 'und', 7, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5210, 5210, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5210, 5210, 'und', 1, 'Running costs and copies of The Life You Can Save for the Run to Better Days', NULL),
('profile2', 'donations', 0, 5212, 5212, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5213, 5213, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5213, 5213, 'und', 1, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5213, 5213, 'und', 2, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5215, 5215, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 0, '80,000 Hours', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 1, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 2, 'Animal Charity Evaluators', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 3, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 4, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 5, 'The Humane League', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 6, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5216, 5216, 'und', 7, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5218, 5218, 'und', 0, '80,000 Hours', NULL),
('profile2', 'donations', 0, 5218, 5218, 'und', 1, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5218, 5218, 'und', 2, 'Project Healthy Children', NULL),
('profile2', 'donations', 0, 5218, 5218, 'und', 3, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5220, 5220, 'und', 0, 'Hospic Slovenija', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 1, 'Center For Applied Rationality', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 2, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 3, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 4, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 5, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5221, 5221, 'und', 6, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5223, 5223, 'und', 0, 'Local', NULL),
('profile2', 'donations', 0, 5225, 5225, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5225, 5225, 'und', 1, 'The Centre for Effective Altruism (unrestricted donation)', NULL),
('profile2', 'donations', 0, 5225, 5225, 'und', 2, 'Deworm the World', NULL),
('profile2', 'donations', 0, 5225, 5225, 'und', 3, 'GiveDirectly', NULL),
('profile2', 'donations', 0, 5225, 5225, 'und', 4, 'Project Healthy Children', NULL),
('profile2', 'donations', 0, 5225, 5225, 'und', 5, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5229, 5229, 'und', 0, 'Leverage Research', NULL),
('profile2', 'donations', 0, 5229, 5229, 'und', 1, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5229, 5229, 'und', 2, 'FHI', NULL),
('profile2', 'donations', 0, 5230, 5230, 'und', 0, 'Against Malaria Foundation', NULL),
('profile2', 'donations', 0, 5230, 5230, 'und', 1, 'GiveWell (itself)', NULL),
('profile2', 'donations', 0, 5230, 5230, 'und', 2, 'Machine Intelligence Research Institute', NULL),
('profile2', 'donations', 0, 5230, 5230, 'und', 3, 'Schistosomiasis Control Initiative (SCI)', NULL),
('profile2', 'donations', 0, 5230, 5230, 'und', 4, 'Vegan Outreach', NULL),
('profile2', 'donations', 0, 5230, 5230, 'und', 5, 'Future of Humanity Institute', NULL);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;