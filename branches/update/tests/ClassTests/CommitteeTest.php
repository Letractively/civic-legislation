<?php
require_once 'PHPUnit/Framework.php';

/**
 * Test class for Committee.
 * Generated by PHPUnit on 2008-09-29 at 10:54:35.
 */
class CommitteeTest extends PHPUnit_Framework_TestCase
{
	protected $test_id;

    /**
     * Sets up the fixture, for example, opens a network connection.
     * This method is called before a test is executed.
     *
     * @access protected
     */
    protected function setUp()
    {
    }

    /**
     * Tears down the fixture, for example, closes a network connection.
     * This method is called after a test is executed.
     *
     * @access protected
     */
    protected function tearDown()
    {
    }

    public function testChangingName()
    {
    	$committee = new Committee();
    	$committee->setName('test name');
    	$this->assertEquals($committee->getName(),'test name');
    }

    public function testInsert()
    {
    	$committee = new Committee();
    	$committee->setName('test committee');
    	try
    	{
    		$committee->save();
			$id = $committee->getId();
			$this->assertGreaterThan(1,$id);
			$this->test_id = $id;
		}
		catch(Exception $e) { $this->fail($e->getMessage()); }
    }

    public function testUpdate()
    {
    	$test_name = 'updated test committee';
		$committee = new Committee($this->test_id);
		$committee->setName($test_name);
		try
		{
			$committee->save();
			$this->assertEquals($committee->getName(),$test_name);
		}
		catch (Exception $e) { $this->fail($e->getMessage()); }
    }

    public function testGetSeats()
    {
    	$committee = new Committee($this->test_id);
    	$this->assertTrue($committee->getSeats() instanceof SeatList);
    }

    public function testGetTopics()
    {
    	$committee = new Committee($this->test_id);
    	$this->assertTrue($committee->getTopics() instanceof TopicList);
    }
}