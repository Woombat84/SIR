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
	
	
	int perimeterBlob(std::vector<cv::Point> BLOB, int Height, int Width);

	float BlobCircularity(int BlobArea, double BlobPerimeter);

	float BoundingCircle(std::vector<cv::Point> BLOB, int Height, int Width);



private:// methodes

public:// members
	std::vector<std::vector<cv::Point>> Perimetor;


private:// members
	//variabels for perimeter	

	std::vector<cv::Point> perimeterVector;

	# define PI 3.14159

	float Degrees[9] = { 0.839099631, 0.577350269, 0.363970234,
			0.176326981, 0, -0.176326981,-0.363970234,
			-0.577350269,-0.839099631 }; // Used for calculating the bounding circle

};

