<?php
require_once("includes.inc.php");

$la = new LoginAction();
$la->execute();
//header("Location:http://localhost/~dana/t3/index.php");
header("location:index.php"); 


?>