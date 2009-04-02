<?php
/**
 * @copyright 2008 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET committee_id
 */
$committee = new Committee($_GET['committee_id']);

$format = isset($_GET['format']) ? $_GET['format'] : 'html';
$template = new Template('default',$format);
$template->title = $committee->getName();

if ($template->outputFormat == 'html') {
	$template->blocks[] = new Block('committees/breadcrumbs.inc',array('committee'=>$committee));
}
$template->blocks[] = new Block('committees/committeeInfo.inc',array('committee'=>$committee));

if ($template->outputFormat == 'html') {
	$template->blocks[] = new Block('committees/tabs.inc',
								array('committee'=>$committee,'currentTab'=>'votes'));

	$topics = $committee->getTopics();
	if (count($topics)) {
		$people = array();
		foreach($committee->getCurrentTerms() as $term) {
			$people[] = $term->getPerson();
		}

		$votingComparison = new Block('votingRecords/votingRecordComparison.inc');
		$votingComparison->topicList = $topics;
		$votingComparison->people = $people;
		$template->blocks[] = $votingComparison;

	}
}

echo $template->render();
