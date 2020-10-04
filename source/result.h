using namespace std;

class Result
{
	private:
		enum ResultType type = User;
	public:
		enum ResultType {User};

		enum ResultType getType();
};