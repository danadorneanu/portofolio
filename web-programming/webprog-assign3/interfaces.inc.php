<?php
interface IAction {
     public function __construct (); //forteaza existenta unui constructor fara parametri; util pentru testare, in absenta unei metode Factory
     public function actionIsset ();
     public function execute ();
}

interface ITesterMethods {
		public static function getUserList (); //intoarce un vector ce contine id-urile tuturor utilizatorilor
		public static function getPostList (); //intoarce un vector ce contine id-urile tuturor post-urilor
		public static function getUsername ($id); //intoarce un string ce contine username-ului utilizatorului avand id-ul $id
		public static function getPassword ($id); //intoarce un string ce contine parola-ului utilizatorului avand id-ul $id
		public static function isAdmin ($id); //daca utilizatorul avand id-ul $id are permisiuni de administrator, intoarce true; altfel intoarce false
		public static function isApprovedUser ($id); //daca utilizatorul avand id-ul $id este aprobat, intoarce true; altfel intoarce false
		public static function isApprovedPost ($id); //daca post-ul avand id-ul $id are este aprobat, intoarce true; altfel intoarce false
		public static function isOwner($user,$post); //intoarce true, daca utilizatorul avand id-ul $user este autorul post-ului avand id-ul $post; altfel intoarce false
		public static function getOwner ($post); //intoarce id-ul autorului post-ului avand id-ul $post
		public static function getTitle ($post); //intoarce titlul-ul post-ului avand id-ul $post
		public static function getContent ($post); //intoarce continutul-ul post-ului avand id-ul $post
}
?>