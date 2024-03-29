<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param VoteList $this->voteList
 * @param Topic $this->topic (optional)
 * @param string $this->title (optional)
 */
$title = isset($this->title) ? View::escape($this->title) : 'Votes';
?>
<div class="interfaceBox votes">
	<h1><?php
			if (isset($this->topic) && userHasRole(array('Administrator','Clerk'))) {
				$url = new URL(BASE_URL.'/votes/addVote.php');
				$url->topic_id = $this->topic->getId();
				echo "<button type=\"button\" class=\"add\" onclick=\"document.location.href='$url';\">
				Add
				</button>";
			}
			echo $title;
		?>
	</h1>
	<table>
		<tr><th></th>
			<th>Vote</th>
			<th>Legislation</th>
			<th>Date</th>
			<?php
				$positions = VotingRecord::getPossiblePositions();
				foreach ($positions as $position) {
					$position = ucfirst($position);
					echo "<th>$position</th>";
				}
			?>
			<th>Outcome</th>
		</tr>
		<?php
			foreach ($this->voteList as $vote) {
				$editButton = '';
				if (userHasRole(array('Administrator','Clerk'))) {
					$url = new URL(BASE_URL.'/votes/updateVote.php');
					$url->vote_id = $vote->getId();
					$editButton = "<button type=\"button\" class=\"edit\" onclick=\"document.location.href='$url';\">
					Edit
					</button>";
				}

				$number = View::escape($vote->getTopic()->getNumber());

				echo "
				<tr><th>$editButton</th>
					<th><a href=\"{$vote->getURL()}\">{$vote->getVoteType()}</a></th>
					<th><a href=\"{$vote->getTopic()->getURL()}\">$number</a></th>
					<td>{$vote->getDate('n/j/Y')}</td>
				";
				foreach ($positions as $position) {
					echo '<td>'.count($vote->getVotingRecords($position)).'</td>';
				}
				echo "
					<td>{$vote->getOutcome()}</td>
				</tr>
				";
			}
		?>
	</table>
</div>
