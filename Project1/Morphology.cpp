#include "stdafx.h"
#include "Morphology.h"


Morphology::Morphology()
{
}


Morphology::~Morphology()
{
}

cv::Mat Morphology::Kernel(int Size, int Type) {

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

void Morphology::Erode(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure)
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

void Morphology::Dilate(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure) {


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

<<<<<<< HEAD
				for (int count = 0; count < Structure.rows && Hit; count++) {
					for (int count_2 = 0; count_2 < Structure.cols && Hit; count_2++) {
=======
				for (int count = 0; count < Structure.rows; count++) {
					for (int count_2 = 0; count_2 < Structure.cols; count_2++) {
>>>>>>> d2b66f1d027d82b9d6077d853f73af850725bd2c

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

<<<<<<< HEAD
=======
void Morphology::Opening(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure) {
	cv::Mat Temp = cv::Mat(Input.rows, Input.cols, CV_8UC1);
	Morphology::Erode(Input, Temp, Structure);
	Morphology::Dilate(Temp, Output, Structure);
}

void Morphology::Closing(cv::Mat& Input, cv::Mat& Output, cv::Mat& Structure) {
	cv::Mat Temp = cv::Mat(Input.rows, Input.cols, CV_8UC1);
	Morphology::Dilate(Input, Temp, Structure);
	Morphology::Erode(Temp, Output, Structure);
}

>>>>>>> d2b66f1d027d82b9d6077d853f73af850725bd2c
