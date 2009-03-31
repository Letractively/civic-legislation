<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Committee $this->committee
 */
$userIsAdmin = userHasRole(array('Administrator','Clerk'));
?>
<div class="interfaceBox seats">
	<h1>Members</h1>
	<table>
		<tr><th>Name</th>
			<th>Appointed By</th>
			<th>Term</th>
			<th></th>
		</tr>
		<?php
			foreach ($this->committee->getSeats() as $seat) {
				$appointer = View::escape($seat->getAppointer());

				//--------------------------------------------------------
				// Show all the terms
				//--------------------------------------------------------
				$terms = array();
				$c = 0;
				foreach ($seat->getCurrentTerms() as $term) {
					$c++;
					$fullname = View::escape($term->getPerson()->getFullname());

					$addButton = '';
					$editButton = '';
					if ($userIsAdmin) {
						$url = new URL(BASE_URL.'/terms/addTerm.php');
						$url->seat_id = $seat->getId();
						$url->person_id = $term->getPerson_id();
						$addButton = "<a class=\"add button\" href=\"$url\">Add</a>";

						$url = new URL(BASE_URL.'/terms/updateTerm.php');
						$url->term_id = $term->getId();
						$editButton = "<a class=\"edit button\" href=\"$url\">Edit</a>";
					}
					echo "
					<tr><td><a href=\"{$term->getPerson()->getURL()}\">$fullname</a></td>
						<td>$appointer</td>
						<td>{$term->getTerm_start('n/j/Y')} - {$term->getTerm_end('n/j/y')}</td>
						<td>$addButton $editButton</td>
					</tr>
					";
				}
				//--------------------------------------------------------
				// Show all the vacancies
				//--------------------------------------------------------
				for ($c; $c<$seat->getMaxCurrentTerms(); $c++) {
					$addButton = '';
					if ($userIsAdmin) {
						$url = new URL(BASE_URL.'/terms/addTerm.php');
						$url->seat_id = $seat->getId();
						$addButton = "<a class=\"add button\" href=\"$url\">Add</a>";
					}
					echo "
					<tr><td>( Vacancy )</td>
						<td>$appointer</td>
						<td></td>
						<td>$addButton</td>
					</tr>
					";
				}
			}
		?>
	</table>
	<div>
		<a href="<?php echo BASE_URL.'/committees/pastMembers.php?committee_id='.$this->committee->getId(); ?>">
			View Past Members
		</a>
	</div>
</div>
