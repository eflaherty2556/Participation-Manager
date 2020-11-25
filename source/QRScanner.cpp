#include "QRScanner.h"

// RaspiCam_Cv camera;

bool QRScanner::decode(Mat &image, vector<decodedObject>&decodedObjects)
{
	bool foundAQRCode = false;

	if(image.empty())
		printf("Image empty!!\n\n");

	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	//sanity check for image channels and size
	//printf("Channels: %d\n", image.channels());
	//printf("Rows: %d, Cols: %d\n", image.rows, image.cols);

	Mat grayImage;
	//printf("Hi :)\n");
	//cvtColor(image, grayImage, COLOR_BGR2GRAY, 4); //if testing an rgb image
	//printf("Bye :(\n");

	Image zbarImage(image.cols, image.rows, "Y800", (uchar *)image.data, image.cols * image.rows);

	scanner.scan(zbarImage);

	for(Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol)
	{
		foundAQRCode = true;

		decodedObject object;

		object.type = symbol->get_type_name();
		object.data = symbol->get_data();

		printf("Type: %s\nData: %s\n", object.type.c_str(), object.data.c_str());

		for(int i = 0; i < symbol->get_location_size(); i++)
			object.location.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
		
		decodedObjects.push_back(object);
	}

	return foundAQRCode;
}

bool QRScanner::setupCamera()
{
	camera.set(CAP_PROP_FORMAT, CV_8UC1);
	bool result = camera.open();

	if(!result)
		printf("Error opening camera");

	return result;
}

Mat QRScanner::getImage()
{
	Mat capturedImage;

	camera.grab();
	camera.retrieve(capturedImage);

	if(capturedImage.empty())
		printf("Image is empty!!");

	return capturedImage;
}

void QRScanner::shutdownCamera()
{
	camera.release();
}

// int main(int argc, char *argv[])
// {
// 	// string imagepath = argv[1];
// 	// Mat image = imread(imagepath);
// 	bool result = QRScanner::setupCamera();
// 	Mat image = QRScanner::getImage();
// 	QRScanner::shutdownCamera();

// 	vector<QRScanner::decodedObject> decodedObjects;

// 	bool found = QRScanner::decode(image, decodedObjects);
// 	printf("Found: %s\n", found ? "yes" : "no");

// 	return 0;
// }
