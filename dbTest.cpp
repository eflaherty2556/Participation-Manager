/*
 * DatabaseAccessor.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: joey
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>

char const *table = "CREATE TABLE IF NOT EXISTS USERS(" 
         "ID INT PRIMARY KEY NOT NULL," 
         "NAME TEXT NOT NULL," 
         "HOURS INT," 
         "ISLOGGEDIN INTEGER );"; //boolean value

int openDatabase(sqlite3 **database)
{
   int databaseConnection = sqlite3_open("test.db", database);

   if (databaseConnection)
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*database));
   else
      fprintf(stderr, "Opened database successfully\n");


   return databaseConnection;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   for (int i = 0; i < argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void createUserTable(sqlite3 *database)
{
   char *errorMessage;  

   int resultCode = sqlite3_exec(database, table, callback, 0, &errorMessage);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "Table created successfully!\n");

}



int main(int argc, char *argv[])
{
   fprintf(stdout, "Opening and creating a table...\n");
   sqlite3 *database;
   openDatabase(&database);
   // int databaseConnection = sqlite3_open("example.db", &database);

   createUserTable(database);

   sqlite3_close(database);
}

