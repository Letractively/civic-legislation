<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class Seat extends ActiveRecord
{
	private $id;
	private $title;
	private $requirements;
	private $committee_id;
	private $appointer_id;

	private $committee;
	private $appointer;

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
		if (!$this->committee_id) { throw new Exception('seats/missingCommittee'); }
		if (!$this->title) { throw new Exception('seats/missingTitle'); }
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
		$fields['title'] = $this->title;
		$fields['requirements'] = $this->requirements ? $this->requirements : null;
		$fields['committee_id'] = $this->committee_id ? $this->committee_id : null;
		$fields['appointer_id'] = $this->appointer_id ? $this->appointer_id : null;

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
	public function getRequirements() { return $this->requirements; }
	public function getCommittee_id() { return $this->committee_id; }
	public function getAppointer_id() { return $this->appointer_id; }

	public function getCommittee()
	{
		if ($this->committee_id)
		{
			if (!$this->committee) { $this->committee = new Committee($this->committee_id); }
			return $this->committee;
		}
		else return null;
	}

	public function getAppointer()
	{
		if ($this->appointer_id)
		{
			if (!$this->appointer) { $this->appointer = new Appointer($this->appointer_id); }
			return $this->appointer;
		}
		else return 'Elected';
	}

	#----------------------------------------------------------------
	# Generic Setters
	#----------------------------------------------------------------
	public function setTitle($string) { $this->title = trim($string); }
	public function setRequirements($string) { $this->requirements = trim($string); }
	public function setCommittee_id($int) { $this->committee = new Committee($int); $this->committee_id = $int; }
	public function setAppointer_id($int) { $this->appointer = new Appointer($int); $this->appointer_id = $int; }

	public function setCommittee($committee) { $this->committee_id = $committee->getId(); $this->committee = $committee; }
	public function setAppointer($appointer) { $this->appointer_id = $appointer->getId(); $this->appointer = $appointer; }

	#----------------------------------------------------------------
	# Custom Functions
	# We recommend adding all your custom code down here at the bottom
	#----------------------------------------------------------------
	public function getMembers() { return new MemberList(array('seat_id'=>$this->id)); }

	/**
	 * Returns the current member for this seat
	 * @return Member
	 */
	public function getMember()
	{
		return null;
	}

}