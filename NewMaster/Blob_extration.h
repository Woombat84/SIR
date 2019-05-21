#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include "feature.h"
#include <iostream>

class Blob_extration
{
public: //methodes
	Blob_extration();
	~Blob_extration();

	std::vector<std::vector<cv::Point>> blob(cv::Mat img);

	void blobRecursiv(cv::Mat& blobNew, int x, int y);
private: //methodes


public: //members


private: //members


	//variabels for blob detection
	std::vector<std::vector<cv::Point>> Blobs_detected;
	std::vector<cv::Point> blob_vector;

	int counterBlob = 0;
	int maxCounterBlob = 2000;
	int countX = 0;
	int countY = 0;
	bool maxCounter = false;
	bool noPixLeft = false;
	int BitValue = 0;
	int MinBlobSize = 100;
	int MaxBlobSize = 10000;
};

