<?php

	require_once("includes.inc.php");
	require_once("testerLib.inc.php");
	
	/* ********************* CHANGE PERMISSION TESTS ****************/
	class ChangePermissionsRequest extends Request {
		public static function test () {
			custom_session_start();
			$o = new ChangePermissionsAction ();
			$r = $o->actionIsset();
			if (!is_null($r))
				echo intval($r);
		}
	}
	
	//user is not logged, but tries to change permissions
	class ChangePermissionsActionIssetFalse01Test extends Test {
		public function run () {
			
			$u = getRandomUserId();
			if (!$u) {
				$this->errorOutput = "No simple user (not admin) found";
				return false;
			}
						
			$r = new ChangePermissionsRequest ("GET", array("id"=>$u), false, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as guest; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}

	//user is logged, but not an administrator (and tries to change permissions)
	class ChangePermissionsActionIssetFalse02Test extends Test {
		public function run () {
			
			$u = getRandomUserId();
			$logged = getRandomUserId();
			if (!$u) {
				$this->errorOutput = "No simple user (not admin) found";
				return false;
			}
			if (!$logged) {
				$this->errorOutput = "No simple user found";
				return false;
			}
			
			$username = TesterMethods::getUsername($logged);
			$password = TesterMethods::getPassword($logged);
			
			$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);
			if (!$login->getCookie()) {
				$this->errorOutput = "Script should set a cookie";
				return false;
			}
			$cook = $login->getCookie();
			if (!isset($cook['PHPSESSID'])) {
				$this->errorOutput = "Incorrect cookie set";
				return false;
			}
			$r = new ChangePermissionsRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as logged user, but not admin; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//not logged, and invalid id 
	class ChangePermissionsActionIssetFalse11Test extends Test {
		public function run () {
			
			$r = new ChangePermissionsRequest ("GET", array("id"=>"999999"), false, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as guest, and with invalid id; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//logged as user, and invalid id
	class ChangePermissionsActionIssetFalse12Test extends Test {
		public function run () {
			
			$u = "999999";
			$logged = getRandomUserId();
			if (!$logged) {
				$this->errorOutput = "No simple user found";
				return false;
			}
			
			$username = TesterMethods::getUsername($logged);
			$password = TesterMethods::getPassword($logged);
			
			$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);
			if (!$login->getCookie()) {
				$this->errorOutput = "Script should set a cookie";
				return false;
			}
			$cook = $login->getCookie();
			if (!isset($cook['PHPSESSID'])) {
				$this->errorOutput = "Incorrect cookie set";
				return false;
			}
			$r = new ChangePermissionsRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as logged user, but not admin and incorrect value; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//logged as admin, but no id sent
	class ChangePermissionsActionIssetFalse13Test extends Test {
		public function run () {
			
			//$u = "999999";
			$logged = getRandomAdminId();
			if (!$logged) {
				$this->errorOutput = "No admin found";
				return false;
			}
			
			$username = TesterMethods::getUsername($logged);
			$password = TesterMethods::getPassword($logged);
			
			$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);
			if (!$login->getCookie()) {
				$this->errorOutput = "Script should set a cookie";
				return false;
			}
			$cook = $login->getCookie();
			if (!isset($cook['PHPSESSID'])) {
				$this->errorOutput = "Incorrect cookie set";
				return false;
			}
			$r = new ChangePermissionsRequest ("GET", false, $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset with no id sent; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//logged as admin, and invalid id
	class ChangePermissionsActionIssetFalse14Test extends Test {
		public function run () {
			
			$u = "999999";
			$logged = getRandomAdminId();
			if (!$logged) {
				$this->errorOutput = "No admin found";
				return false;
			}
			
			$username = TesterMethods::getUsername($logged);
			$password = TesterMethods::getPassword($logged);
			
			$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);
			if (!$login->getCookie()) {
				$this->errorOutput = "Script should set a cookie";
				return false;
			}
			$cook = $login->getCookie();
			if (!isset($cook['PHPSESSID'])) {
				$this->errorOutput = "Incorrect cookie set";
				return false;
			}
			$r = new ChangePermissionsRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset with incorrect id value; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}

	//logged as admin, correct id
	class ChangePermissionsActionIssetTrueTest extends Test {
		public function run () {
			
			$u = getRandomUserId();
			$logged = getRandomAdminId();
			if (!$u) {
				$this->errorOutput = "No simple user (not admin) found";
				return false;
			}
			if (!$logged) {
				$this->errorOutput = "No admin found";
				return false;
			}
			
			$username = TesterMethods::getUsername($logged);
			$password = TesterMethods::getPassword($logged);
			
			$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);
			if (!$login->getCookie()) {
				$this->errorOutput = "Script should set a cookie";
				return false;
			}
			$cook = $login->getCookie();
			if (!isset($cook['PHPSESSID'])) {
				$this->errorOutput = "Incorrect cookie set";
				return false;
			}
			$r = new ChangePermissionsRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called actionIsset logged as user and with correct id; actionIsset does not return true";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ChangePermissionsRequest1 extends Request {
		public static function test () {
			$o = new ChangePermissionsAction ();
			try {
			$o->execute();
			} catch (Exception $e) {
				if (get_class($e) == "ActionNotSetException") {
					echo "1";
				}
			}
		}
	}
	
	class ChangePermissionsRequest2 extends Request {
		public static function test () {
			custom_session_start();
			$o = new ChangePermissionsAction ();
			if ($o->actionIsset()) {
				$o->execute();
			} 
		}
	}

	class ChangePermissionsActionExecute1Test extends Test {
		public function run () {
			
			$u = getRandomUserId();
			$logged = getRandomAdminId();
			//var_dump($u);
			if (!$u) {
				$this->errorOutput = "No simple user (not admin) found";
				return false;
			}
			if (!$logged) {
				$this->errorOutput = "No admin found";
				return false;
			}
			
			$username = TesterMethods::getUsername($logged);
			$password = TesterMethods::getPassword($logged);
			
			$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);
			if (!$login->getCookie()) {
				$this->errorOutput = "Script should set a cookie";
				return false;
			}
			$cook = $login->getCookie();
			if (!isset($cook['PHPSESSID'])) {
				$this->errorOutput = "Incorrect cookie set";
				return false;
			}
			$r = new ChangePermissionsRequest2 ("GET", array("id"=>$u), $cook, false);
			
			if (!TesterMethods::isAdmin($u)){
				$this->errorOutput = "User's permissions were not changed to admin";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ChangePermissionsActionExecute2Test extends Test {
		public function run () {
			
			$u = getRandomUserId();
			if (!$u) {
				$this->errorOutput = "No simple user (not admin) found";
				return false;
			}
						
			$r = new ChangePermissionsRequest1 ("GET", array("id"=>$u), false, false);
						
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called execute, thus actionIsset returns false, exception should be thrown";
				return false;
			}
			
			return true;
		}
	}
	
	
	
	?>