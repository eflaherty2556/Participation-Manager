#include "result.h"

using namespace std;

class GetAllUsersResult: public Result
{
	private:
		ResultType type = GotAllUsers;
		vector<User *> *users;
	public:
		GetAllUsersResult(vector<User *> *users)
		{
			this->users = users;
		}

		ResultType getType()
		{
			return this->type;
		}

		vector<User *> *getResults()
		{
			return this->users;
		}
};