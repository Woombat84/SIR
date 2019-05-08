#include "feature.h"
#include <vector>



feature::feature()
{
}


feature::~feature()
{
}


/*
% Function : perimeterBlob.
%
% Description : This function findes the edges through the use of grass fire algorithem
%
%
% Parameters : An image, x and y coordinates.
%
% Return : nonthing.
%
*/
std::vector<cv::Point> feature::perimeterBlob(cv::Mat& img, int x, int y) {

	std::vector<cv::Point> v;
	bool end = false;
	int startX = x;
	int startY = y + 1;
	int xx = x;
	int yy = y;
	int endX = 0;
	int endY = 0;
	v.push_back(cv::Point{ xx, yy });
	std::cout << "start  : " << startX << " : " << startY << std::endl;
	while (end == false) {

		//Looking up, in a 9 x9 squrea top left pixel have to be black and the top middel have to be white
		if (img.at<uchar>(yy, xx - 1) == 0 && img.at<uchar>(yy - 1, xx) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			yy--; //moving up in the image
			endX = xx;
			endY = yy;
			//std::cout << "up   : " << xx << " : " << yy <<  std::endl;
			//std::cout << "up x : "<< endX << "  Y: "<< endY<< std::endl;
			//std::cout << "en x : " << startX << "  Y: " << startY << std::endl;
			if (startX == endX && startY == endY) {
				std::cout << "drop out" << std::endl;
				v.push_back(cv::Point{ xx, yy });

				return v;
			}
		}
		//Looking right, in a 9 x9 squrea top right pixel have to be black and the middel right have to be white
		if (img.at<uchar>(yy - 1, xx) == 0 && img.at<uchar>(yy, xx + 1) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			xx++; //moving right in the image
			endX = xx;
			endY = yy;
			if (startX == endX && startY == endY) {
				std::cout << "drop out" << std::endl;
				v.push_back(cv::Point{ xx, yy });

				return v;
			}
			//std::cout << "right: " << xx <<" : " << yy << std::endl;
		}
		//Looking down, in a 9 x9 squrea bottum right pixel have to be black and the bottum middel have to be white
		if (img.at<uchar>(yy, xx + 1) == 0 && img.at<uchar>(yy + 1, xx) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			yy++;	//moving down in the image
			endX = xx;
			endY = yy;
			//std::cout << "down : " << xx << " : " << yy << std::endl;
		}
		//Looking left, in a 9 x9 squrea bottum left pixel have to be black and the middel left have to be white
		if (img.at<uchar>(yy + 1, xx) == 0 && img.at<uchar>(yy, xx - 1) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			xx--;	//moving left in the image
			endX = xx;
			endY = yy;
			//std::cout << "left : " << xx << " : " << yy << std::endl;
		}
	}
}

float feature::BlobCircularity(int BlobArea, int BlobPerimeter)
{
	float Circularity = (4 * PI * BlobArea) / (BlobPerimeter * BlobPerimeter);
	return Circularity;
}



