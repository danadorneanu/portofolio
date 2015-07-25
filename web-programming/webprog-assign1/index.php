<html>
<head>
<title> Obiecte </title>
</head>

<body>

<form method = "GET" action = "script.php">
<input type = "hidden" name = "pageNo" value = 1>
<b> Sorteaza lista dupa nume </b> 
<br>
<b>Mod</b>
<select name="modeSort">
	<option value="ASC" selected="selected"> ascendent </option>
	<option value="DESC"> descendent </option>
</select>
<br>
<b>Filtreaza lista de obiecte dupa un domeniu</b>

<select name="valuesFilter">
<?php
require_once('includes.inc.php');
$db = SingletonDB::connect();
$query = "select id,name from domenii";
?>  <?php echo $query ?> <?php 
$result = $db->query($query); 
while ( $row = mysqli_fetch_row($result))
{?>
<option value= <?php echo $row[0]?>> <?php echo $row[1]?></option>
<?php } ?>
</select>
<input type = "submit" value = "OK" >
</form>

</body>
</html>