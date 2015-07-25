<?php
require_once("includes.inc.php");
//session_name(SESSION_NAME);
//session_start();
//session_destroy();
$myusername=$_POST['username'];
$mypassword=$_POST['password'];

$myusername = stripslashes($myusername);
$mypassword = stripslashes($mypassword);

try  {
	$db = SingletonDB::connect();
	$query = "select id from pw_users where username='".$myusername."'"." and password ='".$mypassword."'";
	//echo $query."<br>";
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
	//echo "count<br>";
	$count++;
}
//echo "<br> nr de randuri este $count <br>";

if ($count == 1)
{
	//echo "<br> UTILIZATOR CORECT <br>";
	//echo "<br>---111";
	print_r($_SESSION);
	//echo "----<br>";
	
	$auth = new Auth($myusername);
	$_SESSION=array();
	$_SESSION["user"]=serialize($auth);
	setcookie("user", serialize($myusername));
	//echo "<br>---222";
	//print_r($_SESSION);
}
else {
	//echo "registration falied";
	
}

?>