<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Vote $this->vote
 */
?>
<h1>Update Vote</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" class="yui-skin-sam">
	<fieldset><legend>Vote Info</legend>
		<input name="vote_id" type="hidden" value="<?php echo $this->vote->getId(); ?>" />

		<table>
			<tr><td><label for="vote-date">Date</label></td><td>
					<input name="vote[date]"
							id="vote-date"
							size="10"
							maxlength="10"
							value="<?php echo $this->vote->getDate('n/j/Y'); ?>" />
				</td>
			</tr>
			<tr><td><label for="vote-voteType_id">Type</label></td>
				<td><select name="vote[voteType_id]" id="vote-voteType_id">
					<?php
						$types = new VoteTypeList();
						$types->find();
						foreach ($types as $type) {
							$name = View::escape($type);
							$selected = $this->vote->getVoteType_id()==$type->getId() ? ' selected="selected"' : '';
							echo "<option value=\"{$type->getId()}\"$selected>$name</option>";
						}
					?>
					</select>
				</td>
			</tr>
			<tr><td><label for='vote-outcome'>Outcome</td>
				<td><select name='vote[outcome]' id='vote-outcome'>
						<option></option>
						<option<?php echo $this->vote->getOutcome()=='pass' ? ' selected="selected"' : ''; ?>>pass</option>
						<option<?php echo $this->vote->getOutcome()=='fail' ? ' selected="selected"' : ''; ?>>fail</option>
					</select>
				</td>
			</tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->vote->getTopic()->getURL(); ?>';">Cancel</button>
	</fieldset>
</form>
