<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param PersonList $this->personList
 */
$people = array('Current Members'=>array(),
				'Past Members'=>array(),
				'Users'=>array(),
				'Others'=>array());
foreach ($this->personList as $person) {
	if (count($person->getTerms(array('current'=>time())))) {
		$people['Current Members'][] = $person;
	}
	elseif (count($person->getTerms())) {
		$people['Past Members'][] = $person;
	}
	elseif ($person->getUser_id()) {
		$people['Users'][] = $person;
	}
	else {
		$people['Others'][] = $person;
	}
}
?>
<div class="interfaceBox">
<?php
	$addButton = '';
	if (userHasRole(array('Administrator','Clerk'))) {
		$addButton = "
		<button type=\"button\" class=\"add\" onclick=\"document.location.href='".BASE_URL."/people/addPerson.php';\">
			Add a Person
		</button>
		";
	}
	foreach (array_keys($people) as $key) {
		if ((in_array($key,array('Current Members','Past Members'))
			&& count($people[$key]))
			|| userHasRole(array('Administrator','Clerk'))) {
			echo "
			<h1>$addButton$key</h1>
			<table>
			";
			foreach ($people[$key] as $person) {
				$editButton = '';
				if (userHasRole(array('Administrator','Clerk'))) {
					$url = new URL(BASE_URL.'/people/updatePerson.php');
					$url->person_id = $person->getId();
					$editButton = "
					<button type=\"button\" class=\"edit\" onclick=\"document.location.href='$url';\">
						Edit
					</button>
					";
				}

				$name = View::escape($person->getFullname());
				echo "
				<tr><td>$editButton</td>
					<td><a href=\"{$person->getURL()}\">$name</a></td>
					<td>{$person->getEmail()}</td>
				</tr>
				";
			}
			echo "</table>";
		}
	}
?>
</div>
