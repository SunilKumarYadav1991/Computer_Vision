/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 10 Sep 2021
* Description: Creating virtual board to draw something using red and blue color marker.
*
* Note: Uncomment main() blocks to test different sections.
*   Using Hue Saturation Value (HSV) color space. Read more on color space.
*  H: 0 - 180 degree
*  S: 0 - 255
*  V: 0 - 255
* To bette understand color threshold, use track bar to get right values. Experiment with other images.
* Red Marker: Hmin,hmax, smin, smax, vmin, vmax:0,10, 212, 255, 85,245
* Blue Marker: Hmin,hmax, smin, smax, vmin, vmax:58, 123, 165, 255, 54, 189
***********************************************************************************************/
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;

VideoCapture vcap(1);
Mat img;

// HSV values for object to be used as marker
// hmin,smin,vmin,hmax,smax,vmax
vector<vector<int>> my_colors{ {58,164,54,123,255,189},     // Blue color
								{0,212,82,10,255,245} };    // Red color

// drawing color
vector<Scalar> my_color_value{ {255,0,0},			// BGR value for Blue color
								{0,0,255} };        // BGR value for Red color
 
vector<vector<int>> newPoints;          // holds 3points per position. x,y,i where x,y are co-ordinates and i is index to my_color_value

Point get_shape_contours_(Mat& dial_img, Mat& in_img)
{
    vector<vector<Point>> contours;                                                       // vector to store contour points
    vector<Vec4i> hierarchy;
    findContours(dial_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(in_img, contours, -1, Scalar(255, 0, 255), 2);                       // draw (all) contour on input img (BGR)

    vector<vector<Point>> contourPoly(contours.size());
    vector<Rect> bound_rect(contours.size());                                           // bouning box/rect around shape

	Point draw_point(0,0);

    for (int i = 0; i < contours.size(); ++i)                                           // loop through all contours
    {
        int c_area = contourArea(contours[i]);
        //cout << c_area << endl;
        if (c_area > 1000)     // removing noise etc as per area threshold
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

            drawContours(in_img, contourPoly, i, Scalar(255, 0, 255), 2);   // finds no. of points in countours  and draw lines between them
            //cout << "Number of contours " << contourPoly[i].size() << endl;

            bound_rect[i] = boundingRect(contourPoly[i]);
            rectangle(in_img, bound_rect[i].tl(), bound_rect[i].br(), Scalar(0, 255, 0), 3);   // bound_rect[i].tl()/br() gives top left/ bottom right points
			draw_point.x = bound_rect[i].x + bound_rect[i].width / 2;
			draw_point.y = bound_rect[i].y;
        }
    }

	return draw_point;

}

vector<vector<int>> find_color(Mat img)
{
	Mat img_hsv, mask;
	//int 
	cvtColor(img, img_hsv, COLOR_BGR2HSV);
	
	//for (auto mcolor : my_colors)          // to show multiple mask img use named window approch
	for(int i=0; i< my_colors.size();++i)
	{
		Scalar lower(my_colors[i][0], my_colors[i][1], my_colors[i][2]);                 // upper and lower threshod to mask out other details from HSV img
		Scalar upper(my_colors[i][3], my_colors[i][4], my_colors[i][5]);
		inRange(img_hsv, lower, upper, mask);
		//imshow(to_string(i), mask);
		
		Point my_point= get_shape_contours_(mask, img);
		//imshow("img", img);
		if(my_point.x!=0 && my_point.y!=0)
			newPoints.push_back({ my_point.x,my_point.y,i });
	}
	return newPoints;
}

void draw_on_virtual_canvas(vector<vector<int>> newPoints, vector<Scalar> my_color_value)
{

	for (int i = 0; i < newPoints.size(); ++i)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, my_color_value[newPoints[i][2]], FILLED);
		//cout << "Points (" << newPoints[i][0] << " , " << newPoints[i][1] << ") and i:"<<i<<"\n";
	}
}
//
//int main()
//{
//	//VideoCapture vcap(1);
//	//Mat img;			// holds frame of webcam feed
//	while (true)
//	{
//		vcap.read(img);    // alternate vcap.read(frame)
//		newPoints =find_color(img);
//		//imshow("web cam 1", img);
//		draw_on_virtual_canvas(newPoints, my_color_value);
//		imshow("Virtual Canvas", img);
//		waitKey(1);
//	}
//
//	return 0;
//}