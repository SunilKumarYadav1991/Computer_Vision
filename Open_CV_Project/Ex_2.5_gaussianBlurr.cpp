//Example 2 - 5. Loading and then smoothing an image before it is displayed on the screen
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include<string>
using namespace std;
using namespace cv;

void example2_5(const cv::Mat & image) {
	// Create some windows to show the input
	// and output images in.

	cv::namedWindow("Example2_5-in", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Example2_5-out", cv::WINDOW_AUTOSIZE);
	// Create a window to show our input image
	//
	cv::imshow("Example2_5-in", image);
	// Create an image to hold the smoothed output
	//
	cv::Mat out;
	// Do the smoothing
	// ( Note: Could use GaussianBlur(), blur(), medianBlur() or bilateralFilter(). )
	//
	cv::GaussianBlur(image, out, cv::Size(5, 5), 3, 3);
	cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);
	// Show the smoothed image in the output window
	//
	cv::imshow("Example2_5-out", out);
	// Wait for the user to hit a key, windows will self destruct
	//
	cv::waitKey(0);
}


//int main()
//{
//    string path = "Resources/ThreeFriends.jpg";
//
//    Mat img = imread(path, IMREAD_COLOR);
//	example2_5(img);
//
//	return 0;
//}



//Example 2 - 6. Using cv::pyrDown() to create a new image that is half the width and
//height of the input image
//#include <opencv2/opencv.hpp>

//int main(int argc, char** argv) {
//	cv::Mat img1, img2;
//
//	cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
//	cv::namedWindow("Example2", cv::WINDOW_AUTOSIZE);
//
//	img1 = cv::imread("Resources/ThreeFriends.jpg");
//
//	cv::imshow("Example1", img1);
//	cv::pyrDown(img1, img2);                //downsample and blur
//	cv::imshow("Example2", img2);
//	cv::waitKey(0);
//
//	return 0;
//};