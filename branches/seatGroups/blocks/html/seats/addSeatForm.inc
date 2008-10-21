<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param Committee $this->seatGroup
 */
?>
<h1>Add Seat</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Seat Info</legend>
	<input name="seatGroup_id" type="hidden" value="<?php echo $this->seatGroup->getId(); ?>" />

	<table>
	<tr><td><label for="seat-title" class="required">Title</label></td>
		<td><input name="seat[title]" id="seat-title" /></td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->seatGroup->getCommittee()->getURL(); ?>';">Cancel</button>
</fieldset>
</form>
