// program to rotate an image through an angle
//
#include<opencv2/opencv.hpp>
#include<math.h>
#include<iostream>
using namespace cv;
using namespace std;
Mat RotateImage(Mat , float );
void ShowImage(Mat , Mat );
Mat RotateImage(Mat src, float angle)    // Function to rotate image at an given angle
{
	Mat dst;
	Point2f pt((src.cols) / 2., (src.rows) / 2.);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	Rect2f bbox = RotatedRect(Point2f(), src.size(), angle).boundingRect2f();
	// adjust transformation matrix
	r.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
	r.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;
	warpAffine(src, dst, r, bbox.size(), INTER_NEAREST);
	return dst;
}

void ShowImage(Mat src, Mat dst)          // // Function to display the original and rotated images
{
	
	namedWindow("Original Image");
	namedWindow("Rotated Image");
	imshow("Original Image", src);
	
	imshow("Rotated Image", dst);
	waitKey(0);
	destroyWindow("Original Image");
	destroyWindow("Rotated Image");
}
int main()
{
	float angle;
	string str;
	cout << "\n\t\t\t\tIMAGE ROTATION\t\n";
	cout << "\n\t\tEnter path of the image to be rotated: ";   // Message for user to enter the path to image 
	getline(cin,str);
	cout << "\n\t\tEnter angle: ";                            //Message for user to enter angle
	cin >> angle;
	Mat image = imread(str,1);   // Reading the image 
	if (image.empty())     // conditon to check if image exists or not
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}
	Mat dst = RotateImage(image, angle);        // function call to rotate image 
	ShowImage(image, dst);                      // function call to show image
	return 0;
	
}