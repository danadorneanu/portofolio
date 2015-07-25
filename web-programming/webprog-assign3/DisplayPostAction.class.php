<?php

require_once("includes.inc.php");

class DisplayPostAction implements IAction {
	
	public $userid;
	public $postid;
	public $rights;
	
	
	public function __construct () {
		
	}
     
   	// actionIsset: verifica urmatoarele:
	// -> parametrul trimis prin GET si avand numele id exista, 
	// si contine o valoare valida a unui id de post
	// daca post-ul vizualizat este aprobat sau nu; un post ne-aprobat poate fi vazut doar de:
	// autorul sau, un administrator;	
	public function actionIsset () {    	
    	
    	$this->postid = ($_GET['id']);
    	
    	if(!isset($this->postid) || 
			($this->postid==""))
			return false;
    	
   		try  {
			$db = SingletonDB::connect();
			$query = "select * from posts where id='".$this->postid."'";
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
			$count++;			
		}

		//nu exista id-ul POSTULUI primit prin get
		if ($count == 0)
			return false;
			
		$this->userid = ($_SESSION[SESSION_NAME]);
		
		if(!isset($this->userid) || 
			($this->userid==""))
			return false;
		
		$tm = new TesterMethods();
    	//id-ul userului logat    	   	
    	if ($tm->isAdmin($this->userid) == false && $tm->isOwner($this->userid, $this->postid) == false)
    		return false;	

		return true;
	} 
    
	// execute: daca actionIsset intoarce true, afiseaza post-ul; 
	// altfel arunca o exceptie de tip ActionNotSetException
	public function execute () {
		if ( $this->actionIsset() == false) 
			throw new ActionNotSetException();
		$db = SingletonDB::connect();
		$query = "select continut from posts where id='".$this->postid."'";
		$result = $db->query($query);
		
		$row = $result->fetch_row();
		echo $row[0];
	}
}
?>