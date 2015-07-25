<?php
require_once("includes.inc.php");

class CollectionFactory implements ICollectionFactory {
	
	public static function getCollection ($tableName, $equalPairs, $likePairs, $lessThanPairs, $greaterThanPairs, $inPairs, $orderBy = false, $orderType = false, $itemsPerPage = 0, $pageNo = 0)
	{
		try {
			$collection = Collection::gigi($tableName, $equalPairs, $likePairs, $lessThanPairs, $greaterThanPairs, $inPairs, $orderBy, $orderType, $itemsPerPage, $pageNo);
			
			return $collection;
		} catch (Exception $e) {
			throw $e;
		}
		
	}
}
?>