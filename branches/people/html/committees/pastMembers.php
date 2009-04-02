<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET committee_id
 */
$committee = new Committee($_GET['committee_id']);

$template = new Template();
$template->title = 'Past Members for '.$committee->getName();
$template->blocks[] = new Block('committees/breadcrumbs.inc',array('committee'=>$committee));
$template->blocks[] = new Block('committees/committeeInfo.inc',array('committee'=>$committee));
$template->blocks[] = new Block('committees/tabs.inc',
								array('committee'=>$committee,'currentTab'=>'members'));
$template->blocks[] = new Block('committees/pastMembers.inc',array('committee'=>$committee));
echo $template->render();
