<?php
require_once 'PHPUnit/Framework.php';

class RequirementListDbTest extends PHPUnit_Framework_TestCase
{
	protected function setUp()
	{
		$dir = dirname(__FILE__);
		exec('/usr/local/mysql/bin/mysql -u '.DB_USER.' -p'.DB_PASS.' '.DB_NAME." < $dir/../testData.sql\n");

	}

	/**
	 * Requirements should always be ordered alphabetically
	 */
	public function testFindOrderedAlphabetically()
	{
		$requirement = new Requirement();
		$requirement->setText('Test Requirement');
		$requirement->save();

		$requirement = new Requirement();
		$requirement->setText('Another Requirement');
		$requirement->save();

		$PDO = Database::getConnection();
		$query = $PDO->query('select text from requirements order by text');
		$result = $query->fetchAll();

		$list = new RequirementList();
		$list->find();
		foreach($list as $i=>$requirement)
		{
			$this->assertEquals($requirement->getText(),$result[$i]['text']);
		}
	}

	public function testFindBySeatGroup()
	{
		$committee = new Committee();
		$committee->setName('SeatGroup Test Committee');
		$committee->save();

		$appointer = new Appointer();
		$appointer->setName('SeatGroup Test Appointer');
		$appointer->save();

		$seatGroup = new SeatGroup();
		$seatGroup->setName('Test SeatGroup');
		$seatGroup->setCommittee($committee);
		$seatGroup->setAppointer($appointer);
		$seatGroup->save();

		$requirement = new Requirement();
		$requirement->setText('Test Requirement');
		$requirement->save();
		$seatGroup->addRequirement($requirement);

		$requirement = new Requirement();
		$requirement->setText('Another Requirement');
		$requirement->save();
		$seatGroup->addRequirement($requirement);

		$list = new RequirementList(array('seatGroup_id'=>$seatGroup->getId()));
		foreach($list as $requirement)
		{
			$this->assertTrue($seatGroup->hasRequirement($requirement));
		}
	}
}
