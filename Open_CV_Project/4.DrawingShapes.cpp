/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 7 Sep 2021
* Description: Understanding how to draw shapes in image
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
//
//int main()
//{
//    string path = "Resources/ICE.jpg";
//
//    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));     // creating 512x512 white image(BRG value is 255)
//                                                           // CV_8UC3 denote 8bit scale with 3 planes
//    //----------------------------------------------------------------------------------------------------------------------
//    //circle(img, Point(255, 255), 120, Scalar(0, 69, 255), 10);           // drawing circle of radius 120 at point 255,255 on exiting image. 
//    circle(img, Point(255, 255), 120, Scalar(0, 69, 255), FILLED);        // creates filled circle
//    
//    //----------------------------------------------------------------------------------------------------------------------
//    Rect rec(130, 226, 150, 50);        // creating rect with point size 150 by 50 at point 130,226
//    rectangle(img, rec, Scalar(200, 160, 198), FILLED);              // creating filled rectangle
//
//    //rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);    // rectangle with top left and bottom right point
//
//    //----------------------------------------------------------------------------------------------------------------------
//    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);   // drawing white line of width 2
//
//    //----------------------------------------------------------------------------------------------------------------------
//    putText(img, "Sunil Kumar Yadav", Point(137, 262), FONT_HERSHEY_SCRIPT_COMPLEX,0.5,Scalar(255,255,255),1);
//
//
//
//    imshow("Image", img);
//    waitKey(0);
//    return 0;
//}