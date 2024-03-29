<?php
/**
 * @copyright 2006-2008 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser('Administrator');
$template = new Template();
$template->title = 'User accounts';

$userList = new UserList();
$userList->find();
$template->blocks[] = new Block('users/userList.inc',array('userList'=>$userList));

echo $template->render();
