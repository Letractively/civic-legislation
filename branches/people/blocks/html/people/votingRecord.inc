<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Person $this->person
 */
if ($this->person->hasVotingRecord()) {
	echo "
	<div class=\"interfaceBox legislation\">
		<h1>Voting Record</h1>
	";
	foreach ($this->person->getVotingRecords() as $record) {
		$position = View::escape($record->getPosition());
		$number = View::escape($record->getTopic()->getNumber());
		$date = $record->getDate('n/j/Y');
		$description = View::escape($record->getTopic()->getDescription());
		echo "
		<div class=\"topic\">
			<h3><strong>$position</strong> on
				<a href=\"{$record->getTopic()->getURL()}\">$number</a>
				$date
			</h3>
			<p>$description</p>
		</div>
		";
	}
	echo "</div>";
}
