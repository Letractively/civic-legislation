<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
$options = array('','Ordinance','Resolution','App. Ordinance');
?>
<h1>Update Legislation</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" class="yui-skin-sam">
<fieldset><legend>Legislation Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->topic->getId(); ?>" />
	<table>
	<tr><td><label for="topic-type">Type</label></td>
		<td><select name="topic[type]" id="topic-type">
	<?php 
		foreach($options as $option){
			if($option == $this->topic->getType()){
				echo "<option selected='selected'>$option</option>";
			}
			else{
				echo "<option>$option</option>";
			}
		}
	?>
	</select></td></tr>

	<tr><td><label for="topic-date">Date</label></td>
		<td><input name="topic[date]" id="topic-date" value="<?php echo $this->topic->getDate('n/j/Y'); ?>"  onfocus="FRAMEWORK.popupCalendar(this);" maxlength="10" />
		</td>
	</tr>

	<tr><td><label for="topic-number">Number</label></td>
		<td><input name="topic[number]" id="topic-number" value="<?php echo $this->topic->getNumber(); ?>" /></td></tr>
		
	<tr><td><label for="topic-description">Description</label></td>
		<td><textarea name="topic[description]" id="topic-description" rows="3" cols="60"><?php echo View::escape($this->topic->getDescription()); ?></textarea></td></tr>
		
	<tr><td><label for="topic-synopsis">Synopsis</label></td>
		<td><textarea name="topic[synopsis]" id="topic-synopsis" rows="3" cols="60"><?php echo View::escape($this->topic->getSynopsis()); ?></textarea></td></tr>
		
		<input type="hidden" name="topic[committee_id]" id="topic-committee_id" value="<?php echo $this->topic->getCommittee_id(); ?>" />
		
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel button" href="<?php echo BASE_URL; ?>/topics">Cancel</a>
</fieldset>
</form>