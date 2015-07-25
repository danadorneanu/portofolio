<?php
require_once("includes.inc.php");
$test = new TestMethods();
$posts = $test->getPostList();
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
foreach($posts as $key=>$value)
{
	$content=$test->getPostContent($value);
	echo "<br> $content <br> ";
	
?>
	<form method="GET" action="post.php">
	<input name = "id" type="hidden" value='<?php echo "".$value."" ?>'/>
	<input value = "editeaza_<?php echo "".$value."" ?>" type="submit"/>
	</form>
	
<?php 
}


?>
</body>
</html>