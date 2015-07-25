<?php

require_once("includes.inc.php");

class UpdatePostAction implements IAction {
	
	public $userid;
	public $postid;
	public $posttitle;
	public $postcontent;
	public $rights;
	
	
	public function __construct () {
		
	}
     
	/*
	 * <form action="..." method ='POST'>
		<input type='text' name='post_title' />
		<input type='text' name='post_content' />
		<input type='hidden' name='post_id' value ='...' />
		<input type='submit' value='trimite' />
	   </form>
	 */
   	// actionIsset: verifica urmatoarele:
	// -> utilizatorul logat este autorul post-ului
	// -> parametrii corespunzatori (post_id, post_title, post_content) au fost trimisi prin metoda POST
	public function actionIsset () {		
		
		$this->postid = ($_POST['post_id']);
		$this->posttitle = ($_POST['post_title']);
		$this->postcontent = ($_POST['post_content']);
    	
    	if (!isset($this->postid) || ($this->postid=="") ||
    		!isset($this->posttitle) || ($this->posttitle=="") ||
    		!isset($this->postcontent) || ($this->postcontent ==""))
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
    	if ($tm->isOwner($this->userid, $this->postid) == false)
    		return false;
		return true;
	} 
    
	// execute: daca actionIsset intoarce true, modifica post-ul; 
	// altfel arunca o exceptie de tip ActionNotSetException
	public function execute () {
		if ( $this->actionIsset() == false) 
			throw new ActionNotSetException();
		$db = SingletonDB::connect();
		
		$query = "update posts set titlu='".$this->posttitle."', continut = '".$this->postcontent."' where id='".$this->postid."'";
		$result = $db->query($query);		
		
	}
}
?>
