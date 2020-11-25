#include "request.h"
#include "UpdateUserResult.cpp"


using namespace std;

class UpdateUserRequest: public Request
{
	private:
		RequestType type = UpdateUser;

		int ID;
		string newTimeSpent; 
		string newLastLogTime;
		int newIsLoggedIn; 
		int newPrivilege;
	public:
		UpdateUserRequest(int ID, string newTimeSpent, string newLastLogTime, int newIsLoggedIn, int newPrivilege)
		{
			this->ID = ID;
			this->newTimeSpent = newTimeSpent;
			this->newLastLogTime = newLastLogTime;
			this->newIsLoggedIn = newIsLoggedIn;
			this->newPrivilege = newPrivilege;
		}

		//enum Request::RequestType Request::getType(){}
		RequestType getType()
		{
			return this->type;
		}

		int getID()
		{
			return this->ID;
		}

		string getNewTimeSpent()
		{
			return this->newTimeSpent;
		}

		string getNewLastLogTime()
		{
			return this->newLastLogTime;
		}

		int getNewIsLoggedIn()
		{
			return this->newIsLoggedIn;
		}

		int getNewPrivilege()
		{
			return this->newPrivilege;
		}

		vector<User *> *useRequest()
		{
			DatabaseAccessor::updateRecord(this->ID, this->newTimeSpent, 
				this->newLastLogTime, this->newIsLoggedIn, this->newPrivilege);

			return NULL;
		}

		Result *packageResults(vector<User *> *rawResults)
		{
			return new UpdateUserResult();
		}
};