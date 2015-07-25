<?php
require_once("includes.inc.php");

class TestMethods implements ITestMethods {

	public function __construct () {
	}

	public static function getUserList () {
		
		$index = 0;

		try  {

			$db = SingletonDB::connect();
			$query = "select id from pw_users";
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
		
		print_r($users);
		return $users;
	}

	public static function getPostList () {

		try  {

			$db = SingletonDB::connect();
			$query = "select id from pw_posts";
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
	
	public static function getPostContent ($id) {

		try  {

			$db = SingletonDB::connect();
			$query = "select value from pw_posts where id = '".$id."'";
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

	public static function getUsername ($id) {

		try  {

			$db = SingletonDB::connect();
			$query = "select username from pw_users where id = '".$id."'";
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

	public static function getPassword ($id) {
		try  {

			$db = SingletonDB::connect();
			$query = "select password from pw_users where id = '".$id."'";
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

	public static function isOwner ($postId, $userId) {

		try  {

			$db = SingletonDB::connect();
			$query = "select id,id_user from pw_posts where id= '".$postId."'";
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

	public static function isAdmin ($userId) {

		try  {

			$db = SingletonDB::connect();
			$query = "select statut from pw_users where id = '".$userId."'";
			$result = $db->query($query);
		}
		catch (Exception $e) {
			echo " exceptia sql este  ".$e->getMessage();
		}

		if ($result == false) {
			throw new Exception();
		}

		$row = $result->fetch_row();
		
		if ($row[0] == "admin") {
			return true;
		}
	
		return false;

	}

}
/*
$test = new TestMethods();

$list_users = $test->getUserList();
echo "<br> user list id <br>";
print_r($list_users);

$list_post = $test->getPostList();
echo "<br> post list id <br>";
print_r($list_post);

$user_name = $test->getUsername(3);
$pass = $test->getPassword(3);

echo "<br> $user_name, $pass <br>";

print_r($test->isOwner(11, 4));
echo "<br>";
print_r($test->isOwner(11, 3));
echo "<br>";
print_r($test->isAdmin(3));
echo "<br>";
print_r($test->isAdmin(1));
*/
?>