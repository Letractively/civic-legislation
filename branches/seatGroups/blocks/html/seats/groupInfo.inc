<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SeatGroup $this->seatGroup
 */
$name = View::escape($this->seatGroup->getName());
$appointer = View::escape($this->seatGroup->getAppointer());
$committee = View::escape($this->seatGroup->getCommittee()->getName());

$editRequirementsButton = '';
if (userHasRole(array('Administrator','Clerk')))
{
	$url = new URL(BASE_URL.'/seats/editRequirements.php');
	$url->seatGroup_id = $this->seatGroup->getId();
	$editRequirementsButton = "<a class=\"edit button\" href=\"$url\">Edit</a>";
}
echo "
<div class=\"interfaceBox\">
	<h1>$name</h1>
	<table>
	<tr><th>Appointed By</th>
		<td>$appointer</td>
	</tr>
	<tr><th>Committee</th>
		<td>$committee</td>
	</tr>
	<tr><th>Seats</th>
		<td>{$this->seatGroup->getNumberOfSeats()}</td>
	</tr>
	<tr><th>$editRequirementsButton
			Requirements
		</th>
		<td>
";
			if ($this->seatGroup->hasRequirements())
			{
				echo '<ul>';
				foreach($this->seatGroup->getRequirements() as $requirement)
				{
					echo '<li>'.View::escape($requirement).'</li>';
				}
				echo '</ul>';
			}
echo "
		</td>
	</tr>
	</table>
</div>
";
