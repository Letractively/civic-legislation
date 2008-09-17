<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET committee_id
 */
$topic = new Topic($_GET['topic_id']);

$template = new Template();
$template->blocks[] = new Block('committees/committeeInfo.inc',array('committee'=>$topic->getCommittee()));
$template->blocks[] = new Block('topics/topicInfo.inc',array('topic'=>$topic));

echo $template->render();
