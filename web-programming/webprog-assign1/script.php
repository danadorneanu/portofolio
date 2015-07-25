<html>
<head>
<title> Lista obiectelor</title>
<link rel="stylesheet" type="text/css" href="tabel.css" media="all" />
</head>
<body>
<div class = "titlu">
Lista obiectelor
</div>
<div id = "content">
<table id = "tabel">
<?php require_once('includes.inc.php'); 
$tablename = 'descriere';
$sort_mode = 'ASC';
$tip = "";
$restriction = false;

if (isset($_REQUEST['modeSort']))
		$sort_mode = $_REQUEST['modeSort'];
if ( isset($_REQUEST['valuesFilter']) && $_REQUEST['valuesFilter']!= false)
{
	$tip = $_REQUEST['valuesFilter'];
	$restriction = array("id_domenii" => $_REQUEST['valuesFilter']);
}
	
	$collection = CollectionFactory::getCollection ("obiecte", $restriction, 
	array(), array(), array(), array(), "name",$sort_mode, 10, 0);
	
	
	//print_r($collection);
	$con = new mysqli(ADDRESS, USERNAME, PASSWORD, DATABASE);
	$res = $con->query("SELECT * from obiecte");
	$row = $res->fetch_assoc();
	echo "<tr>";
	foreach ($row as $key => $value) 
		echo "<td>      ".'    '.$key.'   '."      </td>";
	echo "</tr>";
	
	$noEntries = 0;
	$currentPage = 0;
	while ($collection->hasNext()) {
		
		$noEntries++;
		$noPages = $noEntries/$collection->itemsPerPage;
		$currentPage = $_REQUEST['pageNo'];
		$collection->pageNo = $currentPage;
		
		$item = $collection->next();
		
		$query="SELECT * from obiecte where id=".$item->getId(). " ";
		
		$res = $con->query($query);
		$row = $res->fetch_assoc();
		
		echo "<tr>";	
		foreach ($row as $key => $value) 	
		{	
			if (substr($key,0,3) == 'id_')
			{
				$temp_tablename = substr($key,3);
				//echo "<br>".$temp_tablename."<br>"; 
				$temp_item = ItemFactory::getItem ($value, $temp_tablename);
				//echo "<br>";
				//print_r($temp_item);
				//echo "<br>";
				//$value=;
				$value=$temp_item->name;
			}
			echo "<td>   ".$value."   </td>";
		}
		
		//$currentPage ++;
		echo "</tr>";				
	
		if ($noEntries == $collection->itemsPerPage)
		{
			$currentPage = $currentPage + 1;
			echo "<tr><td><a href = 'script.php?pageNo=$currentPage&modeSort=$sort_mode&valuesFilter=$tip'> >> </a></td></tr>";
			
		}
	}
?> 
</table>
</div>
</body>
</html>
