<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Person $this->person
 */
$username = $this->person->getUsername();
if (!$username && userHasRole('Administrator')) {
	$url = BASE_URL.'/users/addUser.php?person_id='.$this->person->getId();
	$username = "
	<button type=\"button\" onclick=\"document.location.href='$url';\">
		Create Account
	</button>";
}


$name = View::escape($this->person->getFullname());
$about = nl2br(View::escape($this->person->getAbout()));
echo "
<div id=\"personalInfo\">
	<h1>$name</h1>
	<table class=\"memberTable\">
";
	if ($this->person->getEmail()) {
		echo "<tr><th>Email</th><td>{$this->person->getEmail()}</td></tr>";
	}
	if ($this->person->getAddress()) {
		echo "<tr><th>Address</th><td>{$this->person->getAddress()}</td></tr>";
	}
	if ($this->person->getBirthdate()) {
		echo "<tr><th>Birthdate</th><td>{$this->person->getBirdate('n/j/Y')}</td></tr>";
	}

	$committees = array();
	foreach ($this->person->getCommittees() as $committee) {
		$name = View::escape($committee->getName());
		$name = "<a href=\"{$committee->getURL()}\">$name</a>";
		$offices = $this->person->getOffices($committee);
		if (count($offices)) {
			$title = View::escape($offices[0]->getTitle());
			$name = "$name ($title)";
		}
		$committees[] = $name;
	}
	$committees = implode(', ',$committees);
	if ($committees) {
		echo "<tr><th>Committees</th><td>$committees</td></tr>";
	}

echo "
	</table>
	<p class=\"memberDescription\">$about</p>
</div>
";
