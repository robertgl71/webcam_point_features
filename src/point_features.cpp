/*
 * point_features.cpp
 *
 *  Created on: 31 oct. 2016
 *      Author: robert
 */

//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"


//std
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace cv;
using namespace std;

//consts
const unsigned int MIN_NUM_FEATURES = 300; //minimum number of point fetaures

int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
    cv::Mat imageOut1; //OpenCV image object
    cv::Mat imageOut2; //OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
    cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(); //ORB point feature detector
    orb_detector->setMaxFeatures(MIN_NUM_FEATURES);
    std::vector<cv::KeyPoint> point_set1; //set of point features
    std::vector<cv::KeyPoint> point_set2; //set of point features
    cv::Mat descriptor_set; //set of descriptors, for each feature there is an associated descriptor

	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }

//        //Definim 4 mask diferents per cobrir tota la imatge
//        vector< Rect > mask_rect;
//        mask_rect.push_back(Rect(0,0,image.cols/2,image.rows/2) );
//        mask_rect.push_back(Rect(image.cols/2,0,image.cols/2,image.rows/2) );
//        mask_rect.push_back(Rect(0,image.rows/2,image.cols/2,image.rows/2) );
//        mask_rect.push_back(Rect(image.cols/2,image.rows/2,image.cols/2,image.rows/2) );
//
//
//        Mat mask = Mat::zeros(image.size(), CV_8U);  // type of mask is CV_8U
//
//
//        for(int i=0; i< mask_rect.size(); ++i)
//        {
//         Mat roi(mask, mask_rect[i] );
//         roi = Scalar(255, 255, 255);
//        }

        //make mask
        int x=50;	//mask size *2
        Mat mask = Mat::zeros(image.size(), CV_8U);  // type of mask is CV_8U
        Mat roi(mask, Rect(image.cols/2-x,image.rows/2-x,2*x,2*x) );
        roi = Scalar(255, 255, 255);


        //clear previous points
        point_set1.clear();
        point_set2.clear();

        //detect and compute(extract) features
        orb_detector->detectAndCompute(image, cv::noArray(), point_set1, descriptor_set);
        orb_detector->detectAndCompute(image, mask, point_set2, descriptor_set);

        std::cout << "Point set 1:" << point_set1.size()<< std::endl;
        std::cout << "Point set 2:" << point_set2.size()<< std::endl;

        //draw points on the image
        cv::drawKeypoints( image, point_set1, imageOut1, 255, cv::DrawMatchesFlags::DEFAULT );
        cv::drawKeypoints( image, point_set2, imageOut2, 255, cv::DrawMatchesFlags::DEFAULT );

    //********************************************************************

        //show image
        cv::imshow("Sortida normal", imageOut1);
        cv::imshow("Màscara central", imageOut2);

		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if(cv::waitKey(1) >= 0) break;
    }
}
