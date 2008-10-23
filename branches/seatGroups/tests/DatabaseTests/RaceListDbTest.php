<?php
require_once 'PHPUnit/Framework.php';

class RaceListDbTest extends PHPUnit_Framework_TestCase
{
	protected function setUp()
	{
		$dir = dirname(__FILE__);
		exec('/usr/local/mysql/bin/mysql -u '.DB_USER.' -p'.DB_PASS.' '.DB_NAME." < $dir/../testData.sql\n");
	}

	/**
	 * Makes sure find returns all Races ordered by name
	 */
	public function testFindOrderedByName()
	{
		$PDO = Database::getConnection();
		$query = $PDO->query('select name from races order by name');
		$result = $query->fetchAll();

    	$list = new RaceList();
    	$list->find();
    	$this->assertEquals($list->getSort(),'name');

    	foreach($list as $i=>$race)
    	{
    		$this->assertEquals($race->getName(),$result[$i]['name']);
    	}
    }
}