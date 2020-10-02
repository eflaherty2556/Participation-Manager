#include <string>

using namespace std;

class User
{
	private:
		int id;
		string name;
		int hours;
		string lastLogTime;
		bool isLoggedIn;

	public:
		User(int id, string name, int hours, string lastLogTime, bool isLoggedIn);

		int getId();
		string getName();
		int getHours();
		string getLastLogTime();
		bool getIsLoggedIn();
};