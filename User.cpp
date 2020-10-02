#include "User.h"

User::User(int id, string name, int hours, string lastLogTime, bool isLoggedIn)
{
	this->id = id;
	this->name = name;
	this->hours = hours;
	this->lastLogTime = lastLogTime;
	this->isLoggedIn = isLoggedIn;
}

int User::getId()
{
	return id;
}

string User::getName()
{
	return name;
}

int User::getHours()
{
	return hours;
}

string User::getLastLogTime()
{
	return lastLogTime;
}

bool User::getIsLoggedIn()
{
	return isLoggedIn;
}


int main(int argc, char *argv[])
{
	printf("Testing user class:\n");

	User testUser1(0, "Joey", 5, "2020-10-01 17:25:30.000", false);

	printf("Hello, %s! You are user id number %d.\n", 
		testUser1.getName().c_str(), testUser1.getId());
	printf("You currently have %d hours on record and last logged in/out at %s.\n",
	 testUser1.getHours(), testUser1.getLastLogTime().c_str());
	printf(testUser1.getIsLoggedIn() ? "You are logged in!\n" : "You are not logged in\n");
}
