// #if _GLIBCXX_USE_CXX11_ABI
// #  define DUAL_ABI cxx11 __attribute__((abi_tag("cxx11")))
// #else
// #  define DUAL_ABI cxx03
// #endif

#include <string>

using namespace std;

class User
{
	private:
		int id;
		string name;
		string timeSpent;
		string lastLogTime;
		bool isLoggedIn;
		int privilege;

	public:
		User(int id, string name, string timeSpent, string lastLogTime, bool isLoggedIn, int privilege);

		int getId();
		string getName();
		string getTimeSpent();
		string getLastLogTime();
		bool getIsLoggedIn();
		int getPrivilege();
};