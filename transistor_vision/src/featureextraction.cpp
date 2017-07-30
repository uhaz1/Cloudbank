/*
 * featureextraction.cpp
 *
 *  Created on: 24 Jul 2017
 *      Author: sheun
 */

#include "featureextraction.h"

feature_extraction::feature_extraction() {
	// TODO Auto-generated constructor stub

}

feature_extraction::~feature_extraction() {
	// TODO Auto-generated destructor stub
}

vector< vector<KeyPoint> > feature_extraction::featurePoints(vector<Mat> images,int world_number)
{

	vector<Mat> images_clone = images;
	int minHessian = 400;
	Ptr<SIFT> detector = SIFT::create(minHessian);
	vector<KeyPoint> keypoints_hold_1_image;
	vector< vector<KeyPoint> > keypoints;
	char file [100];
	int lock_dark_file = 0;
	int lock_light_file = 0;
	Mat img_keypoints_1;
	//
	//
	for(uint32_t i = 0; i < images.size(); i++)
	{

		detector->detect(images_clone[i], keypoints_hold_1_image);
		keypoints.push_back(keypoints_hold_1_image);

		//Draw keypoints
		drawKeypoints(images_clone[i], keypoints[i], img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
		//save regions of interest into a folder
		if (world_number == 0)
		{
			if (lock_dark_file == 0) {system("exec rm -r ../../trasistor_vision_darkFeatures_images/*");lock_dark_file++; }
			sprintf(file,"../../trasistor_vision_darkFeatures_images/Image%d.jpg",i);
		}
		else if(world_number == 1)
		{
			if (lock_light_file == 0) {system("exec rm -r ../../trasistor_vision_lightFeatures_images/*");lock_light_file++; }
			sprintf(file,"../../trasistor_vision_lightFeatures_images/Image%d.jpg",i);
		}

		imwrite(file,img_keypoints_1);

	}


 return keypoints;
}

