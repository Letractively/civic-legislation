<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Topic $this->topic
 */
?>
<h1>Add Vote</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" class="yui-skin-sam">
	<fieldset><legend>Vote Info</legend>
		<input name="topic_id" type="hidden" value="<?php echo $this->topic->getId(); ?>" />

		<table>
			<tr><td><label for="vote-date" class="required">Date</label></td>
				<td><input name="vote[date]"
							id="vote-date"
							size="10"
							maxlength="10"
							value="<?php echo date('n/j/Y'); ?>" />
				</td>
			</tr>
			<tr><td><label for="vote-voteType_id" class="required">Type</label></td>
				<td><select name="vote[voteType_id]" id="vote-voteType_id">
					<?php
						$types = new VoteTypeList();
						$types->find();
						foreach ($types as $type) {
							echo "<option value=\"{$type->getId()}\">$type</option>";
						}
					?>
					</select>
				</td>
			</tr>
			<tr><td><label for='vote-outcome'>Outcome</td>
				<td><select name='vote[outcome]' id='vote-outcome'>
						<option></option>
						<option>pass</option>
						<option>fail</option>
					</select>
				</td>
			</tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->topic->getURL(); ?>';">
			Cancel
		</button>
	</fieldset>
</form>
