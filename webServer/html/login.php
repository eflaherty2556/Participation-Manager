<HTML>
		<!-- ref: https://www.jqueryscript.net/table/Inline-Table-Editing-jQuery-Tabledit.html -->
		<!-- ref: https://phppot.com/jquery/inline-insert-using-jquery-ajax/ -->
        <TITLE>FRC Participation Hours Page</TITLE>
        <head>
                <link rel="stylesheet" href="homepage.css">
                <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
        </head>
        <body class="grayBox">
		<h1>My Hours</h1>

        <?php

        	//log errors
			ini_set('display_errors', '1');
			ini_set('display_startup_errors', '1');
			error_reporting(E_ALL);

			//$file = '/var/www/html/userDatabase.php';
			//include '/var/www/html/userDatabase.php';

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

			if(isset($_POST['login']))
			{
				$id = $_POST['idNumber'];
				#echo "ID: " . $id;

				$db = new userDatabase();
				// $db->verifySuccessfulOpen();

				$user = $db->getUser($id);

				if(!$user)
				{
					echo "User not found!";
					header("Location:login.php");
					exit;
				}

				$row = $user->fetchArray(SQLITE3_ASSOC);

				#give super admins an add student button
				// if($row["PRIVILEGE"] == 2)
				// {
				// 	echo '<br>
				// 			<form action="login.php" method="POST" class="addForm">
				// 				<input type="button" name="update" value="Update" class="add">
				// 				<input type="button" name="addStudent" value="+" class="add">
				// 			</form>
				// 		<br>';
				// }

				echo '<table id="user-table" class="center userTable">
						<thead class="userTable">
							<tr>
								<th class="userTable">Id</th>
								<th class="userTable">Name</th>
								<th class="userTable">Time Spent</th>
								<th class="userTable">Last Log Time</th>
								<th class="userTable">Is Logged In</th>
								<th class="userTable">Privilege Level</th>
							</tr>
						</thead>
						<tbody>';

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
                        echo "<tr><td class='userTable'>" . $row["ID"] . "</td><td class='userTable'>" . $row["NAME"] . "</td><td class='userTable'>" . $row["TIMESPENT"] . "</td><td class='userTable'>" . $row["LASTLOGTIME"] . "</td><td class='userTable'>" . $row["ISLOGGEDIN"] . "</td><td class='userTable'>" . $row["PRIVILEGE"] . "</td></tr>";
                    }
				}

				echo '</tbody></table>';

			}
			// else if(isset($_POST['addStudent']))
			// {
			// 	//check if privilege == 2
			// 	echo "<tr><td contenteditable='true'>" . "newID" . "</td><td contenteditable='true'>" . "newStudent" . "</td><td contenteditable='true'>" . "0:0:0" . "</td><td contenteditable='true'>" . "0000-00-00 00:00:00" . "</td><td contenteditable='true'>" . "0" . "</td><td contenteditable='true'>" . "0" . "</td></tr>";
			// 	//create and call add student method in userdb
			// 	//add button
			// } 


		?>

			<!-- <script src="//code.jquery.com/jquery.min.js"></script>  -->
			<script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
			<!-- <script src="jquery.tabledit.js"></script> -->
			<script src="https://www.jqueryscript.net/demo/Creating-A-Live-Editable-Table-with-jQuery-Tabledit/jquery.tabledit.js"></script>
			<script>
				$('#user-table').Tabledit({
				  url: 'updateDB.php',
				  columns: {
				    identifier: [0, 'Id'],                    
				    editable: [[1, 'Name'], [2, 'Time Spent'], [3, 'Last Log Time'], [4, 'Is Logged In'], [5, 'Privilege Level']]
				  },
			        onSuccess: function(data, textStatus, jqXHR) {
			            // deal with success there
			            console.log("SUCCESS!!!");
			            console.log("data: "+data);
			            console.warn(jqXHR.responseText);
			        },
			        onFail: function(jqXHR, textStatus, errorThrown) {
			            // deal with errors there
			            console.log("FAIL!!!");
			            console.log("jqXHR: " + jqXHR);
			            console.log("textStatus: " + textStatus);
			            console.log("errorThrown: " + errorThrown);
			            console.warn(jqXHR.responseText);
			        },
			        onAjax: function(action, serialize) {
			            // open your xhr here 
			            console.log("on Ajax");
			            console.log("action : ", action);
			            console.log("data : ", serialize);
			        }
				});
			</script>

        </body>
	
</HTML>
