<?php
	session_start();
	$validNames = array('human', 'computer');

	if (isset($_POST['reset']) && ($_POST['reset'])) {
		foreach ($validNames as $name) {
			$_SESSION[$name] = 0;
		}
		die();
	}	


	if (isset($_POST['winner']) && (in_array($_POST['winner'], $validNames))) {
		$_SESSION[$_POST['winner']] += 1;
		
		echo json_encode(array('value' => $_SESSION[$_POST['winner']]));
		die();
	}
	

?>
