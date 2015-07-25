<?php

require_once("includes.inc.php");

class LoginAction implements IAction {

	public $myusername;
	public $mypassword;
	public $myid;


	//forteaza existenta unui constructor fara parametri;
	// util pentru testare, in absenta unei metode Factory
	public function __construct () {
	}

	//verifica daca formularul coresponzator a fost trimis
	// si daca acestea contine date (username si parola) corecte
	public function actionIsset () {
		
		//print_r($_REQUEST);
		//die("mor");
		$myusername = ($_REQUEST['username']);
		$mypassword = ($_REQUEST['password']);
		
		$myusername = ($myusername);
		
//		echo "bibi=".$myusername.", gigi=".$mypassword;
		
		if ( (!isset($myusername)) 
			|| (!isset($mypassword))
		 	|| ($myusername == "") 
		 	|| ($mypassword == ""))
			return false;

		try  {
			$db = SingletonDB::connect();
			$query = "select id from users where username='".$myusername."'"." and password ='".$mypassword."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}

		$count = 0;
		
		while ($row = $result->fetch_row())
		{
			$count++;
			$this->myid = $row[0];
		}

		
		if ($count == 0)
			return false;
			
		return true;
	}
	
	// daca actionIsset intoarce true,
	// atunci seteaza o sesiune ce va contine id-ul utilizatorului autentificat
	public function execute () {
		if ( $this->actionIsset() == false) 
		{ 
			throw new ActionNotSetException();
		}

		if(!session_id())
		{
			session_start();
		}
		
		
		$_SESSION[SESSION_NAME]=$this->myid;
		
		//header("Location:http://localhost/l4/index.php");
	}
}

?>