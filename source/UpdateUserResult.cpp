#include "result.h"

using namespace std;

class UpdateUserResult: public Result
{
	private:
		ResultType type = UpdatedUser;
	public:


		ResultType getType()
		{
			return this->type;
		}
};