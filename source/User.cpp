#include "User.h"

User::User(int id, string name, string timeSpent, string lastLogTime, bool isLoggedIn, int privilege)
{
	this->id = id;
	this->name = name;
	this->timeSpent = timeSpent;
	this->lastLogTime = lastLogTime;
	this->isLoggedIn = isLoggedIn;
	this->privilege = privilege;
}

int User::getId()
{
	return this->id;
}

string User::getName()
{
	return  this->name;
}

string User::getTimeSpent()
{
	return  this->timeSpent;
}

string User::getLastLogTime()
{
	return  this->lastLogTime;
}

bool User::getIsLoggedIn()
{
	return  this->isLoggedIn;
}

int User::getPrivilege()
{
	return this->privilege;
}


//testing
// int main(int argc, char *argv[])
// {
// 	printf("Testing user class:\n");

// 	User testUser1(0, "Joey", 5, "2020-10-01 17:25:30.000", false);

// 	printf("Hello, %s! You are user id number %d.\n", 
// 		testUser1.getName().c_str(), testUser1.getId());
// 	printf("You currently have %d hours on record and last logged in/out at %s.\n",
// 	 testUser1.getHours(), testUser1.getLastLogTime().c_str());
// 	printf(testUser1.getIsLoggedIn() ? "You are logged in!\n" : "You are not logged in\n");
// }
