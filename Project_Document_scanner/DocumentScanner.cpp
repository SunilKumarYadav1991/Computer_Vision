/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 17 Oct 2021
* Description: Extracting given document automatically from image and displaying in wrap perspective.
* steps:
* preprocess :convert to gray scale and then do canny edge detection
* get contour
* wraps
* Future Improvement: User's input via call back to select 4 co ordinates.
***********************************************************************************************/
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
using namespace cv;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// function takes input BGR image and convert it to gray scale and 
//returns dialated img  after application of canny edge detection
Mat preprocess_img(Mat& img)
{   
    Mat img_gray, img_blur, img_canny, img_dilate;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);         // convert img color space. Output image is second arg
    
    GaussianBlur(img_gray, img_blur, Size(3, 3), 3, 0);   // blurring image using gaussian fliter. 
                                                     // 3rd param i.e. Size(7,7) is SE kernal

    Canny(img_blur, img_canny, 25, 75);            // edge detection using canny algo

    // Running dilation on canny output to improve edge thickness
    Mat se1 = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(img_canny, img_dilate, se1);     // dialating image i.e. increasing foreground or increasing object
   
    return img_dilate;
}

// Function takes dialated image and input image (if required to draw conour) and 
// returns points of largest shape i.e. document(assumption on which this algo work)
vector<Point> get_shape_contours(Mat& dial_img, Mat& in_img)
{
    vector<vector<Point>> contours;                                                       // vector to store contour points
    vector<Vec4i> hierarchy;

    findContours(dial_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> contourPoly(contours.size());
    vector<Rect> bound_rect(contours.size());                                           // bouning box/rect around shape

    vector<Point> biggest_detected_object_points;										// position from where virtual canvas starts drawing
    int max_area{ 0 };

    for (int i = 0; i < contours.size(); ++i)                                           // loop through all contours
    {
        int c_area = contourArea(contours[i]);
        

        if (c_area > 1000)     // removing noise etc as per area threshold
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

            if (c_area > max_area && contourPoly[i].size() == 4)  // biggest rectangle (4 point contour) in img
            {
                biggest_detected_object_points = { contourPoly[i][0],
                                            contourPoly[i][1], 
                                            contourPoly[i][2] ,
                                            contourPoly[i][3] }; // update points of detected rectangle
                max_area = c_area;
                //drawContours(in_img, contourPoly, i, Scalar(255, 0, 255), 2);   // draw biggest rect obj
            }
            // note: contours point will not be in same sequence and hence processing required.  
        }
    }
   
    return biggest_detected_object_points;
}

// Function to draw circle on specified points on the input img
void draw_points(Mat& in_img, vector<Point> points, Scalar color)
{
    for (int i = 0; i < points.size(); ++i)
    {
        circle(in_img, points[i], 10,color, FILLED);
        putText(in_img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
    }
}


// Function re organizes the sequence of points from get_shape_contours() before wrap transform can be perfromed.
// returns points in order of {tl, tr, bl, br}
vector<Point> reorder_points(vector<Point> points)
{
    vector<Point> reordered_points(4);
    vector<int> sum_points, sub_points;
    
    // basic idea is to sum (x,y) and subtract (x,y) of all 4 cornors 
    // based on values weight we can identify top left point 1, top right 2, bottom left 3 and bottom right
    for (auto p : points)
    {
        sum_points.push_back(p.x + p.y);
        sub_points.push_back(p.x - p.y);
    }
    // Note: use pen and paper to manually calculate the values to understand better

    int idx0= min_element(sum_points.begin(), sum_points.end()) - sum_points.begin();      // min/max_element returns iterator. Sub tracting begin() iter
    int idx1= max_element(sub_points.begin(), sub_points.end()) - sub_points.begin();      // to find exact index
    int idx2= min_element(sub_points.begin(), sub_points.end()) - sub_points.begin();
    int idx3=  max_element(sum_points.begin(), sum_points.end()) - sum_points.begin();

    reordered_points[0] = points[idx0];
    reordered_points[1] = points[idx1];
    reordered_points[2] = points[idx2];
    reordered_points[3] = points[idx3];

    return reordered_points;
}


// Function perfrom perspective transfrom on input image and 4 points (from detected doc object)
// returns extracted img after transform
Mat get_wrap(Mat img, vector<Point> doc_point, float width, float height)
{
    Mat img_wrap;

    if (doc_point.size() != 4)
    {
        cerr << "invalid no. of points for perspective transform\n";
        // generate exception to handle in main()
    }

    Point2f src[4] = { doc_point[0], doc_point[1], doc_point[2], doc_point[3]}; // (x,y) values of 4 corners of doc
    Point2f dst[4] = { {0.0f,0.0f},{width,0.0f},{0.0f,height},{width,height} };     // (x,y) values of 4 corners of extracted card img
           
    Mat matrix = getPerspectiveTransform(src, dst); 
    warpPerspective(img, img_wrap, matrix, Point(width, height));

    return img_wrap;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    string path = "D:/Win7_Vostro/G_Drive/VectorCAST_Copy/SKY/10.OpenCV/WorkingDirectory/Open_CV_Project/Open_CV_Project/Resources/paper.jpg";
    Mat in_img = imread(path, IMREAD_COLOR);
    Mat img, img_dial, img_grey;
    
    Size img_size = in_img.size();

    if (img_size.width > 1024 || img_size.height > 1024)    // resizing img if its too large
             resize(in_img, img, Size(), 0.3, 0.3);         // scaling input image 0.5 times on x and y axis
    else
               img = in_img; 

    Mat dial_img = preprocess_img(img);
    vector<Point> biggest_obj_points = get_shape_contours(dial_img, img);

    Scalar color{ 255,0,255 };
    vector<Point> updated_doc_point = reorder_points(biggest_obj_points);
    //draw_points(img, updated_doc_point, color);

    // A4 size paper wrt pixel
    float width = 420;
    float height = 840;

    Mat wrap_img = get_wrap(img, updated_doc_point, width, height);
    
    // Note: edges may be rough so may need to crop certain pixel from edges
    int crop_pixel = 5;
    int crop_width = width - (2 * crop_pixel);
    int crop_height = height - (2 * crop_pixel);
    Rect roi(crop_pixel, crop_pixel, crop_width, crop_height);

    Mat cropped_img = wrap_img(roi);

    imshow("Input image", img);
    //imshow("dialated image", dial_img);
    //imshow("wrap image", wrap_img);
    imshow("cropped wrap image", cropped_img);

    waitKey(0);

    return 0;
}
