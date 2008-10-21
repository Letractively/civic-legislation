<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET seatGroup_id
 * @param GET requirement_id
 */
verifyUser(array('Administrator','Clerk'));
$seatGroup = new SeatGroup($_GET['seatGroup_id']);
$requirement = new Requirement($_GET['requirement_id']);

$seatGroup->removeRequirement($requirement);

Header('Location: '.$seatGroup->getURL());
