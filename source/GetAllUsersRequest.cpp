#include "request.h"
#include "DatabaseAccessor.h"

using namespace std;

class GetAllUsersRequest: public Request
{
	private:
		enum RequestType type = GetAllUsers;
	public:
		GetAllUsersRequest()
		{
			//nothing to see here	 
		}

		//enum Request::RequestType Request::getType(){}
		enum RequestType getType()
		{
			return type;
		}

		vector<User *> *useRequest()
		{
			return DatabaseAccessor::getAllUsers();
		}
};