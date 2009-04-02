<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param Person $this->person
 */
?>
<div class="interfaceBox memberVoteComparison">
	<h1>Voting Comparison</h1>
	<table>
		<tr><th>Member</th><th>Percentage</th></tr>
		<?php
			$peers = $this->person->getPeers();
			foreach ($peers as $peer) {
				$fullname = View::escape($peer->getFullname());
				$percent = $this->person->getAccordancePercentage($peer);
				echo "
				<tr><td><a href=\"{$peer->getURL()}\">$fullname</a></td>
					<td>$percent</td>
				</tr>
				";
			}
		?>
	</table>
</div>
