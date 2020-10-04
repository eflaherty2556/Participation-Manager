#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>
#include <vector>

#include "User.h"

using namespace std;

class DatabaseAccessor 
{
   private:
      inline static sqlite3 *database;
      inline static vector<User *> *resultsBuffer = new vector<User *>;

   public:
      static int openDatabase();
      static int printCallback(void *NotUsed, int argc, char **argv, char **azColName);
      static int getCallback(void *NotUsed, int argc, char **argv, char **azColName);
      static void createUserTable();
      static void insertNewRecord(int id, string name, string timeSpent, string lastLogTime, int isLoggedIn, int privilege);
      static void printAllRecords();
      static vector<User *> *getUser(int id);
      static vector<User *> *getAllUsers();
      static void updateRecord(int id, string timeSpent, string lastLogTime, int isLoggedIn, int privilege);
      static void deleteRecord(int id);
};
