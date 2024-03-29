<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Committee $this->committee
 */
$name = View::escape($this->committee->getName());
$description = View::escape($this->committee->getDescription());
$statutoryName = View::escape($this->committee->getStatutoryName());
$statuteReference = View::escape($this->committee->getStatuteReference());
$description = View::escape($this->committee->getDescription());

echo "
<h1><a href=\"{$this->committee->getURL()}\">$name</a></h1>

<div id=\"committeeInfo\">
	<table>
		<tr><th>Date Formed</th>
			<td>{$this->committee->getDateFormed('n/j/Y')}</td>
		</tr>
		<tr><th>Statutory Name</th>
			<td>$statutoryName</td>
		</tr>
		<tr><th>Statute Reference</th>
			<td>$statuteReference</td>
		</tr>
		<tr><th>Website</th>
			<td><a href=\"{$this->committee->getWebsite()}\">View Homepage</a></td>
		</tr>
	</table>
</div>
<div id=\"committeeDescription\">
	<p>$description</p>
</div>
";
