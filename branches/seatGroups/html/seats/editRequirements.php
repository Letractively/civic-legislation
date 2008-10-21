<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param REQUEST seatGroup_id
 */
verifyUser(array('Administrator','Clerk'));

$seatGroup = new SeatGroup($_REQUEST['seatGroup_id']);
try
{
	# User Posted a new Requirement
	if (isset($_POST['text']) && trim($_POST['text']))
	{
		$requirement = new Requirement();
		$requirement->setText($_POST['text']);
		$requirement->save();
	}
	# User selected an existing Requirement
	elseif (isset($_POST['requirement_id']))
	{
		$requirement = new Requirement($_POST['requirement_id']);
	}

	if (isset($requirement)) { $seatGroup->addRequirement($requirement); }
}
catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }


$template = new Template();
$template->blocks[] = new Block('committees/committeeInfo.inc',array('committee'=>$seatGroup->getCommittee()));
$template->blocks[] = new Block('seats/groupInfo.inc',array('seatGroup'=>$seatGroup));
$template->blocks[] = new Block('seats/manageRequirementsForm.inc',array('seatGroup'=>$seatGroup));
echo $template->render();