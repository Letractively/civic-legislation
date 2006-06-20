<?php
	verifyUser("Administrator");

	include(GLOBAL_INCLUDES."/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/menubar.inc");
	include(APPLICATION_HOME."/includes/sidebar.inc");
?>
<div id="mainContent">
	<?php include(GLOBAL_INCLUDES."/errorMessages.inc"); 
				$commission = new Commission($_GET['id']);
	?>

	<h1>New Seat</h1>
	<form method="post" action="addSeat.php">
		
	<fieldset><legend>Committee Info</legend>
		<input type="hidden" name="id" value="<?php echo $commission->getId(); ?>" />
		<table>
		<tr>
				<td><label for="title">Seat Title</label></td>
				<td><input name="title" id="title" /></td>
		</tr>
	
		<tr><td><label for="users">Add Member</label></td>
			<td><select name="users" id="users">
				<option>--Vacant--</option>
				<?php
					$users = new UserList();
					$users->find();
					foreach($users as $user) { echo "<option>{$user->getUsername()}</option>"; }
				?>
				</select>
			</td>
		</tr>
		
	<tr>
		<td><label for="t_start">Term Start Date</label></td>
		<td><input name="t_start" id="t_start" /></td>
	</tr>
			
	<tr>
		<td>*<label for="t_end">Term End Date</label></td>
		<td><input name="t_end" id="t_end" /></td>
	</tr>
		
	<tr><td><label for="category">Appointment Type</label></td>
			<td><select name="category" id="category">
				<?php
					$seatCategoryList = new SeatCategoryList();
					$seatCategoryList->find();
					foreach($seatCategoryList as $seatCategory) { echo "<option>{$seatCategory->getCategory()}</option>"; }
				?>
				</select>
			</td>
		</tr>
		
		<tr>
			<td><label>Commission</label></td>
			<td><?php echo $commission->getName(); ?></td>
		</tr>
		
		<tr><td><label for="restrictions">Restrictions</label></td>
			<td><select name="restrictions[]" id="restrictions" size="5" multiple="multiple">
				<?php
					$restrictions = new RestrictionList();
					$restrictions->find();
					foreach($restrictions as $restriction) { echo "<option>$restriction</option>"; }
				?>
				</select>
			</td>
		</tr>
		
		<tr><td>*If term is indefinte leave field blank.</td></tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>';">Cancel</button>
	</fieldset>
	</form>
</div>

<?php
	include(APPLICATION_HOME."/includes/footer.inc");
	include(GLOBAL_INCLUDES."/xhtmlFooter.inc");
?>