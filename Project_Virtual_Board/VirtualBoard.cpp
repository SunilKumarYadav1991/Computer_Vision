/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 23 Sep 2021
* Description: Creating virtual board to draw something using red and blue color object (used marker cap in this case as drawing object).
*
* Note: Need to refine the implementation and parameterize the functions.
* Using Hue Saturation Value (HSV) color space for easy processing. Read more on color space.
*  H: 0 - 180 degree
*  S: 0 - 255
*  V: 0 - 255
* 
* HSV threshold {Hmin,hmax, smin, smax, vmin, vmax}
* Red Marker: {0,10, 212, 255, 85,245}
* Blue Marker: {58, 123, 165, 255, 54, 189}
***********************************************************************************************/
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<vector>

//configure settng

using namespace std;
using namespace cv;

typedef vector<vector<int>> vec3_point_color;          // holds 3 int per position. x,y,i where x,y are co-ordinates and i is index to my_color_value
typedef vector<vector<int>> vec_hsv_threshold;         // vector of hsv threshold value. Each color threshold valuesm are in order of  {hmin,smin,vmin,hmax,smax,vmax} ,{...}   

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Funtion take dialated/edge detected image and draws countour and bounding rectangle around deteced object
// input: dialected img and raw input img
// return: position from where virtual canvas starts drawing
Point get_shape_contours(Mat& dial_img, Mat& in_img)
{
	vector<vector<Point>> contours;                                                       // vector to store contour points
	vector<Vec4i> hierarchy;
	
	findContours(dial_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> contourPoly(contours.size());
	vector<Rect> bound_rect(contours.size());                                           // bouning box/rect around shape

	Point draw_point(0, 0);																// position from where virtual canvas starts drawing

	for (int i = 0; i < contours.size(); ++i)                                           // loop through all contoursro\G_Drive\VectorCAST_Copy\SKY\10.Open
	{
		int c_area = contourArea(contours[i]);
		
		if (c_area > 1000)     // removing noise etc as per area threshold
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

			drawContours(in_img, contourPoly, i, Scalar(255, 0, 255), 2);						 // finds no. of points in countours  and draw lines between them
																								 // comment out in real app as its not required 

			bound_rect[i] = boundingRect(contourPoly[i]);
			rectangle(in_img, bound_rect[i].tl(), bound_rect[i].br(), Scalar(0, 255, 0), 3);   // bound_rect[i].tl()/br() gives top left/ bottom right points

			draw_point.x = bound_rect[i].x + bound_rect[i].width / 2;						   // x,y position from top middle position of bounding box
			draw_point.y = bound_rect[i].y;
		}
	}

	return draw_point;
}


// function  processes input video frame in hsv color space and get the position of bounding rect around contours of detected object
// input: raw image,  vector of hsv threshold values and vector of position and color index.
// return: void but function updates vector of position and color index of as per detected object. 
void process_color_object(Mat img, vec_hsv_threshold object_colors, vec3_point_color& posNColor)
{
	Mat img_hsv, mask;
	
	cvtColor(img, img_hsv, COLOR_BGR2HSV);          // converting to hsv color space for further processing

	//for (auto mcolor : my_colors)                 // to show multiple mask img use named window approch
	for (int i = 0; i < object_colors.size(); ++i)
	{
		Scalar lower(object_colors[i][0], object_colors[i][1], object_colors[i][2]);                 // upper and lower threshod to mask out other details from HSV img
		Scalar upper(object_colors[i][3], object_colors[i][4], object_colors[i][5]);
		inRange(img_hsv, lower, upper, mask);

		Point my_point = get_shape_contours(mask, img);									// position from where virtual canvas starts drawing
		if (my_point.x != 0 && my_point.y != 0)							
			posNColor.push_back({ my_point.x,my_point.y,i });							// maping x,y position with color index filtered object
	}
}

// draws filled circle on input image 
void draw_on_virtual_canvas(Mat img, vec3_point_color newPoints, vector<Scalar> my_color_value)
{
	for (int i = 0; i < newPoints.size(); ++i)					// based on detected types those many colors would be drawn from my_color_value
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, my_color_value[newPoints[i][2]], FILLED);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	VideoCapture vcap(1);
	Mat img;					                // holds frame of webcam feed
	vec3_point_color posNcolor;					// holds detected objec(marker cap) top position (x,y) and color index

	// threshold i.e.HSV values for object to be used as marker: Order of value {hmin,smin,vmin,hmax,smax,vmax}
	vec_hsv_threshold object_hsv_value{ {58,164,54,123,255,189},     // Blue color
								    	{0,212,82,10,255,245} };    // Red color

	// color value for drawing pattern for detected. Important: 2 color as object_hsv_value contain two object threshold
	vector<Scalar> draw_color_value{ {255,0,0},			// BGR value for Blue color
									 {0,0,255} };        // BGR value for Red color

	while (true)
	{
		vcap.read(img);						// alternate vcap.read(frame)
		process_color_object(img, object_hsv_value, posNcolor);
		draw_on_virtual_canvas(img, posNcolor, draw_color_value);
		imshow("Virtual Canvas", img);
		waitKey(1);
	}

	return 0;
}