#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>


class prossecing
{
public:  //Methodes
	prossecing();
	~prossecing();

	int isIn(cv::Point myPoint);
	void rob_findCountor(cv::Mat& img, cv::Point myPoint, int tresholdValue);
	void rob_findContours(cv::Mat& img, int treshold);
	void drawImage(cv::Mat& img);
	cv::Mat greyscale(cv::Mat& img);
	cv::Mat threshold(cv::Mat& Old, int binaryThreshold);
	

	std::vector<std::vector<cv::Point>> blob(cv::Mat& img);

	void blobRecursiv(cv::Mat& blob, int x, int y);
	

private: //Methodes



public: // members
	

private: //members
	int dif = 1;
	int threshThreshold = 60;
	double wr = 0.3;
	double wb = 0.4;
	double wg = 0.3;
	int8_t BitValue = 0;
	std::vector<cv::Point>	my_vector;
	std::vector<std::vector<cv::Point>>  my_contours;
	std::vector<cv::Point> blob_vector;
	std::vector<std::vector<cv::Point>> Blobs_detected;
};

