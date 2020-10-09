using namespace std;

class Result
{
	private:
		enum ResultType type = User;
	public:
		enum ResultType {User = 0, AllUsers, UpdateUser};

		enum ResultType getType();
};