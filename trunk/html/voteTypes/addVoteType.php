<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
verifyUser('Administrator');

if (isset($_POST['voteType']))
{
	$voteType = new VoteType();
	foreach($_POST['voteType'] as $field=>$value)
	{
		$set = 'set'.ucfirst($field);
		$voteType->$set($value);
	}

	try
	{
		$voteType->save();
		Header('Location: home.php');
		exit();
	}
	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('voteTypes/addVoteTypeForm.inc');
echo $template->render();