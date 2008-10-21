<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET seatGroup_id
 */
$seatGroup = new SeatGroup($_GET['seatGroup_id']);

$template = new Template();

$committee = new Block('committees/committeeInfo.inc');
$committee->committee = $seatGroup->getCommittee();
$template->blocks[] = $committee;

$group = new Block('seats/groupInfo.inc');
$group->seatGroup = $seatGroup;
$template->blocks[] = $group;

$seats = new Block('seats/seatList.inc');
$seats->seatGroup = $seatGroup;
$template->blocks[] = $seats;

$members = new Block('members/memberList.inc');
$members->memberList = $seatGroup->getMembers();
$members->seatGroup = $seatGroup;
$template->blocks[] = $members;

echo $template->render();