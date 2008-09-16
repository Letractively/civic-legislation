<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class TopicList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select topics.id as id from topics';
		if (is_array($fields)) $this->find($fields);
	}
	

	public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 'id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['date']))
		{
			$options[] = 'date=:date';
			$parameters[':date'] = $fields['date'];
		}
		if (isset($fields['number']))
		{
			$options[] = 'number=:number';
			$parameters[':number'] = $fields['number'];
		}
		if (isset($fields['description']))
		{
			$options[] = 'description=:description';
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['synopsis']))
		{
			$options[] = 'synopsis=:synopsis';
			$parameters[':synopsis'] = $fields['synopsis'];
		}
		if (isset($fields['committee_id']))
		{
			$options[] = 'committee_id=:committee_id';
			$parameters[':committee_id'] = $fields['committee_id'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options,$parameters);
	}
	

	protected function loadResult($key) { return new Topic($this->list[$key]); }
}