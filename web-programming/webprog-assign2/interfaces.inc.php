<?php
	interface ITemplate {
 
		public function __set ($name, $value);
		public function getTagNames();
		public function display ();
		public function render ();
	}
 
	interface ITestMethods {
		public static function getUserList ();
		public static function getPostList ();
		public static function getUsername ($id);
		public static function getPassword ($id);
		public static function isOwner ($postId, $userId);
		public static function isAdmin ($userId);
	}
 
	interface IAuth {
		public function getId ();
		public function isAdmin ();
	}
?>
