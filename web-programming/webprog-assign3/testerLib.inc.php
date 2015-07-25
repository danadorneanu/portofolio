<?php

	require_once("includes.inc.php");
	require_once("loginTesterLib.inc.php");
	require_once("approveUserTesterLib.inc.php");
	require_once("approvePostTesterLib.inc.php");
	require_once("changePermissionsTesterLib.inc.php");
	require_once("displayPostTesterLib.inc.php");
	require_once("updatePostTesterLib.inc.php");
	
	abstract class Test {
		
		protected $testName;
		public $value;
		protected $errorOutput = null;
		protected $stops = false;
		
		protected $debug = false;
		protected $debugInfo = "";
		
		
		//members that will be populated after test is run;
		private $result = null;
		
		// runs current test (must return true/false)
		public abstract function run ();
		// tells us if we should stop the test sequence
		
		//default basic constructor; may be overriden
		public function __construct ($name = false, $value = false, $stops = false) {
			$this->testName = $name;
			$this->value = $value;
			$this->stops = $stops;
		}
		
		//runs test, and populates test environment
		public function runTest () {
			$this->result = $this->run();
		}		
		public function getStatus () {
			return ($this->result) ? ("PASSED") : ("FAILED");
		}
		public function debuggingOn(){
			
			$this->debug = true;
		}
		public function getErrorOutput () {
			return $this->errorOutput;
		}
		public function getDebugInfo () {
			return $this->debugInfo;
		}
		public function getDebug () {
			return $this->debug;
		}
		public function displayResults () {
			?>
			<div style="width:800px; text-align:left; float:left"> <?php echo $this->testName; ?> (<?php echo $this->value; ?>p) </div>
			<div style="width:200px; text-align:left; float:left; font-weight:bold;"> <?php echo $this->getStatus(); ?> </div>
			<div style="clear:both"></div>
			<?php
			
			if ($this->debug) {
				
				?>
				<div style="width:800px; text-align:left; float:left; color:#66CC00;"> <?php echo "<b>Debugging output:</b></br>".$this->debugInfo; ?> </div>
				<div style="clear:both"></div>
				<?php
			}
			
			if ($this->errorOutput != false)
			{
				?>
				<div style="width:800px; text-align:left; float:left; color:#FF0000;"> <?php echo "<b>Error output:</b>".$this->errorOutput; ?> </div>
				<div style="clear:both"></div>
				<?php
			}
			
		}
		public function getResult () {
			return $this->result;
		}
		public function stops (){
			return $this->stops;
		}
		public function success () {
			return ($this->result == true);
		}
		public function failed () {
			return ($this->result == false);
		}
	}

	class TestSequence extends Test {
	
		public $tests = array();
		private $grade = 0;
		
		public function __construct ($testName) {
			$this->testName = $testName;
		}
		
		public function run (){
			
			
			$this->displayTitle();
			
			foreach ($this->tests as $test){
				if ($this->debug)
					$test->debuggingOn();
				
				$test->runTest();
				//display Test Results
				$test->displayResults();
				
				if ($test->success())
					$this->grade += $test->value;
				
				//stop if test failed and it is a stopper	
				if ($test->failed() && $test->stops()){
					$this->displayGrade();
					return;
				}
			}
			$this->displayGrade();
		}
		public function add (Test $test) {
			$this->tests [] = $test;
		}
		private function displayGrade() {
			?>
			<div style="width:800px; text-align:left; font-weight:bold; color:#0000ff;"> <?php echo $this->testName; ?> grade: <?php echo $this->grade; ?> </div>
			<?php
		}
		private function displayTitle () {
		?>
		<br>
		<div style="width:800px; text-align:left;"><b> <?php echo $this->testName; ?> </b></div>
		<?php
		}
		public function getGrade(){
			return $this->grade;
		}
	}

	
	abstract class ContextDecorator extends Test {
		public $test;
		public function __construct ($test) {
			$this->testName = $test->testName;
			$this->value = $test->value;
			$this->stops = $test->stops;
			$this->test = $test;
		}
		protected abstract function contextHeader ();
		protected abstract function contextFooter ();
		public function run () {
			$this->contextHeader();
			$value = $this->test->run();
			$this->contextFooter();
			
			//var_dump($this->test->getDebugInfo());
			$this->errorOutput = $this->test->getErrorOutput();
			$this->debugInfo .= $this->test->getDebugInfo();
			$this->debug = $this->debug || $this->test->getDebug();
			return $value;
		}
	}
	
	//decorator that runs a test, and returns false if test throws exception
	class NoExceptionDecorator extends Test {
		public $test;
		public function __construct ($test) {
			$this->testName = $test->testName;
			$this->value = $test->value;
			$this->stops = $test->stops;
			$this->test = $test;
		}
		public function run () {
			try {
				
				$value = $this->test->run();

			}catch (Exception $e) {
				$this->errorOutput = "Tester caught unexpected exception:<br/> $e <br/>";
				$this->debugInfo .= $this->test->getDebugInfo();
				$this->debug = $this->debug || $this->test->getDebug();
				return false;
			}
			$this->errorOutput = $this->test->getErrorOutput();
			$this->debugInfo .= $this->test->getDebugInfo();
			$this->debug = $this->debug || $this->test->getDebug();
			return $value;
		}
	}
	
	class ExceptionDecorator extends Test {
		public $test;
		public $exception;
		
		public function __construct ($test, $exception) {
			$this->testName = $test->testName;
			$this->value = $test->value;
			$this->stops = $test->stops;
			$this->test = $test;
			$this->exception = $exception;
		}
		public function run () {
			try {
				$this->test->run();
			}
			catch (Exception $e) {
				if (get_class($e) == $this->exception) {
					
					$this->debugInfo .= $this->test->getDebugInfo();
					$this->debug = $this->debug || $this->test->getDebug();
					
					return true;
				}
				else 
					$this->errorOutput = "Received exception $e, expected ".$this->exception." <br/>";
			}
			if (!$this->errorOutput)
				$this->errorOutput = "Test should throw exception ".$this->exception."; No exception is thrown ";
			
			$this->errorOutput .= $this->test->getErrorOutput();
			$this->debugInfo .= $this->test->getDebugInfo();
			$this->debug = $this->debug || $this->test->getDebug();
			
			return false;
		}
	}
	/* ********************* MIXED DECORATORS *******************/
	
	
	/**************** TEST IMPLEMENTATIONS ************************/
	/* file existance test */
	class FileExistanceTest extends Test {
		public $fileName;
		public function __construct ($name, $value, $stops, $fileName) {
			$this->testName = $name;
			$this->value = $value;
			$this->stops = $stops;
			$this->fileName = $fileName;
		}
		public function run () {
			$this->debugInfo .= "Checking if file ".$this->fileName." exists ";
			$value = file_exists($this->fileName);
			if (!$value) {
				$this->errorOutput = "No such file ".$this->fileName." exists ";
			}
			return $value; 
		}
	}
	
	/* class existance test */
	class ClassExistanceTest extends Test {
		public $className;
		public function __construct ($name, $value, $stops, $className) {
			$this->testName = $name;
			$this->value = $value;
			$this->stops = $stops;
			$this->className = $className;
		}
		public function run () {
			$this->debugInfo .= "Checking if class ".$this->className." exists <br/>";
			$value = class_exists($this->className);
			if (!$value) {
				$this->errorOutput = "No such class ".$this->className." exists ";
			}
			return $value;
		}
	}
	
	/* class implements interface test */
	class ClassImplementsInterfaceTest extends Test {
		public $className;
		public $interfaceName;
		public function __construct ($name, $value, $stops, $className,$interfaceName) {
			$this->testName = $name;
			$this->value = $value;
			$this->stops = $stops;
			$this->className = $className;
			$this->interfaceName = $interfaceName;
		}
		public function run () {
			$this->debugInfo .= "Checking if class ".$this->className." implements interface ".$this->interfaceName." <br/>";
			$reflectionClass = new ReflectionClass($this->className);
			$value = $reflectionClass->implementsInterface($this->interfaceName);
			if (!$value) {
				$this->errorOutput = "Class ".$this->className." does not implement interface ".$this->interfaceName." ";
			}
			return $value;
		}
	}

	class ConstantDefinedTest extends Test {
		
		public $constant;
		public function __construct ($name, $value, $stops, $constant) {
			$this->testName = $name;
			$this->value = $value;
			$this->stops = $stops;
			$this->constant = $constant;
		}
		
		public function run () {
			
			$errorOutput = "";
			if (!defined($this->constant))
				$errorOutput .= $this->constant;
			
			if ($errorOutput == "")
				return true;
			else
			{
				$errorOutput .=" constant(s) is(are) not defined ";
				$this->errorOutput = $errorOutput;
				return false;
			}
		}
	}
	
	class CreateDatabaseTest extends Test {
		public $sqlFile;
		public function __construct ($name, $value, $stops, $sqlFile) {
			$this->testName = $name;
			$this->value = $value;
			$this->stops = $stops;
			$this->sqlFile = $sqlFile;
		}
		public function run () {
			
			if (!file_exists($this->sqlFile)) {
				$this->errorOutput="No such file ".$this->sqlFile." found";
				return false;
			}
			
			$con = new mysqli(ADDRESS, USERNAME, PASSWORD, DATABASE);
			$fh = fopen($this->sqlFile,"r");
			if (!$fh) {
				$this->errorOutput = "Cannot open ".$this->sqlFile." ;";
				return false;
			}
			$query = fread($fh,filesize($this->sqlFile));
			if (!$query) {
				$this->errorOutput = "Cannot read from ".$this->sqlFile." ;";
				return false;
			}
			$res = $con->multi_query($query);
			if (!$res) {
				$this->errorOutput = "Cannot run query from ".$this->sqlFile." MYSQL said: ".$con->error."  ERROR CODE:".$con->errno.";";
				return false;
			}
			
			return true;
		}
	}
	
	function clearDatabase () {
		$con = new mysqli(ADDRESS, USERNAME, PASSWORD, DATABASE);
		$result = $con->query("Drop database ".DATABASE);
		if (!$result) {
			echo "Query failed ".$con->error."<br/>";
		}
		$con->query('Create database '.DATABASE);
	}
	
	abstract class Request {
		
		private $scriptName = "testScript.php";
		private $header;
		private $content;
		private $cookie;
		//return full URL of script (independent on server location)
		
		private function buildURL ($file) {
			
			$arr = explode('/',$_SERVER['SERVER_NAME'].$_SERVER['PHP_SELF']);
			array_pop($arr);
			array_push($arr,$file);
			$urlString = 'http://'.implode('/',$arr);
			return $urlString;
		}
		
		//build information string
		private function buildData ($info) {
			if (!$info)
				return "";
				
			$data = array();
			foreach ($info as $key => $value) {
				$data[] = "$key=$value";
			}
			$string = implode('&', $data);
			return $string;
		}
		
		
		public function __construct ($methodType, //request method type: GET/POST
									 $info = false, //information to be sent, optional
									 $cookie = false, //cookie to be set, optional
									 $script = false //name of the script for the request
									 ) {
			
			$realScript = false;
			
			//script will be generated automatically, based on $testCode
			if (!$script) {
				
				$fh = fopen($this->scriptName,"w");
				fwrite($fh,"<?php require_once('testerLib.inc.php'); ".get_class($this)."::test(); ?>");
				fclose($fh);
				$realScript = $this->scriptName;
			}
			else
				$realScript = $script;
			
			//build URL array for request
			$url = parse_url($this->buildURL($realScript));
			// extract host and path:
			$host = $url['host'];
			$path = $url['path'];
			$data = $this->buildData($info);
			
			echo "<br>";
			print_r($data);
			echo "<br>";
			// send request 
			$fp = fsockopen($host, 80);
	 
			if ($methodType == "GET")
				$path .= "?".$data;
			// send the request headers:
			fputs($fp, "$methodType $path HTTP/1.1\r\n");
			fputs($fp, "Host: $host\r\n");
			if ($methodType == "POST") {
				fputs($fp, "Content-type: application/x-www-form-urlencoded\r\n");
				fputs($fp, "Content-length: ". strlen($data) ."\r\n");
			}
			if ($cookie) {
				$cook = "";
				foreach ($cookie as $key => $value) {
					$cook .="$key=$value";
				}
				fputs($fp, "Cookie: $cook; \r\n");
			}
			fputs($fp, "Connection: close\r\n\r\n");
			if ($methodType == "POST") {
				fputs($fp, $data);
			}
			
			$result = ''; 
			while(!feof($fp)) {
				// receive the results of the request
				$result .= fgets($fp, 128);
			}
			
			echo "<br> -----result -----<br>";
			print($result);
			echo "<br> ------------------<br>";
		 	// close the socket connection:
			fclose($fp);
		 
			// split the result header from the content
			$result = explode("\r\n\r\n", $result, 2);
		 
			$this->header = isset($result[0]) ? $result[0] : '';
			$this->content = isset($result[1]) ? $result[1] : '';
		    
			//delete code file
			if (!$script) {
				unlink($this->scriptName);
			}
		}
		
		public function getResponse() {
			return $this->content;
		}
		public function getResponseHeader() {
			return $this->header;
		}
		public function getCookie () {
			
			if (preg_match ("/Set-Cookie: ([a-zA-Z0-9])*=([a-zA-Z0-9])*/",$this->header,$matches) == 0)
				return false;
			
			$arr = explode(" ",$matches[0]);
			$arr = explode("=",$arr[1]);
			
			return array($arr[0] => $arr[1]);
		}
		
		public abstract static function test ();
		
	}
		
	function getRandomNewPostId () {
		$pl = TesterMethods::getPostList();
		$fin = array();
		foreach ($pl as $post) {
			if  (!TesterMethods::isApprovedPost($post))
				$fin [] = $post;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	function getRandomPostId () {
		$pl = TesterMethods::getPostList();
		$fin = array();
		foreach ($pl as $post) {
			if  (TesterMethods::isApprovedPost($post))
				$fin [] = $post;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	function getRandomNewUserId () {
		$ul = TesterMethods::getUserList();
		$fin = array();
		foreach ($ul as $user) {
			if (!TesterMethods::isAdmin($user) && !TesterMethods::isApprovedUser($user))
				$fin [] = $user;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	function getRandomUserId () {
		$ul = TesterMethods::getUserList();
		$fin = array();
		foreach ($ul as $user) {
			if (!TesterMethods::isAdmin($user))
				$fin [] = $user;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	function getRandomUserIdDifferentFrom ($uid) {
		$ul = TesterMethods::getUserList();
		$fin = array();
		foreach ($ul as $user) {
			if ($user != $uid)
				$fin [] = $user;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	function getApprovedUser () {
		$ul = TesterMethods::getUserList();
		$fin = array ();
		foreach ($ul as $user) {
			if (TesterMethods::isApprovedUser($user))
				$fin [] = $user;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	function getRandomUserIdNotOwnerOf ($post) {
		$ul = TesterMethods::getUserList();
		$fin = array();
		foreach ($ul as $user) {
			if (!TesterMethods::isOwner($user,$post) && !TesterMethods::isAdmin($user))
				$fin [] = $user;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	function getRandomAdminId () {
		$ul = TesterMethods::getUserList();
		$fin = array();
		foreach ($ul as $user) {
			if (TesterMethods::isAdmin($user))
				$fin [] = $user;
		}
		if (empty($fin))
			return false;
		else
			return $fin[array_rand($fin)];
	}
	
	
	function custom_session_start () {
		if (session_id() == "") // no session is started
			session_start();
	}
	
	function space(){
		echo "<br/>";
	}
	
	function displayGrade ($grade) {
		?>
		<div style="width:800px; text-align:left; font-weight:bold; color:#0000ff;"> Grade on tests: <?php echo $grade; ?> </div>
		<?php
	}
	
?>