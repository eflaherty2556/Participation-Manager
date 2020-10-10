#include "request.h"
#include "UpdateUserResult.cpp"


using namespace std;

class UpdateUserRequest: public Request
{
	private:
		RequestType type = UpdateUser;

		int newId;
		string newTimeSpent; 
		string newLastLogTime;
		int newIsLoggedIn; 
		int newPrivilege;
	public:
		UpdateUserRequest(int newId, string newTimeSpent, string newLastLogTime, int newIsLoggedIn, int newPrivilege)
		{
			this->newId = newId;
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

		int getNewId()
		{
			return this->newId;
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
			DatabaseAccessor::updateRecord(this->newId, this->newTimeSpent, 
				this->newLastLogTime, this->newIsLoggedIn, this->newPrivilege);

			return NULL;
		}

		Result *packageResults(vector<User *> *rawResults)
		{
			return new UpdateUserResult();
		}
};