<?php
require_once("includes.inc.php");

class ItemFactory implements IItemFactory {
	
	public static function getItem ($id, $tableName) {
		try {
			$item = Item::gigi($id, $tableName);
			return $item;
		} catch (Exception $e) {
			throw $e;
		}
	}
}

?>