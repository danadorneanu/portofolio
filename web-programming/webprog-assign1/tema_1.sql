-- MySQL dump 10.13  Distrib 5.1.37, for debian-linux-gnu (i486)
--
-- Host: localhost    Database: licitatii3
-- ------------------------------------------------------
-- Server version	5.1.37-1ubuntu5

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `citate`
--

DROP TABLE IF EXISTS `citate`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `citate` (
  `id` int(9) unsigned NOT NULL AUTO_INCREMENT,
  `citat` text NOT NULL,
  `autor` varchar(150) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `citate`
--

LOCK TABLES `citate` WRITE;
/*!40000 ALTER TABLE `citate` DISABLE KEYS */;
INSERT INTO `citate` VALUES (1,'Anglia este un leu. Eu i-am imprumutat ragetul ','Churchill'),(2,'Zarurile au fost aruncate ','Caesar'),(3,'Eu cu cine votez','Caragiale'),(4,'Moldova nu e a mea, e a urmasilor, urmasilor vostri, in veacul veacului Amin. ','Stefan cel Mare'),(5,'Sa traiti bine ','Traian Basescu');
/*!40000 ALTER TABLE `citate` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `citate_meta`
--

DROP TABLE IF EXISTS `citate_meta`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `citate_meta` (
  `id` int(11) NOT NULL DEFAULT '0',
  `nr_max` mediumint(9) NOT NULL DEFAULT '0',
  `data_modificarii` mediumint(9) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `citate_meta`
--

LOCK TABLES `citate_meta` WRITE;
/*!40000 ALTER TABLE `citate_meta` DISABLE KEYS */;
INSERT INTO `citate_meta` VALUES (1,3,18);
/*!40000 ALTER TABLE `citate_meta` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cumparatori`
--

DROP TABLE IF EXISTS `cumparatori`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cumparatori` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `mail` varchar(45) NOT NULL,
  `data_nastere` date NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cumparatori`
--

LOCK TABLES `cumparatori` WRITE;
/*!40000 ALTER TABLE `cumparatori` DISABLE KEYS */;
INSERT INTO `cumparatori` VALUES (1,'dana','daniela@yahoo.com','1987-04-28'),(3,'vlad','vlad','1985-06-30'),(4,'vali','vali@mail.ro','1985-07-11'),(5,'mariana','m@m.com','1954-10-05'),(7,'andrei','andrei@gmail.com','1952-03-16'),(8,'adina','adina@ro.ro','1985-07-11');
/*!40000 ALTER TABLE `cumparatori` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `domenii`
--

DROP TABLE IF EXISTS `domenii`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `domenii` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=21 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `domenii`
--

LOCK TABLES `domenii` WRITE;
/*!40000 ALTER TABLE `domenii` DISABLE KEYS */;
INSERT INTO `domenii` VALUES (7,'muzica'),(8,'carti'),(9,'automobile'),(19,'vapoare'),(12,'imbracaminte'),(15,'gradinarit'),(17,'mobila'),(18,'birotica'),(20,'negociabil');
/*!40000 ALTER TABLE `domenii` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `licitatii`
--

DROP TABLE IF EXISTS `licitatii`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `licitatii` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `id_obiecte` int(10) unsigned NOT NULL,
  `id_tip_licitatie` int(10) unsigned NOT NULL,
  `id_cumparatori` int(10) unsigned NOT NULL,
  `suma` int(10) unsigned NOT NULL,
  `data` date NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  KEY `FK_licitatii_1` (`id_obiecte`),
  KEY `FK_licitatii_2` (`id_tip_licitatie`),
  KEY `FK_licitatii_3` (`id_cumparatori`)
) ENGINE=MyISAM AUTO_INCREMENT=23 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `licitatii`
--

LOCK TABLES `licitatii` WRITE;
/*!40000 ALTER TABLE `licitatii` DISABLE KEYS */;
INSERT INTO `licitatii` VALUES (12,10,2,1,60000,'2010-01-03'),(13,7,3,3,789,'2010-01-03'),(14,3,4,1,543,'2010-01-03'),(15,8,3,5,30000,'2010-01-03'),(16,9,3,3,80000,'2010-01-03'),(17,10,3,1,61000,'2010-01-03'),(18,8,3,6,31000,'2010-01-03'),(19,9,3,4,59000,'2010-01-03'),(20,11,3,7,40000,'2010-01-06'),(21,11,3,8,59000,'2010-01-06'),(22,8,3,3,59000,'2010-01-06');
/*!40000 ALTER TABLE `licitatii` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `obiecte`
--

DROP TABLE IF EXISTS `obiecte`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `obiecte` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `id_domenii` int(10) unsigned NOT NULL,
  `id_vanzatori` int(10) unsigned NOT NULL,
  `id_tip_licitatie` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  KEY `FK_obiecte_1` (`id_domenii`),
  KEY `FK_obiecte_2` (`id_vanzatori`)
) ENGINE=MyISAM AUTO_INCREMENT=12 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `obiecte`
--

LOCK TABLES `obiecte` WRITE;
/*!40000 ALTER TABLE `obiecte` DISABLE KEYS */;
INSERT INTO `obiecte` VALUES (3,'rochie de seara',12,3,3),(4,'chitara',7,3,3),(5,'ficus',15,3,3),(6,'block notes',18,1,3),(7,'audi',9,5,3),(8,'logan',9,1,3),(9,'golf',9,3,3),(10,'opel corsa',9,3,3),(11,'Jaguar',9,4,3);
/*!40000 ALTER TABLE `obiecte` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tip_licitatie`
--

DROP TABLE IF EXISTS `tip_licitatie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tip_licitatie` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(80) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tip_licitatie`
--

LOCK TABLES `tip_licitatie` WRITE;
/*!40000 ALTER TABLE `tip_licitatie` DISABLE KEYS */;
INSERT INTO `tip_licitatie` VALUES (2,'Vanzare la pret fix'),(3,'Licitatie standard'),(4,'Licitatie cu pret de pornire'),(5,'Vanzare cu pret negociabil');
/*!40000 ALTER TABLE `tip_licitatie` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vanzatori`
--

DROP TABLE IF EXISTS `vanzatori`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vanzatori` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `mail` varchar(45) NOT NULL,
  `tel` varchar(45) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vanzatori`
--

LOCK TABLES `vanzatori` WRITE;
/*!40000 ALTER TABLE `vanzatori` DISABLE KEYS */;
INSERT INTO `vanzatori` VALUES (1,'cristina','dsada','432424'),(3,'rux','noi@yahoo.com','4535435'),(5,'codrut','codrut@gmail.com','654654'),(4,'vlad','vl@vl.com','+40543');
/*!40000 ALTER TABLE `vanzatori` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-03-23 12:36:41
