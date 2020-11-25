#include "request.h"
#include "GetUserResult.cpp"

using namespace std;

class GetUserRequest: public Request
{
	private:
		RequestType type = GetUser;
		int id = 0;
	public:
		GetUserRequest(int id)
		{
			this->id = id; 
		}

		//enum Request::RequestType Request::getType(){}
		RequestType getType()
		{
			return this->type;
		}

		int getId()
		{
			return this->id;
		}

		vector<User *> *useRequest()
		{
			return DatabaseAccessor::getUser(this->id);
		}

		Result *packageResults(vector<User *> *rawResults)
		{
			return new GetUserResult(rawResults);
		}
};