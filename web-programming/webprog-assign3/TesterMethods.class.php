<?php

require_once("includes.inc.php");

class TesterMethods implements ITesterMethods {

	//intoarce un vector ce contine id-urile tuturor utilizatorilor
	public static function getUserList () {
		$index = 0;
		try  {
			$db = SingletonDB::connect();
			$query = "select id from users";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		
		
		while($row = $result->fetch_array())
		{
			$users[$index] = $row[0];
			$index += 1;
		}
		return $users;
	}
	
	//intoarce un vector ce contine id-urile tuturor post-urilor
	public static function getPostList () {
		try  {

			$db = SingletonDB::connect();
			$query = "select id from posts";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}

		while($row = $result->fetch_array())
		{
			$rows[] = $row[0];
		}

		return $rows;
	}
	
	//intoarce un string ce contine username-ului utilizatorului avand id-ul $id
	public static function getUsername ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select username from users where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		return $row[0];
	}
	
	//intoarce un string ce contine parola-ului utilizatorului avand id-ul $id
	public static function getPassword ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select password from users where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		return $row[0];
	}
	
	//daca utilizatorul avand id-ul $id are permisiuni de administrator, intoarce true; altfel intoarce false
	public static function isAdmin ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select rights from users where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		if($row[0] == "admin")
		{
			return true;
		}
		return false;
	}
	
	//daca utilizatorul avand id-ul $id este aprobat, intoarce true; altfel intoarce false
	public static function isApprovedUser ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select state from users where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		if($row[0] == "approved")
			return true;
		return false;
	}
	
	//daca post-ul avand id-ul $id are este aprobat, intoarce true; altfel intoarce false
	public static function isApprovedPost ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select state from posts where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		if($row[0] == "approved")
			return true;
		return false;
	}
	
	//intoarce true, daca utilizatorul avand id-ul $user este autorul post-ului avand id-ul $post; altfel intoarce false
	public static function isOwner($userId, $postId) {
		try  {
			$db = SingletonDB::connect();
			$query = "select id, owner_id from posts where id = '".$postId."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		if ($result->num_rows == 0 ) {
			throw new Exception();
		} else {
			$row = $result->fetch_row();
		}
		if($row[1] == $userId)
		{
			return true;
		}
		return false;
	}
	
	//intoarce id-ul autorului post-ului avand id-ul $id
	public static function getOwner ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select owner_id from posts where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		return $row[0];
	}
	
	//intoarce titlul-ul post-ului avand id-ul $id
	public static function getTitle ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select titlu from posts where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		return $row[0];
	}
	
	//intoarce continutul-ul post-ului avand id-ul $id
	public static function getContent ($id) {
		try  {
			$db = SingletonDB::connect();
			$query = "select continut from posts where id = '".$id."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}
		if ($result == false) {
			throw new Exception();
		}
		$row = $result->fetch_row();
		return $row[0];
	}
	
}