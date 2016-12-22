#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap;
    cap.open("http://192.168.1.11:8080/video?x.mjpeg");//opening IP camera
    namedWindow("MyVideo",CV_WINDOW_FREERATIO); //making a window for the video steam
    namedWindow("Control", CV_WINDOW_FREERATIO); // making a windows for the track bars
    int lowH = 0,highH=179,lowS=0,highS=255,lowV=0,highV=255;//variables to use in trackbars to control HSV
    cvCreateTrackbar("LH", "Control", &lowH, 179);//create track bar for minimum Hue
    cvCreateTrackbar("HH", "Control", &highH, 179);//create track bar for maxmium hue
    cvCreateTrackbar("LS", "Control", &lowS, 255);//create track bar for minimum saturation
    cvCreateTrackbar("HS", "Control", &highS, 255);//create track bar for maxmium saturation
    cvCreateTrackbar("LV", "Control", &lowV, 255);//create track bar for minimum value
    cvCreateTrackbar("HV", "Control", &highV, 255);//create track bar for maxmium value
    Mat frame,imgHSV,imgThreshold,imgTmp;
    cap.read(imgTmp);//Taking a temp. picture from the camera
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );//making a picture the same size as the camera picture
    int lastX = -1;//variables to save the last point of object tracked
    int lastY = -1;//variables to save the last point of object tracked
    while (1)
    {

        cap.read(frame);//reading the camera stream
        flip(frame, frame, 1);//flipping the image
        cvtColor(frame, imgHSV, COLOR_BGR2HSV);//converting the image to HSV instead of BGR
        inRange(imgHSV, Scalar(lowH, lowS,lowV), Scalar(highH, highS, highV), imgThreshold);//thresholding the pixels within the range of the HSV from the trackbars

        erode(imgThreshold, imgThreshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );//to make the white object brighter
        dilate( imgThreshold, imgThreshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );//cleaning the noise

        Moments oMoments = moments(imgThreshold);//getting the moements of the image

        double dM01 = oMoments.m01;//sum of all ones in Y axis
        double dM10 = oMoments.m10;//sum of all ones in X axis
        double dArea = oMoments.m00;//area of ones in the image
        if(dArea > 10000)//to ignore noise
        {
            //getting the central moment
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;

            if (lastX >= 0 && lastY >= 0 && posX >= 0 && posY >= 0)
            {
                //Draw a red line from the previous point to the current point
                line(imgLines, Point(posX, posY), Point(lastX, lastY), Scalar(225,255,0), 2);
            }
            lastX = posX;
            lastY = posY;
        }

        namedWindow("Thresholded Image",CV_WINDOW_FREERATIO);//creaint window for the thresholded image
        imshow("Thresholded Image", imgThreshold);
        frame=frame+imgLines;//adding the drawn lines to the frame
        imshow("MyVideo", frame); //show the frame in "MyVideo" window
        waitKey(1);

    }
    return 0;
}
