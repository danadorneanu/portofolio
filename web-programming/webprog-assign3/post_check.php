<?php
require_once("includes.inc.php");

$up = new UpdatePostAction();
if ($up->actionIsset() == true)
{
	$up->execute();
 	echo "postul a fost editat";
}
else 
{
echo "a aparut o eroare la editarea postului";
}


?>