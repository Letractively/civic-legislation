<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Committee $this->committee
 * @param string $this->currentTab
 */
$tabs = array('members'=>$this->committee->getURL(),
			  'topics'=>BASE_URL.'/committees/topics.php?committee_id='.$this->committee->getId(),
			  'votes'=>BASE_URL.'/committees/votes.php?committee_id='.$this->committee->getId());
?>
<div class="tabBar">
	<ul>
	<?php
		foreach ($tabs as $tab=>$url) {
			$class = $this->currentTab==$tab ? 'class="current"' : '';
			$name = ucfirst($tab);
			echo "<li><a href=\"$url\" $class>$name</a></li>";
		}
	?>
	</ul>
</div>
