<HTML>
        <TITLE>FRC Participation Hours Page</TITLE>
        <head>
                <link rel="stylesheet" href="homepage.css">
        </head>
        <body>
		<h1>My Hours</h1>

		<table>
			<tr>
				<th>Id</th>
				<th>Name</th>
				<th>Time Spent</th>
				<th>Last Log Time</th>
				<th>Is Logged In</th>
				<th>Privilege Level</th>
			</tr>
                	<?php

				//echo "0\n";
				ini_set('display_errors', '1');
				ini_set('display_startup_errors', '1');
				error_reporting(E_ALL);


				//echo "1\n";
				//$file = '/var/www/html/userDatabase.php';
				//include '/var/www/html/userDatabase.php';
				//echo "2\n";

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


			        }

				//if($_SERVER["REQUEST_METHOD"] == "POST")
				if(isset($_POST['login']))
				{
					$id = $_POST['idNumber'];
					#$password = $_POST['password'];

					#echo "ID: " . $id;
					#echo "Password: " . $password;

					$db = new userDatabase();
					$db->verifySuccessfulOpen();

					$user = $db->getUser($id);

					if(!$user)
					{
						echo "User not found!";
						header("Location:login.php");
						exit;
					}

					$row = $user->fetchArray(SQLITE3_ASSOC);

					if($row["PRIVILEGE"] == 0)
					{
						#regular user, only need their info
                                                echo "<tr><td>" . $row["ID"] . "</td><td>" . $row["NAME"] . "</td><td>" . $row["TIMESPENT"] . "</td><td>" . $row["LASTLOGTIME"] . "</td><td>" . $row["ISLOGGEDIN"] . "</td><td>" . $row["PRIVILEGE"] . "</td></tr>";
					}
					else
					{
						#privileged user, get all info
						$users = $db->getAllUsers();

                                                while($row = $users->fetchArray(SQLITE3_ASSOC))
                                                {
                                                        echo "<tr><td contenteditable='true'>" . $row["ID"] . "</td><td contenteditable='true'>" . $row["NAME"] . "</td><td contenteditable='true'>" . $row["TIMESPENT"] . "</td><td contenteditable='true'>" . $row["LASTLOGTIME"] . "</td><td contenteditable='true'>" . $row["ISLOGGEDIN"] . "</td><td contenteditable='true'>" . $row["PRIVILEGE"] . "</td></tr>";
                                                }

					}

				}
				else if(isset($_POST['addStudent']))
				{
					//check if privilege == 2
					echo "<tr><td contenteditable='true'>" . "newID" . "</td><td contenteditable='true'>" . "newStudent" . "</td><td contenteditable='true'>" . "0:0:0" . "</td><td contenteditable='true'>" . "0000-00-00 00:00:00" . "</td><td contenteditable='true'>" . "0" . "</td><td contenteditable='true'>" . "0" . "</td></tr>";
					//create and call add student method in userdb
					//add button
				} 




				#$users = $db->getAllUsers();

				#while($row = $users->fetchArray(SQLITE3_ASSOC))
				#{
				#	echo "<tr><td>" . $row["ID"] . "</td><td>" . $row["NAME"] . "</td><td>" . $row["TIMESPENT"] . "</td><td>" . $row["LASTLOGTIME"] . "</td><td>" . $row["ISLOGGEDIN"] . "</td><td>" . $row["PRIVILEGE"] . "</td></tr>";
				#}

				// date_default_timezone_set("America/Los_Angeles");
        			// echo "The current time in LA is " . date("h:i:sa");

			?>
			</table>

        </body>
</HTML>

