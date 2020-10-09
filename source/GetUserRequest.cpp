#include "request.h"

using namespace std;

class GetUserRequest: public Request
{
	private:
		enum RequestType type = GetUser;
		int id = 0;
	public:
		GetUserRequest(int id)
		{
			this->id = id; 
		}

		//enum Request::RequestType Request::getType(){}
		enum RequestType getType()
		{
			return type;
		}

		int getId()
		{
			return id;
		}

		vector<User *> *useRequest()
		{
			return DatabaseAccessor::getUser(this->id);
		}
};