/*
 * SeperateObjects.h
 *
 *  Created on: 9 Jul 2017
 *      Author: sheun
 *
 *      Separate objects/regions in an image and draw bounded boxes around them in the original captured image frame.
 */
#ifndef SEPERATEOBJECTS_H_
#define SEPERATEOBJECTS_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <map>


using namespace std;
using namespace cv;



class SeperateObjects {

private:


public:

	SeperateObjects();
	virtual ~SeperateObjects();

/**
	 *****************************************************************************************
	 *  @brief      identify objects and get their X and Y coordinates in the image frame
	 *
	 *  @usage      draw boxes around each object/region,
	 *  			create a vector of seperated objects/regions7
	 *  			get coordinates of each object/region
	 *
	 *
	 *  @param      Binary image
	 *  @param      grayscale image
	 *  @param      Original (non- processed) image frame
	 *  @param      indicate which directory to save separated object/regions images (only effective is last parameter is set to "true"). 0 = darkworld/non-contrasted binary image; 1 = lightworld/contrasted binary image
	 *  @param      vector which will hold x coordinates of each object/region
	 *  @param      vector which will hold y coordinates of each object/region
	 *  @param 		true = save separated objects/regions in directory of your choice
	 *  @return     vector of object/regions
 ****************************************************************************************/
	vector <Mat>  BoundBox(Mat Binary, Mat origanal_image, Mat &Original_image_clone, int world_number, vector<int>& x_coordinate, vector<int>& y_coordinate, vector<Rect> &boundRectWorld, bool save_image_result);


};

#endif /* SEPERATEOBJECTS_H_ */
