<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class Seat extends ActiveRecord
{
	private $id;
	private $title;
	private $seatGroup_id;


	private $seatGroup;
	private $member;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('select * from seats where id=?');
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('seats/unknownSeat'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
		}
	}

	/**
	 * Throws an exception if anything's wrong
	 * @throws Exception $e
	 */
	public function validate()
	{
		# Check for required fields here.  Throw an exception if anything is missing.

	}

	/**
	 * This generates generic SQL that should work right away.
	 * You can replace this $fields code with your own custom SQL
	 * for each property of this class,
	 */
	public function save()
	{
		$this->validate();

		$fields = array();
		$fields['title'] = $this->title ? $this->title : null;
		$fields['seatGroup_id'] = $this->seatGroup_id ? $this->seatGroup_id : null;

		# Split the fields up into a preparedFields array and a values array.
		# PDO->execute cannot take an associative array for values, so we have
		# to strip out the keys from $fields
		$preparedFields = array();
		foreach($fields as $key=>$value)
		{
			$preparedFields[] = "$key=?";
			$values[] = $value;
		}
		$preparedFields = implode(",",$preparedFields);


		if ($this->id) { $this->update($values,$preparedFields); }
		else { $this->insert($values,$preparedFields); }
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update seats set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert seats set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	#----------------------------------------------------------------
	# Generic Getters
	#----------------------------------------------------------------
	public function getId() { return $this->id; }
	public function getTitle() { return $this->title; }
	public function getSeatGroup_id() { return $this->seatGroup_id; }
	public function getSeatGroup()
	{
		if ($this->seatGroup_id)
		{
			if (!$this->seatGroup) { $this->seatGroup = new SeatGroup($this->seatGroup_id); }
			return $this->seatGroup;
		}
		else return null;
	}

	#----------------------------------------------------------------
	# Generic Setters
	#----------------------------------------------------------------
	public function setTitle($string) { $this->title = trim($string); }
	public function setSeatGroup_id($int) { $this->seatGroup = new SeatGroup($int); $this->seatGroup_id = $int; }
	public function setSeatGroup($seatGroup) { $this->seatGroup_id = $seatGroup->getId(); $this->seatGroup = $seatGroup; }

	#----------------------------------------------------------------
	# Custom Functions
	# We recommend adding all your custom code down here at the bottom
	#----------------------------------------------------------------
	/**
	 * @return Committee
	 */
	public function getCommittee()
	{
		return $this->getSeatGroup()->getCommittee();
	}

	/**
	 * @return MemberList
	 */
	public function getMembers() { return new MemberList(array('seat_id'=>$this->id)); }

	/**
	 * Returns the current member for this seat
	 * @return Member
	 */
	public function getMember()
	{
		if (!$this->member)
		{
			$PDO = Database::getConnection();

			$sql = "select id from members
					where seat_id=?
					and term_start<now()
					and (term_end is null or term_end>now())";
			$query = $PDO->prepare($sql);
			$query->execute(array($this->id));
			$result = $query->fetchAll();
			if (count($result))
			{
				$this->member = new Member($result[0]['id']);
			}
		}
		return $this->member;
	}
}
