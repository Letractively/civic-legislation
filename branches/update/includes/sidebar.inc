<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="left sidebar">
<?php
	if (!isset($_SESSION['USER']))
	{
		$block = new Block('loginForm.inc');
		echo $block->render();
	}

	if (userHasRole('Administrator'))
	{
		include APPLICATION_HOME.'/includes/sidebarBoxes/Administrator.inc';
	}
?>
</div>