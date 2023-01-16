/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 29Aug2021
* Description: Getting started with OpenCV. This program reads image and videos to display in windows
*
* 
* Note: Uncomment main() blocks to test different sections
***********************************************************************************************/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//----------------------------------------------------------------------------------------------------------------------
// example for image read
//
//int main()
//{
//    string path = "Resources/land.jpg";
//
//    Mat img = imread(path, IMREAD_COLOR);
//    imshow("Display window", img);
//    waitKey(0);
//
//    return 0;
//}

/* to extract BGR planes we can use one of the method
// 1.
Mat src=imread("my.png");
Mat planes[3];
split(src,planes);

2. 
prefer to use void cv::extractChannel (InputArray src, OutputArray dst, int coi )

cv::Mat out; cv::extractChannel(in, out, 0) // Supposing RGB channel with red first out....
*/


//----------------------------------------------------------------------------------------------------------------------
// example video read

//int main()
//{
//    string video_path = "Resources/test_video.mp4";
//
//    VideoCapture v_cap(video_path);
//    Mat img;
//
//    while (true)                        // while one generate exception once v_cap frame read is over
//    {    
//        v_cap.read(img);                // load each frame into img
//        imshow("Display window", img);  // display img
//        waitKey(10);                    // delay of 10 ms
//    }
//
//    return 0;
//}

//----------------------------------------------------------------------------------------------------------------------
// webcam example

//int main()
//{
//  
//    VideoCapture v_cap(1);       // camera id. 0 for default  webcam
//    Mat img;
//
//    while (true)                        // while one generate exception once v_cap frame read is over
//    {
//        v_cap.read(img);                // load each frame into img
//        imshow("Display window", img);  // display img
//        waitKey(1);                    // delay of 1s only to show img frames from camera feed
//    }
//
//    return 0;
//}