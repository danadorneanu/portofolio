<?php

require_once("includes.inc.php");
if(!session_id())
{
	session_start();
}

$_SESSION[SESSION_NAME] = "";
//echo "sesiune : ".$_SESSION[SESSION_NAME]."  ..<br>"; 

header("location:index.php"); 
?>