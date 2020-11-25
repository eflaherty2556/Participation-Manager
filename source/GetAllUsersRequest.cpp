#include "request.h"
#include "GetAllUsersResult.cpp"


using namespace std;

class GetAllUsersRequest: public Request
{
	private:
		RequestType type = GetAllUsers;
	public:
		//enum Request::RequestType Request::getType(){}
		RequestType getType()
		{
			return this->type;
		}

		vector<User *> *useRequest()
		{
			return DatabaseAccessor::getAllUsers();
		}

		Result *packageResults(vector<User *> *rawResults)
		{
			return new GetAllUsersResult(rawResults);
		}
};