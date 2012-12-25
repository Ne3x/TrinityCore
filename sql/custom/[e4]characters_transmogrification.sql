
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET FOREIGN_KEY_CHECKS=0 */;

-- Dumping structure for table transmogrification
CREATE TABLE IF NOT EXISTS `transmogrification` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `fakeEntry` int(10) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table transmogrification: ~0 rows (approximately)
/*!40000 ALTER TABLE `transmogrification` DISABLE KEYS */;
/*!40000 ALTER TABLE `transmogrification` ENABLE KEYS */;
/*!40014 SET FOREIGN_KEY_CHECKS=1 */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
