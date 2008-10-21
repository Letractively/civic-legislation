<?php
require_once 'PHPUnit/Framework.php';

class SeatDbTest extends PHPUnit_Framework_TestCase
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

	public function testValidate()
	{
		$seat = new Seat();
		$seat->setTitle('Test Seat');
		$seat->setSeatGroup($this->seatGroup);
		try { $seat->validate(); }
		catch (Exception $e)
		{
			$this->fail('Validation failed even when all required fields were set');
		}

		$seat->setTitle('');
		try
		{
			$seat->validate();
			$this->fail('Missing Title failed to throw validation error.');
		}
		catch (Exception $e) { }

		$seat->setTitle('Test Seat');
		$seat->setSeatGroup_id(null);
		try
		{
			$seat->validate();
			$this->fail('Missing seat group failed to throw validation error.');
		}
		catch (Exception $e) { }
	}

	public function testSaveAndLoad()
	{
		$seat = new Seat();
		$seat->setTitle('Test Seat');
		$seat->setSeatGroup($this->seatGroup);

		$seat->save();
		$id = $seat->getId();
		$this->assertGreaterThan(0,$id);

		$seat = new Seat($id);
		$seat->setTitle('Updated Test Title');
		$seat->save();

		$seat = new Seat($id);
		$this->assertEquals($seat->getTitle(),'Updated Test Title');
	}

	public function testGetCommittee()
	{
		$seat = new Seat();
		$seat->setTitle('Test Seat');
		$seat->setSeatGroup($this->seatGroup);
		$this->assertEquals($seat->getCommittee()->getId(),$this->committee->getId());
	}
}
