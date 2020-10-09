#include "request.h"

using namespace std;

class GetUserRequest: public Request
{
	private:
		enum RequestType type = UpdateUser;

		int newId;
		string newTimeSpent; 
		string newLastLogTime;
		int newIsLoggedIn; 
		int newPrivilege;
	public:
		GetAllUsersRequest(int newId, string newTimeSpent, string newLastLogTime, int newIsLoggedIn, int newPrivilege)
		{
			this->newId = newId;
			this->newTimeSpent = newTimeSpent;
			this->newLastLogTime = newLastLogTime;
			this->newIsLoggedIn = newIsLoggedIn;
			this->newPrivilege = newPrivilege;
		}

		//enum Request::RequestType Request::getType(){}
		enum RequestType getType()
		{
			return type;
		}

		int getNewId()
		{
			return newId;
		}

		string getNewTimeSpent()
		{
			return newTimeSpent;
		}

		string getNewLastLogTime()
		{
			return getNewLastLogTime;
		}

		int getNewIsLoggedIn()
		{
			return newIsLoggedIn;
		}

		int getNewPrivilege()
		{
			return newPrivilege;
		}

		vector<User *> *useRequest()
		{
			DatabaseAccessor::updateRecord();
			return new vector<User *>;
		}
};