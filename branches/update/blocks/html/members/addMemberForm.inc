<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param Seat $this->seat
 * @param User $this->user
 */
?>
<h1>Add Member</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" class="yui-skin-sam">
<fieldset><legend>Member Info</legend>
	<input name="seat_id" type="hidden" value="<?php echo $this->seat->getId(); ?>" />
	<input name="user_id" type="hidden" value="<?php echo $this->user->getId(); ?>" />

	<table>
	<tr><th>User</th>
		<th><label for="member-term_start">Term Start</label></th>
		<th><label for="member-term_end">Term End</label></th>
	</tr>

	<tr><th><?php
				echo View::escape($this->user->getFirstname());
				echo View::escape($this->user->getLastname());
			?>
		</th>
		<td><input name="member[term_start]" id="member-term_start" onfocus="FRAMEWORK.popupCalendar(this);" /></td>
		<td><input name="member[term_end]" id="member-term_end" onfocus="FRAMEWORK.popupCalendar(this);" /></td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel button" href="<?php echo $this->seat->getURL(); ?>">Cancel</a>
</fieldset>
</form>