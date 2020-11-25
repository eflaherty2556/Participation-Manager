#pragma once
#include "result.h"

using namespace std;

class Request
{
	public:
		enum RequestType {GetUser = 0, GetAllUsers, UpdateUser};

		virtual RequestType getType() = 0; //for implementation: enum Request::RequestType Request::getType(){} 
		virtual vector<User *> *useRequest() = 0;
		virtual Result *packageResults(vector<User *> *rawResults) = 0;
	private:
		RequestType type;
};