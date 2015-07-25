<?php

require_once("includes.inc.php");

class ApproveUserAction implements IAction {
	
	public $myusername;
	public $mypassword;
	public $myid;
	public $loggedid;
	
	//forteaza existenta unui constructor fara parametri; 
	// util pentru testare, in absenta unei metode Factory
    public function __construct () {
    	
    }
     
    //verifica urmatoarele
	// -> utilizatorul logat are dreptul de a aproba alti utilizatori (este administrator)
	// -> parametrul trimis prin GET si avand numele id exista, si contine o valoare 
	// valida a unui utilizator
	public function actionIsset () {
		
		$this->loggedid = ($_SESSION[SESSION_NAME]);
		
		if(!isset($this->loggedid) || 
			($this->loggedid==""))
			return false;
		
		$tm = new TesterMethods();
    	//id-ul userului logat    	   	
    	if ($tm->isAdmin($this->loggedid) == false)
    		return false;	
		
		$this->myid = stripslashes($_GET['id']);
		//echo "<br> id = $this->myid";
		
		try  {
			$db = SingletonDB::connect();
			$query = "select username from users where id='".$this->myid."'";
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
			$this->myusername = $row[0];
		}
		
		if (is_string($this->myusername) == false)
		{
			return false;
		}
		
		if ($count == 0)
			return false;
			
		return true;
	} 
    
	// daca actionIsset intoarce true modifica un camp corespunzator 
	// in baza de date, care reflecta faptul ca un utilizator a fost aprobat; 
	// altfel arunca o exceptie de tip ActionNotSetException	
	public function execute () {
		
		if ( $this->actionIsset() == false) 
			throw new ActionNotSetException();
		$db = SingletonDB::connect();
		$query = "update users set state='approved' where id='".$this->myid."'";
		$result = $db->query($query);
		
	}
}
?>