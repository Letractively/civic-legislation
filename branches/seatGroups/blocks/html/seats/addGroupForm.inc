<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Committee $this->committee
 */
?>
<h1>Add SeatGroup</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>SeatGroup Info</legend>
	<input name="seatGroup[committee_id]" type="hidden" value="<?php echo $this->committee->getId(); ?>" />
	<table>

	<tr><td><label for="seatGroup-name" class="required">Name</label></td>
		<td><input name="seatGroup[name]" id="seatGroup-name" /></td></tr>

	<tr><td><label for="seatGroup-numberOfSeats" class="required">Seats</label></td>
		<td><input name="seatGroup[numberOfSeats]"
					id="seatGroup-numberOfSeats"
					size="3" maxlength="3" />
		</td>
	</tr>

	<tr><td><label for="seatGroup-appointer_id">Appointer</label></td>
		<td><select name="seatGroup[appointer_id]" id="seatGroup-appointer_id">
			<?php
				$list = new AppointerList();
				$list->find();
				foreach($list as $appointer)
				{
					$name = View::escape($appointer->getName());
					$selected = $appointer->getId()==1 ? ' selected="selected"' : '';
					echo "<option value=\"{$appointer->getId()}\"$selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>

	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->committee->getURL(); ?>';">Cancel</button>
</fieldset>
</form>
