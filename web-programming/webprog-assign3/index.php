<?php
require_once("includes.inc.php");
$test = new TesterMethods();
$posts = $test->getPostList();


//if(!session_id())
//{
	session_start();
//}
if (!isset($_SESSION[SESSION_NAME]) || $_SESSION[SESSION_NAME]=="")
{
	echo "sesiune : ".$_SESSION[SESSION_NAME]."  ..<br>"; 
?>

<html>
<head> </head>
<body>
<h1> Login </h1>
<form method="POST" action="login.php">
	<input name="username" type="text" /> <br>
	<input name="password" type="password" /> <br>
	<br>
	<input name="trimite" value="trimite" type="submit" /><br>
</form>
<?php 
}
else {
	
	echo "sesiune : ".$_SESSION[SESSION_NAME]."  ..<br>"; 
	echo "Utilizator logat";
	?>
	<form method="POST" action="logout.php">	
	<input value = "LOGOUT" type="submit"/>
	</form>
	<?php 
}
foreach($posts as $key=>$value)
{
	
	
	$content=$test->getContent($value);
	$title = $test->getTitle($value);
	$ownerid = $test->getOwner($value);
	$username = $test->getUsername($ownerid); 
	/*
	echo "<br>".$username." wrote: <br>";
	echo "<br> Subject <i>".$title."</i><br>";
	echo "<br> $content <br> ";
	*/
	echo '<table width="80%" height="7em" style="border-color: #000; border-style:solid; border-width:1px; " >';
    echo "<tr>";
	echo '<td> Owner <i>'.$username.'</i></td>';
	echo "<tr>";

	echo "<tr>";
	echo '<td> Subject: <i>'.$title.'</i></td>';
	echo "</tr>";
    echo "<tr>";
	echo '<td> Content:</td>';
	echo "</tr>";
    echo "<tr>";    
	echo '<td >
			<table width="100%" style="border-color: #000; border-style:solid; border-width:1px; ">
			<tr>
				<td> <i>'. $content.'</i></td>				
			</tr>
			<tr><td>...</td></tr>
			</table>
		  </td>';	
	echo "</tr><tr><td>";
	
?>
	<form method="GET" action="post.php">
	<input name = "id" type="hidden" value='<?php echo "".$value."" ?>'/>
	<input value = "editeaza_<?php echo "".$value."" ?>" type="submit"/>
	</form>
	
<?php 
echo "</td></tr></table>";
}


?>
</body>
</html>