#pragma once
#include "Segmentation.h"



Segmentation::Segmentation()
{
}


Segmentation::~Segmentation()
{
}

int Segmentation::percent(cv::Mat img, float V) {

	const int HistSize = 256; //Size of histogram 
	int histogram[HistSize] = { 0 }; //Initializing histogram to 0
	bool check = true;	//bool used for ending loop when threshold is found
	float accumulate = 0.0f; // Value for finding threshold
	int pixels = img.rows*img.cols; //Amount of pixels in image
	int thresh = 0; //Calculated threshold

	for (int x = 0; x < img.cols; x++) { 
		for (int y = 0; y < img.rows; y++) {
			histogram[img.at<uchar>(y, x)] += 1; //Add every pixel to the histogram
		}
	}
	
	for (; check && thresh<HistSize; thresh++) {
		if (accumulate > 1.0 - V) { //Check if percentage has been found
			check = false;			// if found end loop
		}
		else {
			accumulate += (float)(histogram[thresh]) / (float)(pixels); //If not found add amount of pixels from next bin in histogram
		}
	}

	return thresh;
}

void Segmentation::Threshold(cv::Mat& img, int Threshold, int TopBot) {
	if (TopBot = 0) {
		for (int x = 0; x < img.cols; x++) {
			for (int y = 0; y < img.rows; y++) {
				if (img.at <uchar>(y, x) > Threshold) { //If value is above threshold make white
					img.at<uchar>(y, x) = 0;
				}
				else {
					img.at<uchar>(y, x) = 255; //Otherwise make pixel black
				}
			}
		}
	}
	else if (TopBot = 1) {
		for (int x = 0; x < img.cols; x++) {
			for (int y = 0; y < img.rows; y++) {
				if (img.at <uchar>(y, x) > Threshold) { //If value is above threshold make white
					img.at<uchar>(y, x) = 255;
				}
				else {
					img.at<uchar>(y, x) = 0; //Otherwise make pixel black
				}
			}
		}
	}
}

cv::Mat Segmentation::Kernel(int Size, int Type) {

	cv::Mat Kern = cv::Mat::ones(Size, Size, CV_8U);

	if (Type == 0) { //Create a disk
		if (Size == 3 || Size == 5 || Size == 7) {

			switch (Size) {
			case 3:
				Kern.at<uchar>(0, 0) = 0;
				Kern.at<uchar>(2, 0) = 0;
				Kern.at<uchar>(0, 2) = 0;
				Kern.at<uchar>(2, 2) = 0;
				break;
			case 5:
				Kern.at<uchar>(0, 0) = 0;
				Kern.at<uchar>(1, 0) = 0;
				Kern.at<uchar>(3, 0) = 0;
				Kern.at<uchar>(4, 0) = 0;
				Kern.at<uchar>(0, 1) = 0;
				Kern.at<uchar>(4, 1) = 0;
				Kern.at<uchar>(0, 3) = 0;
				Kern.at<uchar>(4, 3) = 0;
				Kern.at<uchar>(0, 4) = 0;
				Kern.at<uchar>(1, 4) = 0;
				Kern.at<uchar>(3, 4) = 0;
				Kern.at<uchar>(4, 4) = 0;
				break;
			case 7:
				Kern.at<uchar>(0, 0) = 0;
				Kern.at<uchar>(1, 0) = 0;
				Kern.at<uchar>(2, 0) = 0;
				Kern.at<uchar>(4, 0) = 0;
				Kern.at<uchar>(5, 0) = 0;
				Kern.at<uchar>(6, 0) = 0;

				Kern.at<uchar>(0, 1) = 0;
				Kern.at<uchar>(1, 1) = 0;
				Kern.at<uchar>(5, 1) = 0;
				Kern.at<uchar>(6, 1) = 0;

				Kern.at<uchar>(0, 2) = 0;
				Kern.at<uchar>(6, 2) = 0;

				Kern.at<uchar>(0, 4) = 0;
				Kern.at<uchar>(6, 4) = 0;

				Kern.at<uchar>(0, 5) = 0;
				Kern.at<uchar>(1, 5) = 0;
				Kern.at<uchar>(5, 5) = 0;
				Kern.at<uchar>(6, 5) = 0;

				Kern.at<uchar>(0, 6) = 0;
				Kern.at<uchar>(1, 6) = 0;
				Kern.at<uchar>(2, 6) = 0;
				Kern.at<uchar>(4, 6) = 0;
				Kern.at<uchar>(5, 6) = 0;
				Kern.at<uchar>(6, 6) = 0;
				break;
			}
			return Kern;
		}
		else {
			return cv::Mat::ones(1, 1, CV_8U); //If improper Size is chosen 
		}
	}
	else if (Type == 1) {
		return Kern;
	}
	else {
		return cv::Mat::ones(1, 1, CV_8U);; //If improper Type is chosen
	}

}

void Segmentation::Erode(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure)
{
	bool Fit; //Used for checking if the Structure fits to the Input
	int centreX = Structure.rows / (2.0); //Center of Structure
	int centreY = Structure.cols / (2.0); //Center of Structure

										  //Starting point at a distance from the border equal to the center of the Structure
	for (int x = centreX; x < Input.rows - centreX; x++) {
		for (int y = centreY; y < Input.cols - centreY; y++) {
			Fit = true;
			if (Input.at<uchar>(x, y)) // only runs if the starting position is non-zero
			{
				for (int count = 0; count < Structure.rows && Fit; count++) {
					for (int count_2 = 0; count_2 < Structure.cols && Fit; count_2++) {

						//If the Input is 0 and the Structure is 1 Fit is false and sets the Fit to false to eliminate this pixel.
						if (Input.at<uchar>(x - centreX + count, y - centreY + count_2) == 0 &&
							Structure.at<uchar>(count, count_2) == 1) {
							Output.at<uchar>(x, y) = 0;
							Fit = false;
						}
					}
				}
				//If fit is still true, then the pixel is valid and is set to white
				if (Fit)
					Output.at<uchar>(x, y) = 255;
			}
			// if the pixel what 0 then it stays 0 in the new Input.
			else
				Output.at<uchar>(x, y) = 0;
		}
	}
}

void Segmentation::Dilate(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure) {


	bool Hit; //Used for checking if the Structure hits to the Input
	int centreX = Structure.rows / (2.0); //Center of Structure
	int centreY = Structure.cols / (2.0); //Center of Structure

		//Starting point at a distance from the border equal to the center of the Structure
	for (int x = centreX; x < Input.rows - centreX; x++) {
		for (int y = centreY; y < Input.cols - centreY; y++) {
			Hit = false;
			if (Input.at<uchar>(x, y)) { //check if centre point is white
				//Output.at<uchar>(x, y) = 255;
				Hit = true;
			}
			else {


				for (int count = 0; count < Structure.rows; count++) {
					for (int count_2 = 0; count_2 < Structure.cols; count_2++) {

						if (Hit) {} // if we found a hit previously, don't do more for this pixel
						else if (Input.at<uchar>(x - centreX + count, y - centreY + count_2) &&
							Structure.at<uchar>(count, count_2)) { //Check if other pixel in kernel hits a white
							//Output.at<uchar>(x, y) = 255;
							Hit = true;
						}
					}
				}
			}
			if (Hit) {
				Output.at<uchar>(x, y) = 255;
			}
			else {
				Output.at<uchar>(x, y) = 0;
			}
		}
	}
}


void Segmentation::Opening(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure) {
	cv::Mat Temp = cv::Mat(Input.rows, Input.cols, CV_8UC1);
	Segmentation::Erode(Input, Temp, Structure);
	Segmentation::Dilate(Temp, Output, Structure);
}

void Segmentation::Closing(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure) {
	cv::Mat Temp = cv::Mat(Input.rows, Input.cols, CV_8UC1);
	Segmentation::Dilate(Input, Temp, Structure);
	Segmentation::Erode(Temp, Output, Structure);
}

cv::Mat Segmentation::Cropping(cv::Mat& Input, int size)
{
	cv::Mat Cropped = cv::Mat((Input.rows - size*2), (Input.cols - size*2), CV_8UC1); //Creates a new image in the size of the cropped

	for (int y = 0; y < Cropped.cols; y++) {
		for (int x = 0; x < Cropped.rows; x++) {
			Cropped.at<uchar>(x , y) = Input.at<uchar>(x+size, y+size); //Inputs the new pixel value into the cropped image
			if (x == 0 || y == 0 || y == Cropped.cols-1 || x == Cropped.rows-1) {
				Cropped.at<uchar>(x, y) = 0;
			}
		}
	}

	return Cropped;
}
