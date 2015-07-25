<?php

require_once("includes.inc.php");

class ChangePermissionsAction implements IAction {
	
	
	public $userid;
	public $usertochange;
	public $rights;
	
	public function __construct () {
		
	}
     
   	// actionIsset: verifica urmatoarele:
	// -> utilizatorul logat este administrator
	// -> parametrul trimis prin GET si avand numele id exista, 
	// si contine o valoare valida a unui id de utilizator
	public function actionIsset () {
		
		$this->userid = ($_SESSION[SESSION_NAME]);
		
		if(!isset($this->userid) || 
			($this->userid==""))
			return false;
		
		$tm = new TesterMethods();
    	//id-ul userului logat    	   	
    	if ($tm->isAdmin($this->userid) == false)
    		return false;	
    	
    	
    	$this->usertochange = ($_GET['id']);
    	
    	if(!isset($this->usertochange) || 
			($this->usertochange==""))
			return false;
    	
   		try  {
			$db = SingletonDB::connect();
			$query = "select * from users where id='".$this->usertochange."'";
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

		return true;
	} 
    
	// daca actionIsset intoarce true, 
	// schimba permisiunile utilizatorului; 
	// altfel arunca o exceptie de tip ActionNotSetException	
	public function execute () {	
			
		if ( $this->actionIsset() == false) 
			throw new ActionNotSetException();
		$db = SingletonDB::connect();
		$query = "update users set rights='admin' where id='".$this->usertochange."'";
		$result = $db->query($query);
		
	}
}
?>