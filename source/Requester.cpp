#include "Requester.h"

Result *Requester::makeRequest(Request *request)
{
	vector<User *> *rawResults = request->useRequest();
	return request->packageResults(rawResults);
}

int main(int argc, char *argv[])
{
	printf("Testing Requester:::\n");
	Request *myRequest = new GetAllUsersRequest();

	GetAllUsersResult *myResults = (GetAllUsersResult *)Requester::makeRequest(myRequest);
	vector<User *> *myUsers = myResults->getResults();

	printf("Printing users: \n");
	for(int i = 0; i < myUsers->size(); i++)
	{
		User *theUser = myUsers->at(i);
		printf("name: '%s'\n", (theUser->getName()).c_str());
	}
}

