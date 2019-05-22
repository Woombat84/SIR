#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iterator> 
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "BlobFeatures.h"
#include "feature.h"
#include <algorithm>
#include <map>
class Test
{
public:
	Test();
	~Test();


	void training(cv::Mat& img, cv::Mat& srcC, std::vector<std::vector<cv::Point>> Blobs, std::string Classifier, std::vector<BlobFeatures> vector);

	

	void loadData(std::vector<BlobFeatures>& pipeVec, std::vector<BlobFeatures>& obsVec);
	
	
private:

		std::string DistanceCalc(std::vector<BlobFeatures> vector, BlobFeatures feat);
		
		std::string knearest(std::vector<DistFeatures> v);

	

		int Kneighbors = 11;
	
		
	

	



	

	

	


};

