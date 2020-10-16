#include "QRScanner.h"

// template <typename decodedObject>
void QRScanner::decode(Mat &image, vector<decodedObject>&decodedObjects)
{
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	Mat grayImage;
	cvtColor(image, grayImage, COLOR_BGR2GRAY);

	Image zbarImage(image.cols, image.rows, "Y800", (uchar *)grayImage.data, image.cols * image.rows);

	scanner.scan(zbarImage);

	for(Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol)
	{
		decodedObject object;

		object.type = symbol->get_type_name();
		object.data = symbol->get_data();

		printf("Type: %s\nData: %s\n", object.type.c_str(), object.data.c_str());

		for(int i = 0; i < symbol->get_location_size(); i++)
			object.location.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
		
		decodedObjects.push_back(object);
	}
}

int main(int argc, char *argv[])
{
  string imagepath = argv[1];
  Mat image = imread(imagepath);

  vector<QRScanner::decodedObject> decodedObjects;

  QRScanner::decode(image, decodedObjects);

  return 0;
}