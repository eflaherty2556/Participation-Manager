#include "request.h"
#include "GetAllUsersRequest.cpp"
#include "GetAllUsersResult.cpp"


using namespace std;

class Requester 
{
	public:
		static Result *makeRequest(Request *request);
};