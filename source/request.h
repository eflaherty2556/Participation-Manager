using namespace std;

class Request
{
	public:
		enum RequestType {GetUser = 0, GetAllUsers, UpdateUser};

		RequestType getType(); //for implementation: enum Request::RequestType Request::getType(){} 
		vector<T *> * useRequest();
	private:
		enum RequestType type;
};