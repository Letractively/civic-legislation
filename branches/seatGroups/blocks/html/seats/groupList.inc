<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SeatGroupList $this->seatGroupList
 * @param Committee $this->committee
 */
$userIsAdmin = userHasRole(array('Administrator','Clerk'));
?>
<div class="interfaceBox">
	<h1>
		<?php
			if ($userIsAdmin)
			{
				$url = new URL(BASE_URL.'/seats/addGroup.php');
				$url->committee_id = $this->committee->getId();
				echo "<a class=\"add button\" href=\"$url\">Add Seat Group</a>";
			}
		?>
		Seats
	</h1>
	<table>
	<tr><th></th>
		<th></th>
		<th>Appointed By</th>
		<th>Seats</th>
	</tr>
	<?php
		foreach($this->seatGroupList as $seatGroup)
		{
			$addButton = '';
			$editButton = '';
			if ($userIsAdmin)
			{
				$url = new URL(BASE_URL.'/seats/updateGroup.php');
				$url->seatGroup_id = $seatGroup->getId();
				$editButton = "<a class=\"edit button\" href=\"$url\">Edit Seat Group</a>";

				$url = new URL(BASE_URL.'/seats/addSeat.php');
				$url->seatGroup_id = $seatGroup->getId();
				$addButton = "<a class=\"add button\" href=\"$url\">Add Seat</a>";
			}

			$name = View::escape($seatGroup->getName());
			$appointer = View::escape($seatGroup->getAppointer());
			echo "
			<tr><td>$editButton</td>
				<td><a href=\"{$seatGroup->getURL()}\">$name</a></td>
				<td>$appointer</td>
				<td>
			";

				$block = new Block('seats/seatList.inc');
				$block->seatGroup = $seatGroup;
				$block->seatList = $seatGroup->getSeats();
				echo $block->render();

			echo "
				</td>
			</tr>
			";
		}
	?>
	</table>
</div>
