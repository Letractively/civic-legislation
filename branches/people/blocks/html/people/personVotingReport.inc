<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param Person $this->person
 */
?>
<div class="interfaceBox memberVoteStats">
	<h1>Voting Stats</h1>
	<table>
		<?php
			echo "<tr><th>Legislation</th>";
			$possiblePositions = VotingRecord::getPossiblePositions();
			foreach ($possiblePositions as $position) {
				echo "<th>$position</th>";
			}

			$topicTypes = new TopicTypeList();
			$topicTypes->find();
			foreach ($topicTypes as $topicType) {
				$name = View::escape($topicType->getName());
				echo "<tr><th>$name</th>";
				$percentages = $this->person->getVotePercentages($topicType);

				foreach ($possiblePositions as $position) {
					echo "<td>$percentages[$position]</td>";
				}
				echo "</tr>";
			}
			echo "</tr>"
		?>
	</table>
</div>

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
