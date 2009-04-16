<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Person $this->person
 */
if ($this->person->hasVotingRecord()) {
	echo "
	<div class=\"interfaceBox memberVR\">
		<h1>Voting Record</h1>
	";

	$fields = array('voteType'=>VoteType::getFinalVotetype());
	foreach ($this->person->getVotingRecords($fields) as $record) {
		$position = View::escape($record->getPosition());
		$number = View::escape($record->getTopic()->getNumber());
		$date = $record->getDate('n/j/Y');
		$description = View::escape($record->getTopic()->getDescription());


		$votingRecords = array();
		foreach ($record->getTopic()->getLatestVotingRecords() as $vote) {
			$name = View::escape($vote->getPerson()->getLastname());
			$name = "<a href=\"{$vote->getPerson()->getURL()}\">$name</a>";
			$votingRecords[] = "$name:{$vote->getPosition()}";
		}
		$votingRecords = implode(', ',$votingRecords);

		echo "
		<div class=\"topic\">
			<h3><span class=\"position\">$position</span> on
				<a href=\"{$record->getTopic()->getURL()}\" class=\"number\">$number</a>
				<span class=\"date\">$date</span>
			</h3>
			<p>$description</p>
		";
		if($votingRecords) {
			echo "<div>$votingRecords</div>";
		}
		echo "</div>";
	}
	echo "</div>";
}
