<?php	require_once("includes.inc.php");	require_once("testerLib.inc.php");		/* ********************* DISPLAY POST TESTS ****************/	class DisplayPostRequest extends Request {		public static function test () {			custom_session_start();			$o = new DisplayPostAction ();			$r = $o->actionIsset();			if (!is_null($r))				echo intval($r);			else 				echo "ActionIsset does not return a value";		}	}		class DisplayPostRequest1 extends Request {		public static function test () {			$o = new DisplayPostAction ();			try {			$o->execute();			} catch (Exception $e) {				if (get_class($e) == "ActionNotSetException") {					echo "1";				}			}		}	}		class DisplayPostRequest2 extends Request {		public static function test () {			custom_session_start();			$o = new DisplayPostAction ();			if ($o->actionIsset()) {				$o->execute();			} 		}	}	//not logged, and invalid id 	class DisplayPostActionIssetFalse01Test extends Test {		public function run () {						$r = new DisplayPostRequest ("GET", array("id"=>"999999"), false, false);									if (trim($r->getResponse()) != "0") {				$this->errorOutput = "Called actionIsset as guest, and with invalid id; actionIsset does not return false";				$this->debugInfo .= $r->getResponse();				return false;			}			return true;		}	}			//display un-approved post, as quest	class DisplayPostActionIssetFalse02Test extends Test {		public function run () {						$u = getRandomNewPostId();			if (!$u) {				$this->errorOutput = "No new post found";				return false;			}			$r = new DisplayPostRequest ("GET", array("id"=>$u), false, false);									if (trim($r->getResponse()) != "0") {				$this->errorOutput = "Called actionIsset as guest, but post is not approved; actionIsset does not return false";				$this->debugInfo .= $r->getResponse();				return false;			}						return true;		}	}			//display un-approved post, as logged user, but not owner of selected post	class DisplayPostActionIssetFalse03Test extends Test {		public function run () {						$u = getRandomNewPostId();			$logged = getRandomUserIdNotOwnerOf($u);			if (!$u) {				$this->errorOutput = "No new post found";				return false;			}			if (!$logged) {				$this->errorOutput = "No simple user (not owner of selected post) found";				return false;			}						$username = TesterMethods::getUsername($logged);			$password = TesterMethods::getPassword($logged);						$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);			if (!$login->getCookie()) {				$this->errorOutput = "Script should set a cookie";				return false;			}			$cook = $login->getCookie();			if (!isset($cook['PHPSESSID'])) {				$this->errorOutput = "Incorrect cookie set";				return false;			}			$r = new DisplayPostRequest ("GET", array("id"=>$u), $cook, false);						if (trim($r->getResponse()) != "0") {				$this->errorOutput = "Called actionIsset as logged user, but post is not approved (and user is not owner); actionIsset does not return false";				$this->debugInfo .= $r->getResponse();				return false;			}						return true;		}	}		//display un-approved post, as logged user, and owner	class DisplayPostActionIssetTrue01Test extends Test {		public function run () {						$u = getRandomNewPostId();			$logged = TesterMethods::getOwner($u);			if (!$u) {				$this->errorOutput = "No post found";				return false;			}			if (!$logged) {				$this->errorOutput = "Owner of post not found";				return false;			}						$username = TesterMethods::getUsername($logged);			$password = TesterMethods::getPassword($logged);						$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);			if (!$login->getCookie()) {				$this->errorOutput = "Script should set a cookie";				return false;			}			$cook = $login->getCookie();			if (!isset($cook['PHPSESSID'])) {				$this->errorOutput = "Incorrect cookie set";				return false;			}			$r = new DisplayPostRequest ("GET", array("id"=>$u), $cook, false);									if (trim($r->getResponse()) != "1") {				$this->errorOutput = "Called actionIsset as owner of post; actionIsset does not return true";				$this->debugInfo .= $r->getResponse();				return false;			}						return true;		}	}		//display un-approved post, as admin	class DisplayPostActionIssetTrue02Test extends Test {		public function run () {						$u = getRandomNewPostId();			$logged = getRandomAdminId();			if (!$u) {				$this->errorOutput = "No post found";				return false;			}			if (!$logged) {				$this->errorOutput = "No admin found";				return false;			}						$username = TesterMethods::getUsername($logged);			$password = TesterMethods::getPassword($logged);						$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);			if (!$login->getCookie()) {				$this->errorOutput = "Script should set a cookie";				return false;			}			$cook = $login->getCookie();			if (!isset($cook['PHPSESSID'])) {				$this->errorOutput = "Incorrect cookie set";				return false;			}			$r = new DisplayPostRequest ("GET", array("id"=>$u), $cook, false);									if (trim($r->getResponse()) != "1") {				$this->errorOutput = "Called actionIsset as administrator; actionIsset does not return true";				$this->debugInfo .= $r->getResponse();				return false;			}						return true;		}	}		//display post as guest	class DisplayPostActionExecute01Test extends Test {		public function run () {						$u = getRandomPostId();			$r = new DisplayPostRequest2 ("GET", array("id"=>$u), false, false);						echo "<br/><br/>";			echo $r->getResponse();			echo "<br/><br/>";						return true;		}	}		//display post as logged user	class DisplayPostActionExecute02Test extends Test {		public function run () {						$u = getRandomPostId();			$logged = getRandomUserId();			if (!$u) {				$this->errorOutput = "No post found";				return false;			}			if (!$logged) {				$this->errorOutput = "No user found";				return false;			}						$username = TesterMethods::getUsername($logged);			$password = TesterMethods::getPassword($logged);						$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);			if (!$login->getCookie()) {				$this->errorOutput = "Script should set a cookie";				return false;			}			$cook = $login->getCookie();			if (!isset($cook['PHPSESSID'])) {				$this->errorOutput = "Incorrect cookie set";				return false;			}			$r = new DisplayPostRequest2 ("GET", array("id"=>$u), $cook, false);						echo "<br/><br/>";			echo $r->getResponse();			echo "<br/><br/>";						return true;		}	}	//display post as admin	class DisplayPostActionExecute03Test extends Test {		public function run () {						$u = getRandomPostId();			$logged = getRandomAdminId();			if (!$u) {				$this->errorOutput = "No post found";				return false;			}			if (!$logged) {				$this->errorOutput = "No user found";				return false;			}						$username = TesterMethods::getUsername($logged);			$password = TesterMethods::getPassword($logged);						$login = new LoginRequest2 ("POST", array("username" => $username,"password" => $password), false, false);			if (!$login->getCookie()) {				$this->errorOutput = "Script should set a cookie";				return false;			}			$cook = $login->getCookie();			if (!isset($cook['PHPSESSID'])) {				$this->errorOutput = "Incorrect cookie set";				return false;			}			$r = new DisplayPostRequest2 ("GET", array("id"=>$u), $cook, false);						echo "<br/><br/>";			echo $r->getResponse();			echo "<br/><br/>";						return true;		}	}		//call execute when actionIsset returns false	class DisplayPostActionExecute04Test extends Test {		public function run () {						$u = "999999";			$r = new DisplayPostRequest1 ("GET", array("id"=>$u), false, false);									if (trim($r->getResponse()) != "1") {				$this->errorOutput = "Called execute, thus actionIsset returns false, exception should be thrown";				return false;			}						return true;		}	}			?>