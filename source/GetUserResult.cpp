#include "result.h"

using namespace std;

class GetUserResult: public Result
{
	private:
		ResultType type = GotUser;
		vector<User *> *user;
	public:
		GetUserResult(vector<User *> *user)
		{
			this->user = user;
		}

		ResultType getType()
		{
			return this->type;
		}

		vector<User *> *getResults()
		{
			return this->user;
		}
};