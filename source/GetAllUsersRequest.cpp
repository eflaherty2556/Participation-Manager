#include "request.h"

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
};