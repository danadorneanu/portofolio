<?php
require_once("includes.inc.php");

class Item implements IItem {
	
	public $propr;
	public $tablename;
	public $id;
	
	public static function gigi($idx, $tablename) {
		try {
			return new Item($idx, $tablename);
		} catch (Exception $e) {
			throw $e;
		}
	}
	
	public function __construct($id, $tablename) {
		
		$db = SingletonDB::connect();
		$query = "SHOW TABLES LIKE '".$tablename."'";
		$result = $db->query($query);
		
		if ($result->num_rows == 0 || $result == false || $tablename == '') {
			throw new InvalidTableException();
		}

		$this->id = $id;
		$this->tablename = $tablename;
		
		if ($this->id == false)
		{
		} else {
			try  {
				$query = "select * from ".$tablename." where id = '".$this->id."'";		
				$result = $db->query($query);
			} catch (Exception $e) {
				echo " exceptia sql este  ".$e->getMessage();
			}
			
			if ($result == false) {
				throw new MySQLException();
			}
			
			if ($result->num_rows == 0 ) {
				throw new InvalidIndexException();
			} else {
				$this->propr = $result->fetch_assoc();
			} 
		}
		
	}
	
	public function getProp() {
		return $this->propr;
	}
	
	public function getId () {
		return $this->id;
	}
	
	public function __get ($property) {
		
		if (!array_key_exists($property, $this->propr))
		{
			throw new NoSuchPropertyException();
		}
		else 		
			return $this->propr[$property];
	}
	
	public function __set ($property, $value) {

		if (!array_key_exists($property, $this->propr))
		{
			throw new NoSuchPropertyException();
		}
		else {
			$this->propr[$property]=$value;
			
			$db = SingletonDB::connect();
			$query = "update ".$this->tablename." set ".$property."='".$value."' where id=".$this->id." ";
			$res = $db->query($query);
		
	
			if ($res == false) {
				throw new MySQLException();
			}
		}
		
	}
	
	public function populate ($keyValueSet) {
		
	
		$values = "";
		$columns = "";
		foreach ( $keyValueSet as $key => $value)
		{ 
			
			$values .=  ", '".$value."'";
			$columns .=  ", ".$key;
		}
		
		$this->propr = $keyValueSet;

		$values = substr ($values, 1);
		$columns = substr ($columns, 1);
		
		$db = SingletonDB::connect();
		
		$query = "insert into ".$this->tablename." (".$columns.") values(".$values.")";
		$res = $db->query($query);
		
		$query = "select id from ".$this->tablename." order by id desc limit 1";
		$res = $db->query($query);
		$obj = $res->fetch_object();
		$this->id = $obj->id;
	
		if ($res == false) {
			throw new MySQLException();
		}
	}
	
}

//$c = new Item("12", "pw_users");
//Item::gigi();
?>