#include "DatabaseAccessor.h"

using namespace std;

class Request
{
	public:
		enum RequestType {GetUser = 0, GetAllUsers, UpdateUser};

		RequestType getType(); //for implementation: enum Request::RequestType Request::getType(){} 
		vector<User *> * useRequest();
	private:
		RequestType type;
};