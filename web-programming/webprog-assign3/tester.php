<?php

	include "testerLib.inc.php";
	require_once ("interfaces.inc.php");
	require_once ("Exceptions.class.php");
	
	$test = false;
	$grade = 0;
	if (isset ($_GET['test'])){
		$test = $_GET['test'];
	}
	
	$test_0 = new TestSequence ("Actions: File existance tests");
	$test_0->add( new FileExistanceTest("includes.inc.php file existence ",0,true,"includes.inc.php") );
	$test_0->run();

	
	require_once ("includes.inc.php");
	
	$test_1 = new TestSequence ("Actions: Constants existance tests & database");
	$test_1->add(new ConstantDefinedTest("SESSION_NAME must be defined ",0, false, "SESSION_NAME"));
	$test_1->add(new ConstantDefinedTest("ADDRESS must be defined ",0, false, "ADDRESS"));
	$test_1->add(new ConstantDefinedTest("USERNAME must be defined ",0, false, "USERNAME"));
	$test_1->add(new ConstantDefinedTest("PASSWORD must be defined ",0, false, "PASSWORD"));
	$test_1->add(new ConstantDefinedTest("DATABASE must be defined ",0, false, "DATABASE"));
	
	//a se decomenta, pentru folosirea tabelelor din fisierul "tema3.sql"
	//$test_1->add(new CreateDatabaseTest("Importing database ",0,false,"tema3.sql"));
	$test_1->add(new ClassExistanceTest("TesterMethods.class.php file existance",0,false,"TesterMethods"));
	$test_1->add(new ClassExistanceTest("TesterMethods implements ITesterMethods",0,false,"TesterMethods","ITesterMethods"));
	if (!$test || $test == 'init') {
		$test_1->run();
		$grade += $test_1->getGrade();
	}
	
	/* 2 pct */
	$test_2 = new TestSequence("Login tests");
	$test_2->add(new ClassExistanceTest("LoginAction.class.php file existance",0,false,"LoginAction"));
	$test_2->add(new ClassImplementsInterfaceTest("LoginAction implements IAction",0,false,"LoginAction","IAction"));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetFalse00Test ("Login with no form sent", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetFalse01Test ("Login with empty form", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetFalse02Test ("Login with bad password but good username", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetFalse01Test ("Login with bad username but some valid password from table", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetFalse1Test ("Login with bad credentials test", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetTrueTest ("Login with good credentials test 1", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetTrueTest ("Login with good credentials test 2", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionIssetTrueTest ("Login with good credentials test 3", 2, false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionExecute1Test ("Execute with actionIsset returning false (should throw exception)",2,false)));
	$test_2->add(new NoExceptionDecorator( new LoginActionExecute2Test ("Execute with actionIsset returning true (should set a correct session)",2,false)));
		
	if (!$test || $test == 'login') {
		$test_2->run();
		$grade += $test_2->getGrade();
	}
	
	/* 1 pct */
	$test_3 = new TestSequence("Approve user tests");
	$test_3->add(new NoExceptionDecorator(new ClassExistanceTest("ApproveUserAction.class.php file existance",0,true,"ApproveUserAction")));
	$test_3->add(new NoExceptionDecorator(new ClassImplementsInterfaceTest("ApproveUserAction implements IAction",0,true,"ApproveUserAction","IAction")));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetFalse01Test("ApproveUser not logged, but with correct id value",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetFalse02Test("ApproveUser logged, but not admin (and with correct id value)",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetFalse11Test("ApproveUser not logged, and with incorrect id value",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetFalse12Test("ApproveUser logged, but not admin (and with incorrect id value)",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetFalse13Test("ApproveUser logged as admin but no id value is sent",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetFalse14Test("ApproveUser logged as admin but sent id value is incorrect",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetTrueTest("ApproveUser logged as admin with correct id value 1",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionIssetTrueTest("ApproveUser logged as admin with correct id value 2",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionExecute1Test("Execute with actionIsset returning false (should throw exception)",1,false)));
	$test_3->add(new NoExceptionDecorator(new ApproveUserActionExecute2Test("Execute with actionIsset returning true (should update apropriate table)",1,false)));
	
	if (!$test || $test == 'approveUser') {
		$test_3->run();
		$grade += $test_3->getGrade();
	}
	
	/* 1 pct */
	$test_4 = new TestSequence("Approve post tests");
	
	$test_4->add(new NoExceptionDecorator(new ClassExistanceTest("ApprovePostAction.class.php file existance",0,true,"ApprovePostAction")));
	$test_4->add(new NoExceptionDecorator(new ClassImplementsInterfaceTest("ApprovePostAction implements IAction",0,true,"ApprovePostAction","IAction")));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetFalse01Test("ApprovePost not logged, but with correct id value",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetFalse02Test("ApprovePost logged, but not as admin (and with correct id value)",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetFalse11Test("ApprovePost not logged, and with incorrect id value",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetFalse12Test("ApprovePost logged, but not admin (and with incorrect id value)",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetFalse13Test("ApprovePost logged as admin but no id value is sent",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetFalse14Test("ApprovePost logged as admin but sent id value is incorrect",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetTrueTest("ApprovePost logged as admin with correct id value 1",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionIssetTrueTest("ApprovePost logged as admin with correct id value 2",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionExecute1Test("Execute with actionIsset returning false (should throw exception)",1,false)));
	$test_4->add(new NoExceptionDecorator(new ApprovePostActionExecute2Test("Execute with actionIsset returning true (should update apropriate table)",1,false)));
	
	if (!$test || $test == 'approvePost') {
		$test_4->run();
		$grade += $test_4->getGrade();
	}

	/* 1.5 pct */
	$test_5 = new TestSequence("Change permissions");
	
	$test_5->add(new NoExceptionDecorator(new ClassExistanceTest("ChangePermissionsAction.class.php file existance",0,true,"ChangePermissionsAction")));
	$test_5->add(new NoExceptionDecorator(new ClassImplementsInterfaceTest("ChangePermissionsAction implements IAction",0,true,"ChangePermissionsAction","IAction")));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetFalse01Test("ChangePermissions not logged, but with correct id value",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetFalse02Test("ChangePermissions logged, but not admin (and with correct id value)",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetFalse11Test("ChangePermissions not logged, and with incorrect id value",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetFalse12Test("ChangePermissions logged, but not admin (and with incorrect id value)",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetFalse13Test("ChangePermissions logged as admin but no id value is sent",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetFalse14Test("ChangePermissions logged as admin but sent id value is incorrect",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetTrueTest("ChangePermissions logged as admin with correct id value 1",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionIssetTrueTest("ChangePermissions logged as admin with correct id value 2",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionExecute1Test("Execute with actionIsset returning false (should throw exception)",1.5,false)));
	$test_5->add(new NoExceptionDecorator(new ChangePermissionsActionExecute2Test("Execute with actionIsset returning true (should update apropriate table)",1.5,false)));
	
	if (!$test || $test == 'changePermissions') {
		$test_5->run();
		$grade += $test_5->getGrade();
	}
	/* 2 pct */
	$test_6 = new TestSequence("Display Post");
	
	$test_6->add(new NoExceptionDecorator(new ClassExistanceTest("DisplayPostAction.class.php file existance",0,true,"DisplayPostAction")));
	$test_6->add(new NoExceptionDecorator(new ClassImplementsInterfaceTest("DisplayPostAction implements IAction",0,true,"DisplayPostAction","IAction")));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionIssetFalse01Test("DisplayPost as guest, and invalid id",2,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionIssetFalse02Test("Display un-approved post as guest",2,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionIssetFalse03Test("Display un-approved post as logged user, but not owner of post",2,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionIssetTrue01Test("Display un-approved post as owner",3,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionIssetTrue02Test("Display un-approved post as admin",3,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionExecute01Test("Display approved post as guest",2,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionExecute02Test("Display approved post as logged user",2,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionExecute03Test("Display approved post as admin",2,false)));
	$test_6->add(new NoExceptionDecorator(new DisplayPostActionExecute04Test("Execute with actionIsset returning false (should throw exception)",2,false)));
	
	//$test_6->debuggingOn();
	
	if (!$test || $test == 'displayPost') {
		$test_6->run();
		$grade += $test_6->getGrade();
	}
	
	/* 1.5 pct */
	$test_7 = new TestSequence("Update Post");
	
	$test_7->add(new NoExceptionDecorator(new ClassExistanceTest("UpdatePostAction.class.php file existance",0,true,"UpdatePostAction")));
	$test_7->add(new NoExceptionDecorator(new ClassImplementsInterfaceTest("UpdatePostAction implements IAction",0,true,"UpdatePostAction","IAction")));
	$test_7->add(new NoExceptionDecorator(new UpdatePostActionIssetFalse01Test("UpdatePost as guest ",2,false)));
	$test_7->add(new NoExceptionDecorator(new UpdatePostActionIssetFalse02Test("UpdatePost as logged user, but not owner ",2,false)));
	$test_7->add(new NoExceptionDecorator(new UpdatePostActionIssetFalse03Test("UpdatePost as logged user, owner, but field post_id was not sent ",2,false)));
	$test_7->add(new NoExceptionDecorator(new UpdatePostActionIssetFalse04Test("UpdatePost as logged user, owner, but field post_title was not sent ",2,false)));
	$test_7->add(new NoExceptionDecorator(new UpdatePostActionIssetFalse05Test("UpdatePost as logged user, owner, but field post_content was not sent ",2,false)));
	$test_7->add(new NoExceptionDecorator(new UpdatePostActionIssetTrueTest("UpdatePost as owner, and all proper fields sent",1,false)));
	$test_7->add(new NoExceptionDecorator(new UpdatePostExecute1Test("Update a post",2,false)));
	$test_7->add(new NoExceptionDecorator(new UpdatePostExecute2Test("Trying to update a post with actionIsset returning false (should throw exception)",2,false)));
	
	//
	
	if (!$test || $test == 'updatePost') {
		$test_7->run();
		$grade += $test_7->getGrade();
	}
	
	space();
	space();
	displayGrade($grade);
	
	
	//A NU SE DE-COMENTA; va produce stergerea bazei de date
	//clearDatabase();
?>