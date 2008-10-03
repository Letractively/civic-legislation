<?php
require_once 'PHPUnit/Framework.php';

/**
 * Test class for Requirement.
 * Generated by PHPUnit on 2008-09-29 at 10:54:58.
 */
class RequirementTest extends PHPUnit_Framework_TestCase
{
	protected $test_id;

	public function testTextChanging()
	{
		$requirement = new Requirement();
		$requirement->setText('another test');
		$this->assertEquals($requirement->getText(),'another test');
	}

	public function testToString()
	{
		$requirement = new Requirement();
		$requirement->setText('string name');
		$this->assertEquals($requirement,'string name');
	}

	public function testValidate()
	{
		$requirement = new Requirement();
		try
		{
			$requirement->validate();
			$this->fail('Missing name did not throw an exception');
		}
		catch (Exception $e)
		{
			# Success
		}
	}

	public function testInsert()
	{
		$requirement = new Requirement();
		$requirement->setText('Test Requirement');
		try
		{
			$requirement->save();
			$id = $requirement->getId();
			$this->assertGreaterThan(1,$id);
			$this->test_id = $id;
		}
		catch (Exception $e) { $this->fail($e->getMessage()); }
	}

	public function testLoadById()
	{
		$requirement = new Requirement($this->test_id);
		$this->assertEquals($this->test_id,$requirement->getId());
	}

	public function testUpdate()
	{
		$test_name = 'Changed Test Requirement';

		$requirement = new Requirement($this->test_id);
		$requirement->setText($test_name);
		try
		{
			$requirement->save();

			$requirement = new Requirement($this->test_id);
			$this->assertEquals($requirement->getText(),$test_name);
		}
		catch (Exception $e) { $this->fail($e->getMessage()); }
	}

	/**
	 * We should be able to remove any and all requirements.  There should be no
	 * foreign key errors thrown - ever.
	 */
	public function testDelete()
	{
		$list = new RequirementList();
		$list->find();
		foreach($list as $requirement) { $requirement->delete(); }
	}
}