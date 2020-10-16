#include "Requester.h"

#include "GetAllUsersRequest.cpp"
#include "GetAllUsersResult.cpp"

Result *Requester::makeRequest(Request *request)
{
	vector<User *> *rawResults = request->useRequest();
	return request->packageResults(rawResults);
}

int main(int argc, char *argv[])
{
   printf("Testing Requester:::\n");
   Request *myRequest = new GetAllUsersRequest();

   GetAllUsersResult *myResults = Requester::makeRequest(myRequest);

}

