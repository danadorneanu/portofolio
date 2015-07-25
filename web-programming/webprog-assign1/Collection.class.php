<?php

require_once("includes.inc.php");

class Collection implements ICollection {
	
	public $tableName;
	public $equalPairs;
	public $likePairs;
	public $lessThanPairs;
	public $greaterThanPairs;
	public $inPairs;
	public $orderBy;
	public $orderType;
	public $itemsPerPage;
	public $pageNo;
	
	public $result;
	public $row;
	public $is_next;
	public $set_and =false;

	public static function gigi($tableName, $equalPairs, $likePairs, $lessThanPairs, $greaterThanPairs, $inPairs, $orderBy, $orderType, $itemsPerPage, $pageNo)
	{
		try {
			return new Collection($tableName, $equalPairs, $likePairs, $lessThanPairs, $greaterThanPairs, $inPairs, $orderBy, $orderType, $itemsPerPage, $pageNo);
			
		} catch (Exception $e) {
			throw $e;
		}
	}
	
	public function __construct($tableName, $equalPairs, $likePairs, $lessThanPairs, $greaterThanPairs, $inPairs, $orderBy, $orderType, $itemsPerPage, $pageNo)
	{
		if (!$pageNo)
			$this->pageNo = 1;
		else
			$this->pageNo = $pageNo;
		
		$this->tableName = $tableName;
		$this->equalPairs = $equalPairs;
		$this->likePairs = $likePairs;
		$this->lessThanPairs = $lessThanPairs;
		$this->greaterThanPairs = $greaterThanPairs;
		$this->inPairs = $inPairs;
		$this->orderBy = $orderBy;
		$this->orderType = $orderType;
		$this->itemsPerPage = $itemsPerPage;
		
		
		$this->refresh();
		$this->is_next = true;
	}
	
	public function refresh ()
	{
		$query = "SELECT * from ".$this->tableName;
		
		if (!empty($this->equalPairs) || !empty($this->likePairs) ||
		!empty($this->lessThanPairs) || !empty($this->greaterThanPairs) ||
		!empty($this->inPairs)) 
		{
			//echo "add where statement <br>";
			$query .= " WHERE ";
		}
		
	
		if (!empty($this->equalPairs))
		{
			foreach ($this->equalPairs as $key => $value)
				$query .= " $key = '".$value."' AND";
            $query = substr ($query,0,-3);
            $this->set_and = true;
		}
		
		if (!empty($this->likePairs))
		{
			if ($this->set_and == true)
				$query .= " AND ";
				
			foreach ($this->likePairs as $key => $value)
				$query .= " $key LIKE '".$value."' AND";
            $query = substr ($query,0,-3);
            $this->set_and = true;
		}
		
		if (!empty($this->lessThanPairs))
		{
			if ($this->set_and == true)
				$query .= " AND ";
				
			foreach ($this->lessThanPairs as $key => $value)
				$query .= " $key < '".$value."' AND";
            $query = substr ($query,0,-3);
            $this->set_and = true;
		}
		
		if (!empty($this->greaterThanPairs))
		{
			if ($this->set_and == true)
				$query .= " AND ";
				
			foreach ($this->greaterThanPairs as $key => $value)
				$query .= " $key > '".$value."' AND";
            $query = substr ($query,0,-3);
            $this->set_and = true;
		}
		
		if (!empty($this->inPairs))
		{
			if ($this->set_and == true)
				$query .= " AND ";
				
			foreach ($this->inPairs as $key => $values) 
			{
				
				$query .= " $key IN ( ";
				
				foreach ( $values as $value )
				{
					$query .= "'".$value."',";
				}
				
				$query = substr ($query,0,-1);
				$query .= " ) AND";
			}
			
			$query = substr ($query,0,-3);
		}
		
		$this->set_and = false;
		
		if ($this->orderBy)
		{
			$query .= " ORDER BY $this->orderBy ";
			
			if ($this->orderType != 'ASC' && $this->orderType != 'DESC')
			{
				throw new MySQLException();
				return;
			}
			else  
			{
				$query .= $this->orderType;
			}
		} 
		 
		if ($this->itemsPerPage != 0)
		{
			$startIndex = ($this->pageNo-1)*$this->itemsPerPage;

			if ($this->pageNo > 0)
				$query .= " LIMIT $startIndex, ".$this->itemsPerPage;
		}
			

		$db = SingletonDB::connect();
		$this->result = $db->query($query);
		
		if ($this->result == false )
		{
			throw new MySQLException();
			return;
		}
		
	}
	
	
	public function getNumberOfPages () {
		return $this->pageNo;
		
	}
	
	public function hasNext () {
		
		$this->row = $this->result->fetch_assoc();
		
		if ($this->row) {
			$this->is_next = true;
			return true;
		}
		
		$this->is_next = false;
		return false;
		
	}
	
	public function next () {
		
		if ($this->is_next == true) {
			$item = ItemFactory::getItem($this->row['id'], $this->tableName);
			return $item;
		}
		else return array();
		
	}
}
?>
