<?php
require_once 'PHPUnit/Framework.php';

/**
 * Test class for Seat.
 * Generated by PHPUnit on 2008-09-29 at 10:55:14.
 */
class SeatTest extends PHPUnit_Framework_TestCase
{
	protected $test_committee_id;
	protected $test_appointer_id;
	protected $test_id;

	public function testSetCommittee()
	{
		$committee = new Committee();
		$committee->setName('Seat Test Committee');
		$committee->save();
		$this->test_committee_id = $committee->getId();

		$seat = new Seat();
		$seat->setCommittee($committee);
		$this->assertEquals($seat->getCommittee_id(),$committee->getId());
	}

	public function testSetCommittee_id()
	{
		$seat = new Seat();
		$seat->setCommittee_id($this->test_committee_id);
		echo "Committee_id: {$this->test_committee_id}\n";
		$this->assertEquals($seat->getCommittee()->getId(),$this->test_committee_id);
	}

	public function testSetAppointer()
	{
		$appointer = new Appointer();
		$appointer->setName('Seat Test Appointer');
		$appointer->save();
		$this->test_appointer_id = $appointer->getId();

		$seat = new Seat();
		$seat->setAppointer($appointer);
		$this->assertEquals($seat->getAppointer_id(),$appointer->getId());

	}

	public function testSetAppointer_id()
	{
		$appointer = new Appointer($this->test_appointer_id);

		$seat = new Seat();
		$seat->setAppointer_id($appointer->getId());
		$this->assertEquals($seat->getAppointer()->getId(),$appointer->getId());
	}

	public function testValidate()
	{
		$seat = new Seat();
		$seat->setTitle('Test Seat');
		$seat->setCommittee_id($this->test_committee_id);
		try { $seat->validate(); }
		catch (Exception $e) { $this->fail('Validation failed even when all required fields were set'); }

		$seat->setTitle('');
		try
		{
			$seat->validate();
			$this->fail('Missing Title failed to throw validation error.');
		}
		catch (Exception $e) { }

		$seat->setTitle('Test Seat');
		$seat->setCommittee_id(null);
		try
		{
			$seat->validate();
			$this->fail('Missing committee failed to throw validation error.');
		}
		catch (Exception $e) { }
	}

	public function testInsert()
	{
		$seat = new Seat();
		$seat->setTitle('Test Seat');
		$seat->setCommittee_id($this->test_committee_id);
		try
		{
			$seat->save();
			$id = $seat->getId();
			$this->assertGreaterThan(1,$id);
			$this->test_id = $id;
		}
		catch (Exception $e) { $this->fail($e->getMessage()); }
	}

	public function testLoadById()
	{
		$seat = new Seat($this->test_id);
		$this->assertEquals($seat->getId(),$this->test_id);
	}

	public function testUpdate()
	{
		$test_title = 'Updated Test Title';

		$seat = new Seat($this->test_id);
		$seat->setTitle($test_title);
		try
		{
			$seat->save();

			$seat = new Seat($this->test_id);
			$this->assertEquals($seat->getTitle(),$test_title);
		}
		catch (Exception $e) { $this->fail($e->getMessage()); }
	}
}