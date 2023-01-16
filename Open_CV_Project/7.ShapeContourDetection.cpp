/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 12 Sep 2021
* Description: Understanding how to detect object shape via edge detection method and draw 
*   rectangle around the shape
*
* Note: Uncomment main() blocks to test different sections. Read more on lib function used.
*   This example does not handle complex shape like star etc
***********************************************************************************************/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;


//----------------------------------------------------------------------------------------------------------------------
// helper function to draw contours around the shapes. Set threshold for excluding noise area
void get_shape_contours(Mat& dial_img, Mat& in_img)
{
    vector<vector<Point>> contours;                                                       // vector to store contour points
    vector<Vec4i> hierarchy;
    findContours(dial_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); 
    //drawContours(in_img, contours, -1, Scalar(255, 0, 255), 2);                       // draw (all) contour on input img (BGR)
    
    vector<vector<Point>> contourPoly(contours.size());
    vector<Rect> bound_rect(contours.size());                                           // bouning box/rect around shape
    

    for (int i = 0; i < contours.size();++i)                                           // loop through all contours
    {
        int c_area = contourArea(contours[i]);
        //cout << c_area << endl;
        if (c_area > 1000)     // removing noise etc as per area threshold
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);       // approximate poly curve with stated accurracy

            drawContours(in_img, contourPoly, i, Scalar(255, 0, 255), 2);   // finds no. of points in countours  and draw lines(purple) between them
            //cout << "Number of contours " << contourPoly[i].size() << endl;
            
            bound_rect[i] = boundingRect(contourPoly[i]);
            rectangle(in_img, bound_rect[i].tl(), bound_rect[i].br(), Scalar(0, 255, 0), 3);   // bound_rect[i].tl()/br() gives top left/ bottom right points
        
            // annotating image with shape type
            int obj_corners = (int)contourPoly[i].size();
            string obj_name;
            if (obj_corners == 3)
                obj_name = "Triangle";
            else if (obj_corners == 4)   // rectangle or square
            {
                float aspect_ratio = (float)bound_rect[i].width /(float) bound_rect[i].height;

                if(aspect_ratio>0.95 && aspect_ratio<1.05)    // tolerance for l/w ratio
                    obj_name = "Square";
                else
                    obj_name = "Rectangle";
            }
            /*else if (obj_corners >= 6)
                obj_name = "Polygon";*/
            else if (obj_corners > 6)
                obj_name = "Circle";

            Point text_point { bound_rect[i].x, bound_rect[i].y - 5 };      // y axis offset to ensure text is above detected shape
            putText(in_img, obj_name, text_point , FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1);
        }
    }

}

//----------------------------------------------------------------------------------------------------------------------

//int main()
//{
//    string path = "Resources/color_shapes.jpg";
//    //string path = "Resources/colourful-shape-icons.jpg";
//
//    Mat img = imread(path);
//
//    Mat img_gray, img_blur, img_canny, img_dilate, img_erode;
//
//    //----------------------------------------------------------------------------------------------------
//    // Preprocessing image 
//
//    cvtColor(img,img_gray,COLOR_BGR2GRAY);         // convert img color space. Output image is second arg
//    
//    GaussianBlur(img_gray, img_blur, Size(3, 3), 3, 0);   // blurring image using gaussian fliter. 
//                                                     // 3rd param i.e. Size(7,7) is SE kernal
//
//    Canny(img_blur, img_canny, 25, 75);            // edge detection using canny algo
//
//    // Running dilation on canny output to improve edge thickness
//    Mat se1 = getStructuringElement(MORPH_RECT, Size(3, 3));
//    dilate(img_canny, img_dilate, se1);     // dialating image i.e. increasing foreground or increasing object
//    //----------------------------------------------------------------------------------------------------
//
//    get_shape_contours(img_dilate, img);         // draw contour and print shap details
//
//
//    imshow("BGR image", img);
//   /* imshow("Gray scale image", img_gray);
//    imshow("Blur image", img_blur);
//    imshow("Canny image", img_canny);
//    imshow("Canny image dilated", img_dilate);*/
//    
//    
//    waitKey(0);
//
//    return 0;
//}