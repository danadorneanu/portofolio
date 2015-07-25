<?php

	require_once("includes.inc.php");
	require_once("testerLib.inc.php");

	class UpdatePostRequest extends Request {
		public static function test () {
			custom_session_start();
			$o = new UpdatePostAction ();
			$r = $o->actionIsset();
			if (!is_null($r))
				echo intval($r);
		}
	}
	
	
	
	//user is logged, but not owner
	class UpdatePostActionIssetFalse01Test extends Test {
		public function run () {
			
			$p = getRandomPostId();
			
			$content = 'content_modified';
			$title = 'title_modified';
			
			$r = new UpdatePostRequest ("POST", array("post_id" => $p, "post_title" => $title, "post_content" => $content), false, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as guest; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//user is not logged, but tries to modify post
	class UpdatePostActionIssetFalse02Test extends Test {
		public function run () {
			
			$p = getRandomPostId();
			if (!$p) {
				$this->errorOutput = "No approved post found";
				return false;
			}
			
			$logged = getRandomUserIdDifferentFrom(TesterMethods::getOwner($p));
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
			
			$content = 'content_modified';
			$title = 'title_modified';
			
			$r = new UpdatePostRequest ("POST", array("post_id" => $p, "post_title" => $title, "post_content" => $content), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as logged user, but not owner; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//user is logged, owner, but post_id was not sent
	class UpdatePostActionIssetFalse03Test extends Test {
		public function run () {
			
			$p = getRandomPostId();
			if (!$p) {
				$this->errorOutput = "No approved post found";
				return false;
			}
			
			$logged = TesterMethods::getOwner($p);
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
			
			$content = 'content_modified';
			$title = 'title_modified';
			
			$r = new UpdatePostRequest ("POST", array("post_title" => $title, "post_content" => $content), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as owner, but post_id was not sent; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	
	//user is logged, owner, but post_title was not sent
	class UpdatePostActionIssetFalse04Test extends Test {
		public function run () {
			
			$p = getRandomPostId();
			if (!$p) {
				$this->errorOutput = "No approved post found";
				return false;
			}
			
			$logged = TesterMethods::getOwner($p);
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
			
			$content = 'content_modified';
			$title = 'title_modified';
			
			$r = new UpdatePostRequest ("POST", array("post_id" => $p, "post_content" => $content), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as owner, but post_title was not sent; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}

	
	//user is logged, owner, but post_title was not sent
	class UpdatePostActionIssetFalse05Test extends Test {
		public function run () {
			
			$p = getRandomPostId();
			if (!$p) {
				$this->errorOutput = "No approved post found";
				return false;
			}
			
			$logged = TesterMethods::getOwner($p);
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
			
			$content = 'content_modified';
			$title = 'title_modified';
			
			$r = new UpdatePostRequest ("POST", array("post_id" => $p, "post_title" => $title), $cook, false);
						
			if (trim($r->getResponse()) != "0") {
				$this->errorOutput = "Called actionIsset as owner, but post_content was not sent; actionIsset does not return false";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	//user is logged, owner, but post_title was not sent
	class UpdatePostActionIssetTrueTest extends Test {
		public function run () {
			
			$p = getRandomPostId();
			if (!$p) {
				$this->errorOutput = "No approved post found";
				return false;
			}
			
			$logged = TesterMethods::getOwner($p);
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
			
			$content = 'content_modified';
			$title = 'title_modified';
			
			$r = new UpdatePostRequest ("POST", array("post_id" => $p, "post_title" => $title, "post_content" => $content), $cook, false);
						
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called actionIsset as owner, with all fields sent; actionIsset does not return true";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	class UpdatePostRequest1 extends Request {
		public static function test () {
			$o = new UpdatePostAction ();
			try {
			$o->execute();
			} catch (Exception $e) {
				if (get_class($e) == "ActionNotSetException") {
					echo "1";
				}
			}
		}
	}
	
	class UpdatePostRequest2 extends Request {
		public static function test () {
			custom_session_start();
			$o = new UpdatePostAction ();
			if ($o->actionIsset()) {
				$o->execute();
			} 
		}
	}
	
	class UpdatePostExecute1Test extends Test {
		public function run () {
			
			$p = getRandomPostId();
			if (!$p) {
				$this->errorOutput = "No approved post found";
				return false;
			}
			
			$logged = TesterMethods::getOwner($p);
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
			$seed = rand(0,100);
			$content = 'content_modified_'.$seed;
			$title = 'title_modified_'.$seed;
			
			$r = new UpdatePostRequest2 ("POST", array("post_id" => $p, "post_title" => $title, "post_content" => $content), $cook, false);
			
			if (TesterMethods::getTitle($p) != $title) {
				$this->errorOutput = "Title of post was not changed";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			if (TesterMethods::getContent($p) != $content) {
				$this->errorOutput = "Content of post was not changed";
				$this->debugInfo .= $r->getResponse();
				return false;
			}
			
			return true;
		}
	}
	
	
	class UpdatePostExecute2Test extends Test {
		public function run () {
			
			$p = getRandomPostId();
			if (!$p) {
				$this->errorOutput = "No approved post found";
				return false;
			}
			
			$logged = TesterMethods::getOwner($p);
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
			$seed = rand(0,100);
			$content = 'content_modified_'.$seed;
			$title = 'title_modified_'.$seed;
			
			$r = new UpdatePostRequest1 ("POST", array("post_id" => $p, "post_title" => $title), $cook, false);
			
			if (trim($r->getResponse()) != "1") {
				$this->errorOutput = "Called execute, thus actionIsset returns false, exception should be thrown";
				return false;
			}
			
			return true;
		}
	}
	?>