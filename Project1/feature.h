#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

class feature
{
public:// methodes
	feature();
	~feature();
	
	
	std::vector<cv::Point> perimeterBlob(cv::Mat& img, int x, int y);

	float BlobCircularity(int BlobArea, int BlobPerimeter);



private:// methodes

public:// members
	std::vector<std::vector<cv::Point>> Perimetor;


private:// members
	//variabels for perimeter	

	std::vector<cv::Point> perimeterVector;

	# define PI 3.14159

};

