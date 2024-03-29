<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */

verifyUser(array('Administrator','Clerk'));

if (isset($_POST['race'])) {
	$race = new Race();
	foreach ($_POST['race'] as $field=>$value) {
		$set = 'set'.ucfirst($field);
		$race->$set($value);
	}

	try {
		$race->save();
		header('Location: '.BASE_URL.'/races');
		exit();
	}
	catch(Exception $e) {
		$_SESSION['errorMessages'][] = $e;
	}
}

$template = new Template();
$template->title = 'Add Race';
$template->blocks[] = new Block('races/addRaceForm.inc');
echo $template->render();
