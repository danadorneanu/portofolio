<?php
require_once("includes.inc.php");

$postid = $_REQUEST['id'];
$methodtest = new TestMethods();
$postcontent = $methodtest->getPostContent($postid);
$myusername = unserialize(stripcslashes($_COOKIE["user"]));
$auth = new Auth($myusername);
$id_poster = $auth->getId();

if($_POST['Submit']){
	// Get parameters from form.
	$id=$_POST['post'];
	// Do update statement.
	$db = SingletonDB::connect();
	$query = "update pw_users set value='$name' where cod='$postid'";
	$result = $db->query($query);
}

if ($auth->isAdmin())
{

	?>
<form method="POST" action="<? echo $PHP_SELF; ?>">
<p>Editeaza post : <input name="post" type="text"
	value="<?php echo $postcontent; ?>" /> <br>
</p>
<br>
<input name="update" type="submit" /><br>
</form>
	<?php
}
else
{
	echo "postid = $postid, id = $id_poster";
	if ($methodtest->isOwner($postid, $id_poster))
	{
		
		?>
<form method="POST" action="<? echo $PHP_SELF; ?>">
<p>Editeaza post : <input name="post" type="text"
	value="<?php echo $postcontent; ?>" /> <br>
</p>
<br>
<input name="update" type="submit" /><br>
</form>
		<?php
	}
	else echo "<br> nu aveti permisiune de editare <br>";
}

?>