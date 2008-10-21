<?php
require_once 'PHPUnit/Framework.php';

class SeatGroupDbTest extends PHPUnit_Framework_TestCase
{
	protected $committee;
	protected $appointer;

	protected function setUp()
	{
		$dir = dirname(__FILE__);
		exec('/usr/local/mysql/bin/mysql -u '.DB_USER.' -p'.DB_PASS.' '.DB_NAME." < $dir/../testData.sql\n");

		$PDO = Database::getConnection();

		$committee = new Committee();
		$committee->setName('SeatGroup Test Committee');
		$committee->save();
		$this->committee = $committee;

		$appointer = new Appointer();
		$appointer->setName('SeatGroup Test Appointer');
		$appointer->save();
		$this->appointer = $appointer;
	}

	public function testSetCommitte()
	{
		$seatGroup = new SeatGroup();
		$seatGroup->setCommittee_id($this->committee->getId());
		$this->assertEquals($seatGroup->getCommittee()->getId(),$this->committee->getId());

		$seatGroup = new SeatGroup();
		$seatGroup->setCommittee($this->committee);
		$this->assertEquals($seatGroup->getCommittee_id(),$this->committee->getId());
	}

	public function testSetAppointer()
	{
		$seatGroup = new SeatGroup();
		$seatGroup->setAppointer($this->appointer);
		$this->assertEquals($seatGroup->getAppointer_id(),$this->appointer->getId());

		$seatGroup = new SeatGroup();
		$seatGroup->setAppointer_id($this->appointer->getId());
		$this->assertEquals($seatGroup->getAppointer()->getId(),$this->appointer->getId());
	}

	public function testValidate()
	{
		$seatGroup = new SeatGroup();
		$seatGroup->setName('Test SeatGroup');
		$seatGroup->setCommittee($this->committee);
		try { $seatGroup->validate(); }
		catch (Exception $e)
		{
			$this->fail('Validation failed even when all required fields were set');
		}

		$seatGroup->setName('');
		try
		{
			$seatGroup->validate();
			$this->fail('Missing Name failed to throw validation error.');
		}
		catch (Exception $e) { }

		$seatGroup->setName('Test SeatGroup');
		$seatGroup->setCommittee_id(null);
		try
		{
			$seatGroup->validate();
			$this->fail('Missing committee failed to throw validation error.');
		}
		catch (Exception $e) { }
	}

	public function testSaveAndLoad()
	{
		$seatGroup = new SeatGroup();
		$seatGroup->setName('Test SeatGroup');
		$seatGroup->setCommittee($this->committee);

		$seatGroup->save();
		$id = $seatGroup->getId();
		$this->assertGreaterThan(0,$id);

		$seatGroup = new SeatGroup($id);
		$seatGroup->setName('Updated Test Name');
		$seatGroup->save();

		$seatGroup = new SeatGroup($id);
		$this->assertEquals($seatGroup->getName(),'Updated Test Name');
	}

	public function testRequirements()
	{
		$requirement = new Requirement();
		$requirement->setText('Test Requirement');
		$requirement->save();

		$seatGroup = new SeatGroup();
		$seatGroup->setName('Test SeatGroup');
		$seatGroup->setCommittee($this->committee);
		$seatGroup->save();

		$seatGroup->addRequirement($requirement);
		$this->assertTrue($seatGroup->hasRequirement($requirement));

		$seatGroup->removeRequirement($requirement);
		$this->assertFalse($seatGroup->hasRequirement($requirement));
	}

	public function testGetSeats()
	{
		$seatGroup = new SeatGroup();
		$seatGroup->setName('Test SeatGroup');
		$seatGroup->setCommittee($this->committee);
		$seatGroup->save();
	}

	public function testGetMembers()
	{
		$list = new SeatGroupList();
		$list->find();
		foreach($list as $seatGroup)
		{
			foreach($seatGroup->getMembers() as $member)
			{
				$this->assertEquals($member->getSeatGroup()->getId(),$seatGroup->getId());
			}
		}
	}
}
