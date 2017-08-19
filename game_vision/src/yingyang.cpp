/*
 * yingyang.cpp
 *
 *  Created on: 13 Jun 2017
 *      Author: sheun
 */

#include "yingyang.h"

ying_yang::ying_yang() {

cout<<"converting to binary"<<endl;
}

ying_yang::~ying_yang() {

}
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
 Mat  ying_yang::Watershed(Mat Binary, Mat origanal_image)
{
	// Use the distance transform algorithm
	    Mat distance; //hold output matrix result of distance transform function
	    //CV_CV_DIST_L2_L2 = Euclidian distance and using a 3x3 mask change last parameter "3" to 5  for a more accurate distance estimation
	    //default output image type is CV_32F
	    distanceTransform(Binary, distance, CV_DIST_L2, 3);
	    // Normalize the distance image within range 0.0-1.0} to threshold it

	    normalize(distance, distance, 0, 1., NORM_MINMAX);

	    // Threshold to obtain the peaks
	    // This will be the markers for the foreground objects
	    threshold(distance, distance, 0.043, 1., CV_THRESH_BINARY);
	    // Dilate a bit the distance image
	    //use  convolution matrix masking
	    Mat kernel = Mat::ones(3, 3, CV_8UC1);
	    dilate(distance, distance, kernel);


	    // Create the CV_8U (unsigned 8bit/pixel) version of the distance image so to get pixel values between 0-255
	    // It is needed for findContours()
	    Mat distance_8u;
	    distance.convertTo(distance_8u, CV_8U);
	    // Find total markers
	    vector<vector<Point> > contours;
	    findContours(distance_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	    // Create the marker image for the watershed algorithm
	    Mat markers = Mat::zeros(distance.size(), CV_32SC1);
	    // Draw the foreground markers
	    for (size_t i = 0; i < contours.size(); i++)
	        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);

	    // Perform the watershed algorithm
	    watershed(origanal_image, markers);
	   // the markers image will be -1 at the boundaries of the regions
	    cv::Mat region = markers==-1;

	    return region;
}
 /**
 	 *****************************************************************************************
 	 *  @brief      binary image converter
 	 *
 	 *  @usage      convert grayscale image into a binary image using the watershed segmentation method
 	 *
 	 *  @param      grayscale image
 	 *  @param      original (non-grayscale image)
 	 *
 	 *  @return     Mat Binary image
 	 ****************************************************************************************/
Mat ying_yang::binary (Mat img,Mat origanal)
{

	 Mat binaryImage;
	 //create binary image
	 threshold(img, binaryImage, 0.5, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	 //clean up the binary image i.e. remove small blobs
	 binaryImage = cleanupBinary(binaryImage);
	 Mat Binary_post_watershed = Watershed(binaryImage,  origanal);


	 return Binary_post_watershed;
}

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
Mat ying_yang::binary_Inverse (Mat img,Mat origanal)
{
	double alpha = 2.2;//contrast control
	int beta = 50;//brightness control
	Mat contrasted, binaryImage, binaryImage_inv;
	img.convertTo(contrasted, -1, alpha, beta);

	threshold(contrasted, binaryImage,0.5,255,THRESH_BINARY| CV_THRESH_OTSU);
	binaryImage = cleanupBinary(binaryImage);
	//inverse the binary image
	bitwise_not(binaryImage, binaryImage_inv);

	Mat Binary_post_watershed = Watershed(binaryImage_inv,  origanal);


	return Binary_post_watershed;
}




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
Mat ying_yang::cleanupBinary(Mat Binary)
{
		Mat se1 = getStructuringElement(MORPH_RECT, Size(10, 10));
	    Mat se2 = getStructuringElement(MORPH_RECT, Size(4, 4));

	    // Perform closing then opening
	    Mat mask;
	    morphologyEx(Binary, mask, MORPH_CLOSE, se1);
	    morphologyEx(mask, mask, MORPH_OPEN, se2);

	    // Filter the output
	    Mat CleanedBinaryImage = Binary.clone();
	    CleanedBinaryImage.setTo(Scalar(0), mask == 0);

	    return CleanedBinaryImage;
}
