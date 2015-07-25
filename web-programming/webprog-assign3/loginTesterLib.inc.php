<?php

	require_once("includes.inc.php");
	require_once("testerLib.inc.php");

	/* **************** LOGIN TESTS *******************/
	
	class LoginRequest extends Request {
		public static function test () {
			$o = new LoginAction ();
			$r = $o->actionIsset();
			if (!is_null($r))
				echo intval($r);
		}
	}
	
	class LoginActionIssetFalse00Test extends Test {
		public function run () {
			$r = new LoginRequest ("GET", false, false, false);
			if (rtrim($r->getResponse()) != "0") {
				$this->debugInfo = "Script response was: ".$r->getResponse()."<br/>";
				$this->errorOutput = "ActionIsset returns true, but no form was sent";
				return false;
			}
			return true;
		}
	}
	
	class LoginActionIssetFalse01Test extends Test {
		public function run () {
			$r = new LoginRequest ("POST", array("username" => "","password" => ""), false, false);
			if (rtrim($r->getResponse()) != "0") {
				$this->debugInfo = "Script response was: ".$r->getResponse()."<br/>";
				$this->errorOutput = "ActionIsset returns true, but void form was sent";
				return false;
			}
			return true;
		}
	}
	
	class LoginActionIssetFalse1Test extends Test {
		public function run () {
			$user = "INVALID_USER";
			$pass = "INVALID_PASS";
			$r = new LoginRequest ("POST", array("username" => $user,"password" => $pass), false, false);
			if (rtrim($r->getResponse()) != "0") {
				$this->debugInfo = "Script response was: ".$r->getResponse()."<br/>";
				$this->errorOutput = "ActionIsset returns true, but incorrect username/password was sent";
				return false;
			}
			return true;
		}
	}
	
	class LoginActionIssetFalse02Test extends Test {
		public function run () {
			//$ul = TesterMethods::getUserList();
			//$id = rand(1,count($ul));
			$id = getApprovedUser();
			
			$user = TesterMethods::getUsername($id);
			$pass = "INVALID_PASS";
			$r = new LoginRequest ("POST", array("username" => $user,"password" => $pass), false, false);
			if (rtrim($r->getResponse()) != "0") {
				$this->debugInfo = "Script response was: ".$r->getResponse()."<br/>";
				$this->errorOutput = "ActionIsset returns true, but password is incorrect";
				return false;
			}
			return true;
		}
	}
	
	class LoginActionIssetFalse03Test extends Test {
		public function run () {
			//$ul = TesterMethods::getUserList();
			//$id = rand(1,count($ul));
			$id = getApprovedUser();
			$user = "INVALID_USERNAME";
			$pass = TesterMethods::getPassword($id);
			$r = new LoginRequest ("POST", array("username" => $user,"password" => $pass), false, false);
			if (rtrim($r->getResponse()) != "0") {
				$this->debugInfo = "Script response was: ".$r->getResponse()."<br/>";
				$this->errorOutput = "ActionIsset returns true, but username is incorrect";
				return false;
			}
			return true;
		}
	}
	
	class LoginActionIssetTrueTest extends Test {
		public function run () {
			//$ul = TesterMethods::getUserList();
			//$id = rand(1,count($ul));
			$id = getApprovedUser();
			
			$user = TesterMethods::getUsername($id);
			$pass = TesterMethods::getPassword($id);
			$r = new LoginRequest ("POST", array("username" => $user,"password" => $pass), false, false);
			if (rtrim($r->getResponse()) != "1") {
				$this->debugInfo = "Script response was: ".$r->getResponse()."<br/>";
				$this->errorOutput = "ActionIsset returns false, but correct username && password was sent";
				return false;
			}
			return true;
		}
	}
	
	class LoginRequest1 extends Request {
		public static function test () {
			$o = new LoginAction ();
			try {
			$o->execute();
			} catch (Exception $e) {
				if (get_class($e) == "ActionNotSetException") {
					echo "1";
				}
			}
		}
	}
	
	class LoginRequest2 extends Request {
		public static function test () {
			custom_session_start();
			$o = new LoginAction ();
			if ($o->actionIsset()) {
				$o->execute();
			} 
		}
	}
	class LoginActionExecute1Test extends Test {
		public function run () {
			$user = "INVALID_USER";
			$pass = "INVALID_PASS";
			$r = new LoginRequest1 ("POST", array("username" => $user,"password" => $pass), false, false);
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Execute does not throw ActionNotSetException";
				return false;
			}
			return true;
		}
	}
	
	
	
	class LoginRequest2a extends Request {
		public static function test () {
			custom_session_start();
			echo $_SESSION[SESSION_NAME]; 
		}
	}
	
	class LoginActionExecute2Test extends Test {
		public function run () {
			//$ul = TesterMethods::getUserList();
			//$id = rand(1,count($ul));
			$id = getApprovedUser();
			$user = TesterMethods::getUsername($id);
			$pass = TesterMethods::getPassword($id);
			$r = new LoginRequest2 ("POST", array("username" => $user,"password" => $pass), false, false);
			//print_r($_REQUEST);
			//die("aici");

			if (!$r->getCookie()) {
				$this->errorOutput = "Script should set a cookie";
				return false;
			}
			$cook = $r->getCookie();
			if (!isset($cook['PHPSESSID'])) {
				$this->errorOutput = "Incorrect cookie set";
				return false;
			}
			
			$newr = new LoginRequest2a ("GET", false, $cook, false);
			
			$val =  rtrim($newr->getResponse()); 
			print_r ($newr);
			echo "val = $val, id = $id <br>";
			if ($val != $id) {
				$this->errorOutput = "Found incorrect value in session :".rtrim($newr->getResponse());
				return false;
			}			
			return true;
		}
	}
	
	/* ********************* END of LOGIN TESTS ******************/
?>