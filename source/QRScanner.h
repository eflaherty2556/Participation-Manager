#include <iostream>
#include <vector>
#include <zbar.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace zbar;

class QRScanner
{
	public:
		typedef struct 
		{
			string type;
			string data;
			vector <Point> location;
		} decodedObject;

		static bool decode(Mat &image, vector<decodedObject>&decodedObjects);
	private:

};
