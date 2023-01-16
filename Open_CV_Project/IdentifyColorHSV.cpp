/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 10 Sep 2021
* Update: 23 Sep 2021
* Description: Understanding how to detect particular color or shape of perticular color and create
*    mask for further usage.
*
* Note: Uncomment main() blocks to test different sections.
*   Using Hue Saturation Value (HSV) color space. Read more on color space.
*  H: 0 - 180 degree
*  S: 0 - 255
*  V: 0 - 255
* To bette understand color threshold, use track bar to get right values. Experiment with other images.
* 
* 
* Red Marker: Hmin,hmax, smin, smax, vmin, vmax:0,10, 212, 255, 85,245
* Blue Marker: Hmin,hmax, smin, smax, vmin, vmax:58, 123, 165, 255, 54, 189
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
//    VideoCapture vcap(1);    // external webcam
//
//    string path = "Resources/lambo.png";
//    Mat img;  
//    Mat img_hsv, mask;
//
//    int hmin = 0, smin = 0, vmin = 0;                // min and max values of HSV channel to detect object
//    int hmax = 0, smax = 0, vmax = 0;               // values are wrt lambo.png
//
//    namedWindow("Trackers", (600,600));                  // creating named window to hold track bars
//    createTrackbar("Hue Min", "Trackers", &hmin, 179);
//    createTrackbar("Hue Max", "Trackers", &hmax, 179);
//    createTrackbar("Sat Min", "Trackers", &smin, 255);
//    createTrackbar("Sat Max", "Trackers", &smax, 255);
//    createTrackbar("Val Min", "Trackers", &vmin, 255);
//    createTrackbar("Val Max", "Trackers", &vmax, 255);
//
//    while (true)
//    {
//        vcap >> img;
//        cvtColor(img, img_hsv, COLOR_BGR2HSV);               // converting input img to HSV color space
//        Scalar lower(hmin, smin, vmin);                 // upper and lower threshod to mask out other details from HSV img
//        Scalar upper(hmax, smax, vmax);
//
//        inRange(img_hsv, lower, upper, mask);           // excluding values out of range from [lower:upper] from input img and creating mask img (CV_8U type)
//
//
//        //imshow("input image", img);
//        //imshow("HSV image", img_hsv);
//        imshow("mask image", mask);
//        cout << hmin << " " << smin << " " << vmin << " " << hmax << " " << smax << " " << vmax << endl;
//        waitKey(1);
//    }
//    return 0;
//}