<?php
require_once("includes.inc.php");

?>
	<form action="post_check.php" method ='POST'>
	<h3> Titlu
		<input type='text' name='post_title' />  </h3>
	<h3> Content 
		<input type='text' name='post_content' /></h3>
		<input type='hidden' name='post_id' value ='<?php echo "".$_GET['id']."" ?>' />
		<input type='submit' value='trimite' />
	   </form>
<?php 

?>