#pragma once 
//result.h is needed both in request.h and in each class that implements this one
//since each class that implements request needs both of those things, 
//this is used to prevent redefinition
#include "DatabaseAccessor.h"

using namespace std;

class Result
{
	public:
		enum ResultType {GotUser = 0, GotAllUsers, UpdatedUser};

		ResultType getType();
	private:
		ResultType type;
};