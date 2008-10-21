<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SeatGroup extends ActiveRecord
{
	private $id;
	private $name;
	private $numberOfSeats;
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
			$query = $PDO->prepare('select * from seatGroups where id=?');
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('seatGroups/unknownSeatGroup'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
			$this->appointer = 1;
			$this->numberOfSeats = 1;
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
		if (!$this->name) { throw new Exception('missingName'); }

		if (!$this->appointer_id) { $this->appointer_id = 1; }
		if (!$this->numberOfSeats) { $this->numberOfSeats = 1; }
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
		$fields['name'] = $this->name;
		$fields['numberOfSeats'] = $this->numberOfSeats;
		$fields['committee_id'] = $this->committee_id;
		$fields['appointer_id'] = $this->appointer_id;

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

		$sql = "update seatGroups set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert seatGroups set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	#----------------------------------------------------------------
	# Generic Getters
	#----------------------------------------------------------------
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }
	public function getNumberOfSeats() { return $this->numberOfSeats; }
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
		else return null;
	}

	#----------------------------------------------------------------
	# Generic Setters
	#----------------------------------------------------------------
	public function setName($string) { $this->name = trim($string); }
	public function setNumberOfSeats($int) { $this->numberOfSeats = ereg_replace("[^0-9]","",$int); }
	public function setCommittee_id($int) { $this->committee = new Committee($int); $this->committee_id = $int; }
	public function setAppointer_id($int) { $this->appointer = new Appointer($int); $this->appointer_id = $int; }

	public function setCommittee($committee) { $this->committee_id = $committee->getId(); $this->committee = $committee; }
	public function setAppointer($appointer) { $this->appointer_id = $appointer->getId(); $this->appointer = $appointer; }


	#----------------------------------------------------------------
	# Custom Functions
	# We recommend adding all your custom code down here at the bottom
	#----------------------------------------------------------------
	/**
	 * @param Requirement $requirement
	 * @return boolean
	 */
	public function hasRequirement($requirement)
	{
		$PDO = Database::getConnection();
		$query = $PDO->prepare('select requirement_id from seatGroup_requirements where seatGroup_id=? and requirement_id=?');
		$query->execute(array($this->id,$requirement->getId()));
		$result = $query->fetchAll();
		return count($result) ? true : false;
	}
	/**
	 * @param Requirement $requirement
	 */
	public function addRequirement($requirement)
	{
		if (!$this->hasRequirement($requirement))
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('insert seatGroup_requirements set seatGroup_id=?,requirement_id=?');
			$query->execute(array($this->id,$requirement->getId()));
		}
	}
	/**
	 * @param Requirement $requirement
	 */
	public function removeRequirement($requirement)
	{
		if ($this->id)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('delete from seatGroup_requirements where seatGroup_id=? and requirement_id=?');
			$query->execute(array($this->id,$requirement->getId()));
		}
	}
	/**
	 * @return RequirementsList
	 */
	public function getRequirements()
	{
		return new RequirementList(array('seatGroup_id'=>$this->id));
	}
	/**
	 * @return boolean
	 */
	public function hasRequirements()
	{
		return count($this->getRequirements()) ? true : false;
	}

	/**
	 * @return SeatList
	 */
	public function getSeats()
	{
		return new SeatList(array('seatGroup_id'=>$this->id));
	}

	/**
	 * @return string
	 */
	public function getURL()
	{
		return BASE_URL.'/seats/viewGroup.php?seatGroup_id='.$this->id;
	}

	/**
	 * @return MemberList
	 */
	public function getMembers()
	{
		return new MemberList(array('seatGroup_id'=>$this->id));
	}
}
