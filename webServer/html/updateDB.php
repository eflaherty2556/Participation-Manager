<?php

//scp joey@joey-Desktop:~/Desktop/COMP462/project/Participation-Manager/webServer/html/\{index.php,login.php,updateDB.php,homepage.css\} ./

//log errors
ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);

header('Content-Type: application/json');

// CHECK REQUEST METHOD
if ($_SERVER['REQUEST_METHOD']=='POST') {
  $input = filter_input_array(INPUT_POST);
} else {
  $input = filter_input_array(INPUT_GET);
}

// Connect to DB

class userDatabase extends SQLite3
{
	function __construct()
	{
		$this->open('/home/pi/Desktop/Project462/source/build/users.db');
    }

	function verifySuccessfulOpen()
	{
    	if(!$this)
    	{
            	echo $this->lastErrorMsg();
    	}
    	else
    	{
            	echo "Database was opened successfully.\n\n";
    	}
	}

	function getAllUsers()
	{
    	$sql = "SELECT * from USERS;";

    	return $this->query($sql);
	}

	function getUser($id)
	{
        $sql = "SELECT * from USERS 
                WHERE ID=" . $id . ";";

        return $this->query($sql);
    }

    function updateUser($id, $name, $time_spent, $last_log_time, $is_logged_in, $privilege_level)
    {
    	$sql = "UPDATE USERS SET 
    			NAME='" . $name . "',
	            TIMESPENT='" . $time_spent . "',
	            LASTLOGTIME='" . $last_log_time . "',
	            ISLOGGEDIN=" . $is_logged_in . ",
	            PRIVILEGE=" . $privilege_level . " 
	            WHERE ID=" . $id . ";";

        return $this->query($sql);
    }

    function removeUser($id)
    {
    	$sql = "DELETE FROM USERS
	            WHERE ID=" . $id . ";";

        return $this->query($sql);
    }
}

$db = new userDatabase();
// $db->verifySuccessfulOpen();

//{"Id":"1","Name":"Jeff","Time_Spent":"00000:00:00","Last_Log_Time":"0000-00-00 00:00:00.000","Is_Logged_In":"0","Privilege_Level":"1","action":"edit"}

// Php question
if ($input['action'] === 'edit') {

	$db->updateUser($input['Id'], $input['Name'], $input['Time_Spent'], $input['Last_Log_Time'], $input['Is_Logged_In'], $input['Privilege_Level']);

} else if ($input['action'] === 'delete') {

	$db->removeUser($input['Id']);

} else if ($input['action'] === 'restore') {

	
}

// Close connection to DB

/*  Your code for close connection to DB*/

// RETURN OUTPUT
echo json_encode($input);

?>