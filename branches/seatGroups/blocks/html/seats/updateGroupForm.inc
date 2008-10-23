<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SeatGroup $this->seatGroup
 */
?>
<h1>Update SeatGroup</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Seat Group Info</legend>
	<input name="seatGroup_id" type="hidden" value="<?php echo $this->seatGroup->getId(); ?>" />
	<table>

	<tr><td><label for="seatGroup-name" class="required">Name</label></td>
		<td><input name="seatGroup[name]" id="seatGroup-name" value="<?php echo View::escape($this->seatGroup->getName()); ?>" /></td></tr>

	<tr><td><label for="seatGroup-numberOfSeats" class="required">Seats</label></td>
		<td><input name="seatGroup[numberOfSeats]"
					id="seatGroup-numberOfSeats"
					size="3" maxlength="3"
					value="<?php echo $this->seatGroup->getNumberOfSeats(); ?>" />
		</td>
	</tr>

	<tr><td><label for="seatGroup-appointer_id" class="required">Appointer</label></td>
		<td><select name="seatGroup[appointer_id]" id="seatGroup-appointer_id">
			<?php
				$list = new AppointerList();
				$list->find();
				foreach($list as $appointer)
				{
					$name = View::escape($appointer->getName());
					$selected = ($this->seatGroup->getAppointer_id()==$appointer->getId()) ? ' selected="selected"' : '';
					echo "<option value=\"{$appointer->getId()}\"$selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>

	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->seatGroup->getCommittee()->getURL(); ?>';">Cancel</a>
</fieldset>
</form>