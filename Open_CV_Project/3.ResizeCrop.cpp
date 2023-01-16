/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 7 Sep 2021
* Description: Getting started with OpenCV. This program deals with basic image processing operation
*	like croping image and resizing
*
* Note: Uncomment main() blocks to test different sections
***********************************************************************************************/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//int main()
//{
//    string path = "Resources/ICE.jpg";
//
//    Mat img = imread(path, IMREAD_COLOR);    
//    Mat resized_img;
//    Mat resized_ratio_img;
//    Mat cropped_img;
//
//    // printing size of image
//    cout << img.size()<<'\n';    //1280 x 960
//
//    // resizing image using resize() 
//    resize(img, resized_img, Size(600,400));
//    resize(img, resized_ratio_img, Size(), 0.5,0.5);        // scaling input image 0.5 times on x and y axis
//                                                            // scaling ensure aspect ratio remain similar to input image
// 
//    //use Range() for extracting portion of Mat
//    // crop specific region
//    Rect roi(400, 300, 400, 400);         // roi is rectangle of sixe 400x400 from point(400,300)
//    
//    cropped_img = img(roi);                // saving portion of image as per roi in new img
//
//    imshow("Original image",img);
//    imshow("Resized custom image", resized_img);
//    imshow("Resized ratio image", resized_ratio_img);
//    imshow("Cropped image", cropped_img);
//
//    waitKey(0);
//	return 0;
//}