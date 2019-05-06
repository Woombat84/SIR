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

float feature::BoundingCircle(std::vector<cv::Point> BLOB, int Height, int Width)
{
	//Find the centre of the BLOB
	int xAvr = 0;
	int yAvr = 0;
	for (int i = 0; i < BLOB.size(); i++) {
		xAvr += BLOB[i].x;
		yAvr += BLOB[i].y;
	}
	xAvr = xAvr / BLOB.size(); //Centre x-coordinate
	yAvr = yAvr / BLOB.size(); //Centre y-coordinate

	//Create the BLOB in a new Matrix
	cv::Mat Calc = cv::Mat::zeros(Height, Width, CV_8UC1);

	for (int i = 0; i < BLOB.size(); i++) {
		Calc.at<uchar>(BLOB[i].y, BLOB[i].x) = 255;
	}

	//find radii with 15deg intervals

	float Radius = 0;
	float TempRadius = 0;
	int pointX = xAvr;
	int pointY = yAvr;

	//Cosine right
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Up
		if (Degrees[i] >= 0) {
			for (int r = 1; r < Width - xAvr && yAvr - (r*Degrees[i]) > 0; r++) {
				if (Calc.at<uchar>(yAvr - (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr - (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
		//Down
		else {
			for (int r = 1; r < Width - xAvr && (-r * Degrees[i]) < Height - yAvr; r++) {
				if (Calc.at<uchar>(yAvr - (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr - (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}


	//Sine down
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Right
		if (Degrees[i] >= 0) {
			for (int r = 1; r < Height - yAvr && (r*Degrees[i]) < Width - xAvr; r++) {
				if (Calc.at<uchar>(yAvr + r, xAvr + (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
		//Left
		else {
			for (int r = 1; r + yAvr < Height && xAvr + (r * Degrees[i]) > 0; r++) {
				if (Calc.at<uchar>(yAvr + r, xAvr + (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}



	//Cosine left
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Up
		if (Degrees[i] >= 0) {
			for (int r = -1; xAvr + r > 0 && yAvr + (r*Degrees[i]) > 0; r--) {
				if (Calc.at<uchar>(yAvr + (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}

		//Down
		else {
			for (int r = -1; xAvr + r > 0 && (r * Degrees[i]) < Height - yAvr; r--) {
				if (Calc.at<uchar>(yAvr + (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}

	//Sine up
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Right
		if (Degrees[i] >= 0) {
			for (int r = -1; yAvr + r > 0 && (-r * Degrees[i]) < Width - xAvr; r--) {
				if (Calc.at<uchar>(yAvr + r, xAvr - (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
		//Left
		else {
			for (int r = -1; yAvr + r > 0 && xAvr - (r * Degrees[i]) > 0; r--) {
				if (Calc.at<uchar>(yAvr + r, xAvr - (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr - (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}

	return Radius;
}



