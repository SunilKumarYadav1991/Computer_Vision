/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 10 Sep 2021
* Description: Understanding how to extract sub set of image(card in this case) and display it 
*		as in proper angle. This is also known as Image Alignment.
*
* Note: Uncomment main() blocks to test different sections.
*   Read more on prespective transform and geometric transforms
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
//    string path = "Resources/cards2.jpg";
//    Mat img = imread(path, IMREAD_COLOR);
//       
//    // image to be extracted (from img) have below height and width
//    float w = 285, h = 301;
//    Mat matrix, imgWrap;
//
//    Point2f src[4] = { {622,179},{907,96},{874,481},{1156,364} }; // (x,y) values of 4 corners of card
//    Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };     // (x,y) values of 4 corners of extracted card img
//
//       
//    matrix = getPerspectiveTransform(src, dst); 
//    warpPerspective(img, imgWrap, matrix, Point(w, h)); 
//    
//    // To debug or understand better, draw circle around edges of input img
//    for (int i = 0; i < 4; ++i)
//        circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
//
//   
//    imshow("Input image", img);
//    imshow("Warped image", imgWrap);
//    waitKey(0);
//
//    return 0;
//}