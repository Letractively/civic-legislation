<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Committee $this->committee
 */
?>
<div class="interfaceBox seats">
	<h1>Past Members</h1>
	<table>
		<?php
			foreach ($this->committee->getPeople() as $person) {
				$fullname = View::escape($person->getFullname());
				$earliestStart = time();
				$latestEnd = null;
				foreach ($person->getTerms($this->committee) as $term) {
					if ($term->getTerm_start()<$earliestStart) {
						$earliestStart = $term->getTerm_start();
					}
					if (!$latestEnd || $term->getTerm_end()>$latestEnd) {
						$latestEnd = $term->getTerm_end();
					}
				}
				$earliestStart = date('n/j/Y',$earliestStart);
				$latestEnd = date('n/j/Y',$latestEnd);

				echo "
				<tr><td><a href=\"{$term->getPerson()->getURL()}\">$fullname</a></td>
					<td>$earliestStart - $latestEnd</td>
				</tr>
				";
			}
		?>
	</table>
</div>
