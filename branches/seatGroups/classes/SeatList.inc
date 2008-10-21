<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SeatList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select seats.id as id from seats';
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
		if (isset($fields['title']))
		{
			$options[] = 'title=:title';
			$parameters[':title'] = $fields['title'];
		}
		if (isset($fields['seatGroup_id']))
		{
			$options[] = 'seatGroup_id=:seatGroup_id';
			$parameters[':seatGroup_id'] = $fields['seatGroup_id'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['committee_id']))
		{
			$this->joins.= ' left join seatGroups g on seats.seatGroup_id=g.id';
			$options[] = 'committee_id=:committee_id';
			$parameters[':committee_id'] = $fields['committee_id'];
		}

		$this->populateList($options,$parameters);
	}


	protected function loadResult($key) { return new Seat($this->list[$key]); }
}
