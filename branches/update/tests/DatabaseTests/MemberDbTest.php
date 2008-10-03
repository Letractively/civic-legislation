<?php
require_once 'PHPUnit/Framework.php';

class MemberTest extends PHPUnit_Framework_TestCase
{
	protected function setUp()
	{
		$dir = dirname(__FILE__);

		$PDO = Database::getConnection();
		$PDO->exec('drop database '.DB_NAME);
		$PDO->exec('create database '.DB_NAME);
		exec('/usr/local/mysql/bin/mysql -u '.DB_USER.' -p'.DB_PASS.' '.DB_NAME." < $dir/../testData.sql\n");

		$PDO = Database::getConnection(true);
	}

	public function testSaveLoadDelete()
	{
		$list = new SeatList();
		$list->find();
		$seat = $list[0];

		$list = new UserList();
		$list->find();
		$user = $list[0];

		$member = new Member();
		$member->setSeat($seat);
		$member->setUser($user);

		$member->save();
		$id = $member->getId();
		$this->assertGreaterThan(1,$member->getId());

		$member = new Member($id);
		$this->assertEquals($member->getId(),$id);

		$now = time();
		$member->setTerm_end($now);
		$member->save();

		$member = new Member($id);
		$this->assertEquals($member->getTerm_end(),$now);

		$member->delete();
		try
		{
			$member = new Member($id);
			$this->fail('Test member was not deleted');
		}
		catch (Exception $e)
		{
			# Success
		}
	}

	public function testDelete()
	{
		$list = new MemberList();
		$list->find();
		if (count($list))
		{
			foreach($list as $member)
			{
				try { $member->delete(); }
				catch (Exception $e) { $this->fail($e->getMessage()); }
			}
		}
		else
		{
			$this->markTestIncomplete('No Members in the system to test');
		}
	}
}