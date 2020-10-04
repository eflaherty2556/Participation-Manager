using namespace std;

class Request
{
	private:
		enum RequestType type = getUser;
	public:
		enum RequestType {GetUser, GetAllUsers};

		enum RequestType getType(); //for implementation: enum Request::RequestType Request::getType(){} 
};