
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

cv::Mat Morphology::discKernel(int size) {
	//creates a Mat of Size size full with zeros
	cv::Mat kern = cv::Mat::zeros(size, size, CV_8U);
	int center = size / 2;
	for (int i = 0; i < kern.rows; i++)
		for (int j = 0; j < kern.cols; j++)
			//checks if the point Point{i,j} is in the radius of center point      //because we work in a 2D array, the radius is not float(size / 2.0) (for 3 will be 1.5), but int(size/2) (for 3 will be 1)  
			//if the point is in the radius, then makes the point 1
			if (rob_distance(cv::Point{ center,center }, cv::Point{ i,j }) <= (size / 2))
				kern.at<uchar>(i, j) = 1;

	//if you want to see the kernel uncomment this
	//for (int i = 0; i < kern.rows; i++)
	//{
	//	for (int j = 0; j < kern.cols; j++)
	//		cout << int(kern.at<uchar>(i, j));
	//	cout << endl;
	//}
	return kern;

}

float Morphology::rob_distance(cv::Point point1, cv::Point point2) {

	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}


