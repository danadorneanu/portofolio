<?php

	require_once("includes.inc.php");
	require_once("testerLib.inc.php");
	
	/* ********************* APPROVE USER TESTS ****************/
	class ApproveUserRequest extends Request {
		public static function test () {
			custom_session_start();
			$o = new ApproveUserAction ();
			$r = $o->actionIsset();
			if (!is_null($r))
				echo intval($r);
		}
	}
		
	//user is not logged, but tries to approve other user
	class ApproveUserActionIssetFalse01Test extends Test {
		public function run () {
			
			$u = getRandomNewUserId();
			if (!$u) {
				$this->errorOutput = "No un-approved user found";
				return false;
			}
						
			$r = new ApproveUserRequest ("GET", array("id"=>$u), false, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as guest; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//user is logged, but not an administrator (and tries to approve somebody else)
	class ApproveUserActionIssetFalse02Test extends Test {
		public function run () {
			
			$u = getRandomNewUserId();
			$logged = getRandomUserId();
			if (!$u) {
				$this->errorOutput = "No un-approved user found";
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
			$r = new ApproveUserRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as logged user, but not admin; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApproveUserActionIssetFalse11Test extends Test {
		public function run () {
			
			$r = new ApproveUserRequest ("GET", array("id"=>"999999"), false, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as guest; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApproveUserActionIssetFalse12Test extends Test {
		public function run () {
			
			$u = "999999";
			$logged = getRandomUserId();
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
			$r = new ApproveUserRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as logged user, but not admin and incorrect value; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApproveUserActionIssetFalse13Test extends Test {
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
			$r = new ApproveUserRequest ("GET", false, $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset with no id sent; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApproveUserActionIssetFalse14Test extends Test {
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
			$r = new ApproveUserRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset with incorrect id value; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApproveUserActionIssetTrueTest extends Test {
		public function run () {
			
			$u = getRandomNewUserId();
			$logged = getRandomAdminId();
			if (!$u) {
				$this->errorOutput = "No un-approved user found";
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
			$r = new ApproveUserRequest ("GET", array("id"=>$u), $cook, false);
						
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called actionIsset logged as user and with correct id; actionIsset does not return true";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApproveUserRequest1 extends Request {
		public static function test () {
			$o = new ApproveUserAction ();
			try {
			$o->execute();
			} catch (Exception $e) {
				if (get_class($e) == "ActionNotSetException") {
					echo "1";
				}
			}
		}
	}
	
	class ApproveUserRequest2 extends Request {
		public static function test () {
			custom_session_start();
			$o = new ApproveUserAction ();
			if ($o->actionIsset()) {
				$o->execute();
			} 
		}
	}
	
	class ApproveUserActionExecute1Test extends Test {
		public function run () {
			
			$u = getRandomNewUserId();
			$logged = getRandomAdminId();
			//var_dump($u);
			if (!$u) {
				$this->errorOutput = "No un-approved user found";
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
			$r = new ApproveUserRequest2 ("GET", array("id"=>$u), $cook, false);
			
			if (!TesterMethods::isApprovedUser($u)){
				$this->errorOutput = "User was not approved";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApproveUserActionExecute2Test extends Test {
		public function run () {
			
			$u = getRandomNewUserId();
			if (!$u) {
				$this->errorOutput = "No un-approved user found";
				return false;
			}
						
			$r = new ApproveUserRequest1 ("GET", array("id"=>$u), false, false);
						
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called execute, thus actionIsset returns false, exception should be thrown";
				return false;
			}
			
			return true;
		}
	}
	
?>