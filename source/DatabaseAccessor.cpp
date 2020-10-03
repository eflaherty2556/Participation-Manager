/*
 * DatabaseAccessor.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: joey
 */
//g++ DatabaseAccessor.cpp User.cpp -lsqlite3 -o dbTest.out -std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0 -g3

#include "DatabaseAccessor.h"

int DatabaseAccessor::openDatabase()
{
   int databaseConnection = sqlite3_open("users.db", &database);

   if (databaseConnection)
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(database));
   else
      fprintf(stderr, "Opened database successfully\n");


   return databaseConnection;
}

//used to print database
int DatabaseAccessor::printCallback(void *NotUsed, int argc, char **argv, char **azColName)
{
   printf("Users:\n");
   for (int i = 0; i < argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

//used to get elements from the database
int DatabaseAccessor::getCallback(void *NotUsed, int argc, char **argv, char **azColName)
{
   const int elementsPerUser = 5;

   for(int i = 0; i < argc; i+=elementsPerUser)
   {
      User *foundUser = new User(atoi(argv[i]), argv[i+1], atoi(argv[i+2]), argv[i+3], atoi(argv[i+4]));
      resultsBuffer->push_back(foundUser);
   }
   
   return 0;
}

void DatabaseAccessor::createUserTable()
{
   openDatabase();

   char *errorMessage;  
   char const *table = "CREATE TABLE IF NOT EXISTS USERS(" 
         "ID INT PRIMARY KEY NOT NULL," 
         "NAME TEXT NOT NULL," 
         "HOURS INT,"
         "LASTLOGTIME TEXT," //ISO8601 format (YYYY-MM-DD HH:MM:SS.SSS)
         "ISLOGGEDIN INTEGER );"; //boolean value

   int resultCode = sqlite3_exec(database, table, NULL, 0, &errorMessage);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error in createUserTable: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "Table created successfully!\n");

   sqlite3_close(database);
}

void DatabaseAccessor::insertNewRecord(int id, string name, int hours, string lastLogTime, int isLoggedIn)
{
   openDatabase();

   char *errorMessage; 
   char *record = (char *)malloc(sizeof(char) * 128);
   const char *baseCommand = "INSERT INTO USERS (ID,NAME,HOURS,LASTLOGTIME,ISLOGGEDIN) VALUES (%d, '%s', %d, '%s', %d ); ";

   sprintf(record, baseCommand, 
      id, name.c_str(), hours, lastLogTime.c_str(), isLoggedIn);

   int resultCode = sqlite3_exec(database, record, NULL, 0, &errorMessage);
   free(record);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error in insertNewRecord: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "Record inserted successfully!\n");

   sqlite3_close(database);
}

void DatabaseAccessor::printAllRecords()
{
   openDatabase();

   char *errorMessage;  
   char const *command = "SELECT * from USERS";

   int resultCode = sqlite3_exec(database, command, printCallback, 0, &errorMessage);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error in printAllRecords: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "Table printed successfully!\n");

   sqlite3_close(database);
}

vector<User *> *DatabaseAccessor::getUser(int id)
{
   openDatabase();

   resultsBuffer->clear(); //remove elements from last use

   char *errorMessage;
   char *record = (char *)malloc(sizeof(char) * 128);  
   char const *baseCommand = "SELECT * from USERS "
                           "WHERE ID = %d;";

   sprintf(record, baseCommand, id);

   int resultCode = sqlite3_exec(database, record, getCallback, 0, &errorMessage);
   free(record);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error in getUser: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "User got successfully!\n");

   sqlite3_close(database);

   vector<User *> *results = resultsBuffer; //assignment of vectors copies the vector
   return results;
}

vector<User *> *DatabaseAccessor::getAllUsers()
{
   openDatabase();

   resultsBuffer->clear(); //remove elements from last use


   char *errorMessage; 
   char const *command = "SELECT * from USERS";

   int resultCode = sqlite3_exec(database, command, getCallback, 0, &errorMessage);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error in getUser: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "User got successfully!\n");

   sqlite3_close(database);

   vector<User *> *results = resultsBuffer; //assignment of vectors copies the vector
   return results;
}

void DatabaseAccessor::updateRecord(int id, int hours, string lastLogTime, int isLoggedIn)
{
   openDatabase();

   char *errorMessage; 
   char *record = (char *)malloc(sizeof(char) * 128);
   const char *baseCommand = "UPDATE USERS SET " 
                              "HOURS=%d," 
                              "LASTLOGTIME='%s'," 
                              "ISLOGGEDIN=%d " 
                              "WHERE ID = %d";
                              

   sprintf(record, baseCommand, 
      hours, lastLogTime.c_str(), isLoggedIn, id);

   int resultCode = sqlite3_exec(database, record, NULL, 0, &errorMessage);
   free(record);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error in updateRecord: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "Record updated successfully!\n");

   sqlite3_close(database);
}

void DatabaseAccessor::deleteRecord(int id)
{
   openDatabase();

   char *errorMessage; 
   char *record = (char *)malloc(sizeof(char) * 128);
   const char *baseCommand = "DELETE from USERS " 
                              "WHERE ID = %d";

   sprintf(record, baseCommand, id);

   int resultCode = sqlite3_exec(database, record, NULL, 0, &errorMessage);
   free(record);

   if(resultCode != SQLITE_OK)
   {
      fprintf(stderr, "SQL error in deleteRecord: %s\nResult code: %d\n", errorMessage, resultCode);
      free(errorMessage);
   }
   else
      fprintf(stdout, "Record updated successfully!\n");

   sqlite3_close(database);
}    


int main(int argc, char *argv[])
{
   fprintf(stdout, "Opening and creating a table...\n");

   DatabaseAccessor::createUserTable();
   DatabaseAccessor::insertNewRecord(0, "Joey", 0, "0000-00-00 00:00:00.000", 0);
   DatabaseAccessor::printAllRecords();
   DatabaseAccessor::updateRecord(0, 3, "2020-09-30 15:53:30.000", 1);
   DatabaseAccessor::printAllRecords();
   DatabaseAccessor::insertNewRecord(1, "Jeff", 4, "1234-56-78 12:34:56.789", 0);
   DatabaseAccessor::printAllRecords();
   // DatabaseAccessor::deleteRecord(0);
   // DatabaseAccessor::printAllRecords();

   printf("\nget 1 user:\n");

   vector<User *> *requestResults = DatabaseAccessor::getUser(0);
   User *myUser = requestResults->front();
   string name = myUser->getName();
   printf("!Name: %s\n", name.c_str());

   printf("\nget all users:\n");

   requestResults = DatabaseAccessor::getAllUsers();
   for(int i = 0; i < requestResults->size(); i++)
   {
      User *theUser = requestResults->at(i);
      printf("!Name: %s\n", (theUser->getName()).c_str());
   }

   delete myUser;
}