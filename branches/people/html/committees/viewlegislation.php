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
	

	$topics = $committee->getTopics();
	if (count($topics)) {
		$people = array();
		foreach($committee->getCurrentTerms() as $term) {
			$people[] = $term->getPerson();
		}

		$template->blocks[] = new Block('topics/tagCloud.inc',array('topicList'=>$topics));
	}
	if (count($topics) > 15) {
		$pages = new Paginator($topics,15);
		$page = (isset($_GET['page']) && $_GET['page'])
				? (int)$_GET['page']
				: 0;
		if (!$pages->offsetExists($page)) {
			$page = 0;
		}
		$topicList = new LimitIterator($topics,$pages[$page],$pages->getPageSize());
	}
	else {
		$topicList = $topics;
	}
	$template->blocks[] = new Block('topics/topicList.inc',
									array('topicList'=>$topicList,'committee'=>$committee));

	if (isset($pages)) {
		$pageNavigation = new Block('pageNavigation.inc');
		$pageNavigation->page = $page;
		$pageNavigation->pages = $pages;
		$pageNavigation->url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

		$template->blocks[] = $pageNavigation;
	}
}

}
echo $template->render();
?>
