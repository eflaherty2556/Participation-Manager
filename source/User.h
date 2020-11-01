#pragma once
#include <string>

using namespace std;

class User
{
	private:
		int id;
		string name;
		string timeSpent;
		string lastLogTime;
		bool isLoggedIn;
		int privilege;

	public:
		User(int id, string name, string timeSpent, string lastLogTime, bool isLoggedIn, int privilege);

		int getId();
		string getName();
		string getTimeSpent();
		string getLastLogTime();
		bool getIsLoggedIn();
		int getPrivilege();
};