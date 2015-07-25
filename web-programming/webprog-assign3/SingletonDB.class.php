<?php

require_once("includes.inc.php");

class SingletonDB implements Singleton {

	private static $connection;
	
	private function __construct() 
	{
		 echo 'I am constructed';
	}
	
	public function __clone()
    {
        trigger_error('Clone is not allowed.', E_USER_ERROR);
    }
    
	// The singleton method
	public static function connect () {
		if (!isset(self::$connection)) {
			self::$connection = new mysqli(ADDRESS, USERNAME, PASSWORD, DATABASE);
		}
        return self::$connection;
	}
	
}

?>