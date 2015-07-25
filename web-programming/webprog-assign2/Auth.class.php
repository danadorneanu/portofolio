<?php
require_once("includes.inc.php");

class Auth implements IAuth {
	
	public $myusername;
	
	public function __construct($username) {
		
		$this->myusername = $username;
		//echo "I am constructed Auth";
	}
	
	public function getId () {
		try  {

			$db = SingletonDB::connect();
			$query = "select id from pw_users where username = '".$this->myusername."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		
		$row = $result->fetch_row();

		return $row[0];
		
	}
		
	public function isAdmin () {
		try  {

			$db = SingletonDB::connect();
			$query = "select statut from pw_users where username = '".$this->myusername."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		
		$row = $result->fetch_row();

		if ($row[0] == "admin")
			return true;
		return false;
	}
	
}
?>