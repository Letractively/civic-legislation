<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param Committee $this->seatGroup
 */
$userIsAdmin = userHasRole(array('Administrator','Clerk'));

$addButton = '';
if ($userIsAdmin)
{
	if (count($this->seatGroup->getSeats()) < $this->seatGroup->getNumberOfSeats())
	{
		$url = new URL(BASE_URL.'/seats/addSeat.php');
		$url->seatGroup_id = $this->seatGroup->getId();
		$addButton = "<a class=\"add button\" href=\"$url\">Add Seat</a>";
	}
}
?>
<table>
<tr><th><?php echo $addButton; ?></th>
	<th colspan="2">Seats</th>
</tr>
<?php
	foreach($this->seatGroup->getSeats() as $seat)
	{
		$editButton = '';
		if ($userIsAdmin)
		{
			$url = new URL(BASE_URL.'/seats/updateSeat.php');
			$url->seat_id = $seat->getId();
			$editButton = "<a class=\"edit button\" href=\"$url\">Edit Seat</a>";
		}

		$title = View::escape($seat->getTitle());

		$member = $seat->getMember();
		$memberName = $member ? View::escape($member->getFirstname().' '.$member->getLastname()) : 'Vacant';
		echo "
		<tr><th>$editButton</th>
			<th>$title</th>
			<td>$memberName</td>
		</tr>
		";
	}
?>
</table>
