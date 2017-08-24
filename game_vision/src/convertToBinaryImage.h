/*

* yingyang.h
 *
 *  Created on: 13 Jun 2017
 *      Author: sheun
 *
 *      return a binary image
 */
#ifndef CONVERTTOBINARYIMAGE_H_
#define CONVERTTOBINARYIMAGE_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
using namespace cv;



class convertToBinaryImage {

private:

	/**
		 *****************************************************************************************
		 *  @brief      clean up a binary image
		 *
		 *  @usage      remove small blobs from a binary image
		 *
		 *
		 *  @param      Binary image you want to clean
		 *
		 *  @return     Binary image
		 ****************************************************************************************/
	Mat cleanupBinary (Mat Binary);
	/**
		 *****************************************************************************************
		 *  @brief      Watershed segmentation
		 *
		 *  @usage      use watershed segmentation method to create binary image
		 *
		 *  @param      Binary Image
		 *  @param      original (non-grayscale image)
		 *
		 *  @return     Mat Binary image
		 ****************************************************************************************/
	Mat  Watershed(Mat Binary, Mat origanal_image);
public:
	convertToBinaryImage();
	virtual ~convertToBinaryImage();

	 /**
	 	 *****************************************************************************************
	 	 *  @brief      binary converter
	 	 *
	 	 *  @usage      convert grayscale image into i binary image using the watershed segmentation method
	 	 *
	 	 *  @param      grayscale image
	 	 *  @param      origanal (non-grayscale image)
	 	 *
	 	 *  @return     Mat Binary image
	 	 ****************************************************************************************/

	Mat binary (Mat img, Mat origanal);
	/**
		 *****************************************************************************************
		 *  @brief      binary image converter on inverse of a grayscale image
		 *
		 *  @usage      Heighten contrast on and convert grayscale image into a binary image using the watershed segmentation method
		 *
		 *
		 *  @param      grayscale image
		 *  @param      original (non-grayscale image)
		 *
		 *  @return     Mat Binary image
		 ****************************************************************************************/
	Mat binary_Inverse (Mat img, Mat origanal);


};

#endif