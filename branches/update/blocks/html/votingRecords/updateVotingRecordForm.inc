<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<h1>Update VotingRecord</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>VotingRecord Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->votingRecord->getId(); ?>" />
	<table>

	<tr><td><label for="votingRecord-member_id">member_id</label></td>
		<td><input name="votingRecord[member_id]" id="votingRecord-member_id" value="<?php echo $this->votingRecord->getMember_id(); ?>" /></td></tr>
		
	<tr><td><label for="votingRecord-vote">vote</label></td>
		<td><input name="votingRecord[vote]" id="votingRecord-vote" value="<?php echo $this->votingRecord->getVote(); ?>" /></td></tr>
		
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel button" href="<?php echo BASE_URL; ?>/votingRecords">Cancel</a>
</fieldset>
</form>