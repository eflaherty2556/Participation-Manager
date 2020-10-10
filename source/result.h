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