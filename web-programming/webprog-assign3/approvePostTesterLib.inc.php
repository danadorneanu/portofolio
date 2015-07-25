<?php

	require_once("includes.inc.php");
	require_once("testerLib.inc.php");

	/* ********************* APPROVE POST TESTS ****************/
	class ApprovePostRequest extends Request {
		public static function test () {
			custom_session_start();
			$o = new ApprovePostAction ();
			$r = $o->actionIsset();
			if (!is_null($r))
				echo intval($r);
		}
	}
	
	class ApprovePostActionIssetFalse01Test extends Test {
		public function run () {
			
			$p = getRandomNewPostId();
			if (!$p) {
				$this->errorOutput = "No un-approved post found";
				return false;
			}
						
			$r = new ApprovePostRequest ("GET", array("id"=>$p), false, false);
			
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as guest; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostActionIssetFalse02Test extends Test {
		public function run () {
			
			$p = getRandomNewPostId();
			$logged = getRandomUserId();
			if (!$p) {
				$this->errorOutput = "No un-approved post found";
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
			$r = new ApprovePostRequest ("GET", array("id"=>$p), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as logged user, but not admin; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostActionIssetFalse11Test extends Test {
		public function run () {
			
			$r = new ApprovePostRequest ("GET", array("id"=>"999999"), false, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as guest; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostActionIssetFalse12Test extends Test {
		public function run () {
			
			$p = "999999";
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
			$r = new ApprovePostRequest ("GET", array("id"=>$p), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as logged user, but not admin and incorrect value; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostActionIssetFalse13Test extends Test {
		public function run () {
			
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
			$r = new ApprovePostRequest ("GET", false, $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset with no id sent; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostActionIssetFalse14Test extends Test {
		public function run () {
			
			$p = "999999";
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
			$r = new ApprovePostRequest ("GET", array("id"=>$p), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset with incorrect id value; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostActionIssetTrueTest extends Test {
		public function run () {
			
			$p = getRandomNewPostId();
			$logged = getRandomAdminId();
			if (!$p) {
				$this->errorOutput = "No un-approved post found";
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
			$r = new ApprovePostRequest ("GET", array("id"=>$p), $cook, false);
						
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called actionIsset logged as user and with correct id; actionIsset does not return true";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostRequest1 extends Request {
		public static function test () {
			$o = new ApprovePostAction ();
			try {
			$o->execute();
			} catch (Exception $e) {
				if (get_class($e) == "ActionNotSetException") {
					echo "1";
				}
			}
		}
	}
	
	class ApprovePostRequest2 extends Request {
		public static function test () {
			custom_session_start();
			$o = new ApprovePostAction ();
			if ($o->actionIsset()) {
				$o->execute();
			} 
		}
	}
	
	class ApprovePostActionExecute1Test extends Test {
		public function run () {
			
			$p = getRandomNewPostId();
			$logged = getRandomAdminId();
			if (!$p) {
				$this->errorOutput = "No un-approved post found";
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
			$r = new ApprovePostRequest2 ("GET", array("id"=>$p), $cook, false);
			
			if (!TesterMethods::isApprovedPost($p)){
				$this->errorOutput = "Post was not approved";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class ApprovePostActionExecute2Test extends Test {
		public function run () {
			
			$p = getRandomNewPostId();
			if (!$p) {
				$this->errorOutput = "No un-approved post found";
				return false;
			}
						
			$r = new ApprovePostRequest1 ("GET", array("id"=>$p), false, false);
						
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called execute, thus actionIsset returns false, exception should be thrown";
				return false;
			}
			
			return true;
		}
	}
	
?>