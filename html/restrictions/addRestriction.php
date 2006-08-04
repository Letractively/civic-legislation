<?php
/*
	$_POST variables:	restriction
	
	$_GET variables: page  (which page just came from)
									 id    (id associated with either a 
									 				seat/committee, depending on 'page' value)
*/
	verifyUser("Administrator");

	#--------------------------------------------------------------------------
	# Create a new restriction
	#--------------------------------------------------------------------------
	$restriction = new Restriction();
	$restriction->setRestriction($_POST['restriction']);
	
	try
	{
		$restriction->save();
		if ($_GET['page'] == "add") {Header("Location: ".BASE_URL."/committees/addSeatForm.php?id=".$_GET['id']);}
		else {Header("Location: ".BASE_URL."/committees/updateSeatForm.php?seat={$_GET['page']}&id=".$_GET['id']);}
	}
	catch (Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		Header("Location: addRestrictionForm.php");
	}
?>