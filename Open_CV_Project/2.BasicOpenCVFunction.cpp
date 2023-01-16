/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 29Aug2021
* Description: Getting started with OpenCV. This program deals with basic image processing function
*
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


//----------------------------------------------------------------------------------------------------------------------
// Basic image processing functions of openCV

//int main()
//{
//    string path = "Resources/ThreeFriends.jpg";
//
//    Mat img = imread(path, IMREAD_COLOR);
//
//    Mat img_gray, img_blur, img_canny, img_dilate, img_erode;
//
//    cvtColor(img,img_gray,COLOR_BGR2GRAY);         // convert img color space. Output image is second arg
//    
//    GaussianBlur(img_gray, img_blur, Size(7, 7), 3, 0);   // blurring image using gaussian fliter. 
//                                                     // 3rd param i.e. Size(7,7) is SE kernal
//
//    Canny(img_blur, img_canny, 50, 150);            // edge detection using canny algo
//
//    Mat se1 = getStructuringElement(MORPH_RECT, Size(3, 3));
//    Mat se2 = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
//
//    dilate(img_canny, img_dilate, se1);     // dialating image i.e. increasing foreground or increasing object
//    erode(img_canny, img_erode, se2);     // eroding image  i.e increasing background or reducing object 
//
//    imshow("BGR image", img);
//    imshow("Gray scale image", img_gray);
//    imshow("Blur image", img_blur);
//    imshow("Canny image", img_canny);
//    imshow("Canny image dilated", img_dilate);
//    imshow("Canny image eroded", img_erode);
//    
//    
//    waitKey(0);
//
//    return 0;
//}

// slicing alternative in OpenCV c++: Range() function
//Mat crop = img(Range(80,280),Range(150,330))