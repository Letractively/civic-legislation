<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class Vote extends ActiveRecord
{
	private $id;
	private $date;
	private $type;
	private $topic_id;


	private $topic;



	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('select * from votes where id=?');
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('votes/unknownVote'); }
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
		$fields['date'] = $this->date ? $this->date : null;
		$fields['type'] = $this->type ? $this->type : null;
		$fields['topic_id'] = $this->topic_id ? $this->topic_id : null;

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

		$sql = "update votes set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert votes set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	#----------------------------------------------------------------
	# Generic Getters
	#----------------------------------------------------------------
	public function getId() { return $this->id; }

	public function getDate($format=null)
	{
		if ($format && $this->date)
		{
			if (strpos($format,'%')!==false) { return strftime($format,$this->date); }
			else { return date($format,$this->date); }
		}
		else return $this->date;
	}
	public function getType() { return $this->type; }
	public function getTopic_id() { return $this->topic_id; }

	public function getTopic()
	{
		if ($this->topic_id)
		{
			if (!$this->topic) { $this->topic = new Topic($this->topic_id); }
			return $this->topic;
		}
		else return null;
	}
		
	#----------------------------------------------------------------
	# Generic Setters
	#----------------------------------------------------------------

	public function setDate($date)
	{
		if (is_array($date)) { $this->date = $this->dateArrayToTimestamp($date); }
		elseif(ctype_digit($date)) { $this->date = $date; }
		else { $this->date = strtotime($date); }
	}
	public function setType($string) { $this->type = trim($string); }
	public function setTopic_id($int) { $this->topic = new Topic($int); $this->topic_id = $int; }

	public function setTopic($topic) { $this->topic_id = $topic->getId(); $this->topic = $topic; }


	#----------------------------------------------------------------
	# Custom Functions
	# We recommend adding all your custom code down here at the bottom
	#----------------------------------------------------------------
}