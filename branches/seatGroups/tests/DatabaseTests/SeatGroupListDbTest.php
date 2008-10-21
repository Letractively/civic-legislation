<?php
require_once 'PHPUnit/Framework.php';

class SeatGroupListDbTest extends PHPUnit_Framework_TestCase
{
	protected $committee;
	protected $seatGroup;

	protected function setUp()
	{
		$dir = dirname(__FILE__);
		exec('/usr/local/mysql/bin/mysql -u '.DB_USER.' -p'.DB_PASS.' '.DB_NAME." < $dir/../testData.sql\n");

		$PDO = Database::getConnection();

		$committee = new Committee();
		$committee->setName('Seat Test Committee');
		$committee->save();
		$this->committee = $committee;

		$seatGroup = new SeatGroup();
		$seatGroup->setName('Test Group');
		$seatGroup->setCommittee($committee);
		$seatGroup->save();
		$this->seatGroup = $seatGroup;
	}

	/**
	 * SeatGroups should be ordered alphabetically
	 */
	public function testFind()
	{
		$seatGroup = new SeatGroup();
		$seatGroup->setCommittee($this->committee);
		$seatGroup->setName('Test SeatGroup');
		$seatGroup->save();

		$seatGroup = new SeatGroup();
		$seatGroup->setCommittee($this->committee);
		$seatGroup->setName('Another Test SeatGroup');
		$seatGroup->save();

		$PDO = Database::getConnection();
		$query = $PDO->query('select name from seatGroups order by name');
		$result = $query->fetchAll();

		$list = new SeatGroupList();
		$list->find();
		foreach($list as $i=>$seatGroup)
		{
			$this->assertEquals($seatGroup->getName(),$result[$i]['name']);
		}
	}
}
