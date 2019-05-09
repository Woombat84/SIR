#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include <vector>
class feature
{
public:// methodes
	feature();
	~feature();
	
	


	int perimeterBlob(std::vector<cv::Point> BLOB, int Height, int Width, std::vector<cv::Point>& v);//blob vector , height and width of image, a vector to hold perimeter

	float BlobCircularity(int BlobArea, double BlobPerimeter);	// area of the blob and the perimeter of the blob

	float BoundingCircle(std::vector<cv::Point> BLOB, int Height, int Width);//blob vector , height and width of image


	std::vector<cv::Point> BoundingBox(std::vector<cv::Point> perimeter);// perimeter vector 

	float HeightWitdh(std::vector<cv::Point> v);//perimeter vector

	float compactness(std::vector<cv::Point> v, int area);//perimeter vector , area

	int area(std::vector<cv::Point>);//vector of BoundingBox



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

