<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param SeatList $this->seatList
 * @param Committee $this->committee (optional)
 */
$addSeatButton = '';
if (isset($this->committee) && userHasRole('Administrator'))
{
	$url = new URL(BASE_URL.'/seats/addSeat.php');
	$url->committee_id = $this->committee->getId();
	$addSeatButton = "<a class=\"add button\" href=\"$url\">Add</a>";
}
?>
<div class="interfaceBox">
	<h1><?php echo $addSeatButton; ?>
		Seats
	</h1>
	<table>
	<tr><td></td>
		<td>Member</td>
		<td>Title</td>
		<td>Appointed By</td>
		<td>Requirements</td>
	</tr>
	<?php
		foreach($this->seatList as $seat)
		{
			$editButton = '';
			if (userHasRole('Administrator'))
			{
				$url = new URL(BASE_URL.'/seats/updateSeat.php');
				$url->seat_id = $seat->getId();
				$editButton = "<a class=\"edit button\" href=\"$url\">Edit</a>";
			}

			$title = View::escape($seat->getTitle());
			$appointer = View::escape($seat->getAppointer());
			$requirements = View::escape($seat->getRequirements());

			$member = $seat->getMember() ? View::escape($seat->getMember()->getFullName()) : 'Vacant';
			$member = "<a href=\"".BASE_URL."/seats/viewSeat.php?seat_id={$seat->getId()}\">$member</a>";
			echo "
			<tr><td>$editButton</td>
				<td>$member</td>
				<td>$title</td>
				<td>$appointer</td>
				<td>$requirements</td>
			</tr>
			";
		}
	?>
	</table>
</div>