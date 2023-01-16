/***********************************************************************************************
* Author: Sunil Kumar Yadav
* Date: 18 Sep 2021
* Description: Understanding how to use Viola Jones face detection algorithm to detect face in OpenCV
*
* Note: I'm using pretrained modes for cascade classifier. For more such classifier refer OpenCV folder
* Frontal Face: C:/opencv4.5.3/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml
* Eyes: C:/opencv4.5.3/opencv/sources/data/haarcascades/haarcascade_eye.xml
* 
* 
***********************************************************************************************/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>  // for cascade classifier 
#include <iostream>
#include <vector>
#include <string>


using namespace cv;
using namespace std;


// Input: image
// Output: void. Draws bounding rectangle around detected face in input image
void detect_faces(Mat& img)
{

    CascadeClassifier face_cascade;

    face_cascade.load("Resources/haarcascade_frontalface_default.xml");
    //face_cascade.load("C:/opencv4.5.3/opencv/sources/data/haarcascades/haarcascade_frontalcatface.xml");

    if (face_cascade.empty())
        cout << "Classifier has not been loaded!\n";

    // creating rect for printing bounding box around detected faces
    vector<Rect> faces;
    face_cascade.detectMultiScale(img, faces, 1.1,10);        // Detects objects of different sizes in the input image.   
                                                              // The detected objects are returned as a list of rectangles.

   // face_cascade.detectMultiScale(img, faces, 1.1, 10, 0, Size(30, 30));
    
   

    // drawing bounding box around detected faces
    for (auto& face : faces)
        rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);

}

//----------------------------------------------------------------------------------------------------------------------
// Face detection from img
//
int main()
{
    string path = "Resources/ThreeFriends.jpg";
    //string path = "D:/Win7_Vostro/G_Drive/VectorCAST_Copy/SKY/1.Blog/BlogCategory/7.OpenVC_and_Computer_Vision/3. Face Detection Using Viola Jones algorithm using OpenCV/mod_obama.jpg";

    Mat img = imread(path);

    detect_faces(img);

    imshow("Face Detection", img);
    waitKey(0);
    return 0;
}


//----------------------------------------------------------------------------------------------------------------------
 //Face detection via live feed from webcam

//int main()
//{
//    VideoCapture v_cap(0);
//    Mat img;
//    
//    while (true)                        // while one generate exception once v_cap frame read is over
//    {    
//        v_cap.read(img);                // load each frame into img
//        detect_faces(img);
//        imshow("Detected Faces", img);  // display img
//        waitKey(10);                    // delay of 10 ms 
//                                         // use sleep() if required
//
//    }
//
//    return 0;
//}