<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET committee_id
 */
verifyUser('Administrator');


if (isset($_POST['seatGroup']))
{
	$seatGroup = new SeatGroup();
	foreach($_POST['seatGroup'] as $field=>$value)
	{
		$set = 'set'.ucfirst($field);
		$seatGroup->$set($value);
	}

	try
	{
		$seatGroup->save();
		Header('Location: '.$seatGroup->getCommittee()->getURL());
		exit();
	}
	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$committee = new Committee($_GET['committee_id']);

$template = new Template();
$template->blocks[] = new Block('committees/committeeInfo.inc',array('committee'=>$committee));
$template->blocks[] = new Block('seats/addGroupForm.inc',array('committee'=>$committee));
echo $template->render();
