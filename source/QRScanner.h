#include <iostream>
#include <vector>
#include <zbar.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>

using namespace std;
using namespace cv;
using namespace zbar;
using namespace raspicam;

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
		static bool setupCamera();
		static Mat getImage(); //https://www.uco.es/investiga/grupos/ava/node/40
		static void shutdownCamera();
	private:
		inline static RaspiCam_Cv camera;
};
