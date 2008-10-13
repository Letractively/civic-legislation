<?php
require_once 'PHPUnit/Framework.php';

class PhoneNumberListDbTest extends PHPUnit_Framework_TestCase
{
	protected function setUp()
	{
		$dir = dirname(__FILE__);

		$PDO = Database::getConnection();
		$PDO->exec('drop database '.DB_NAME);
		$PDO->exec('create database '.DB_NAME);
		exec('/usr/local/mysql/bin/mysql -u '.DB_USER.' -p'.DB_PASS.' '.DB_NAME." < $dir/../testData.sql");

		$PDO = Database::getConnection(true);
	}

	/**
	 * Makes sure find returns all phoneNumbers ordered correctly by default
	 */
	public function testFindOrderedByOrdering()
	{
		$PDO = Database::getConnection();
		$query = $PDO->query('select id from phoneNumbers order by ordering');
		$result = $query->fetchAll();

		$list = new PhoneNumberList();
		$list->find();
		$this->assertEquals($list->getSort(),'ordering');

		foreach($list as $i=>$phonenumber)
		{
			$this->assertEquals($phonenumber->getId(),$result[$i]['id']);
		}
    }
}
