#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iterator> 
#include <iostream>
#include <fstream>
#include <sstream>
#include "BlobFeatures.h"
#include "feature.h"
class Test
{
public:
	Test();
	~Test();

	void run(cv::Mat img, cv::Mat srcC, std::vector<std::vector<cv::Point>>& Blobs);


};

