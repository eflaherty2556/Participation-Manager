<?php
	class userDatabase extends SQLite3
	{
		function __construct()
		{
			$this->open('~/Desktop/462Project/source/users.db');
		}

		function verifySuccessfulOpen()
		{
			if(!$this)
			{
				echo $this->lastErrorMsg();
			}
			else
			{
				echo "Database was opened successfully.\n";
			}
		}

		function getAllUsers()
		{
			$sql = "SELECT * from USERS;";

			return $this->query($sql);
		}

		function getUser(int id)
		{
			$sql = "SELECT * from USERS 
				WHERE ID=" . id . ";";

			return $this->query($sql);
		}

	}

