#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Morphology
{
public:
	Morphology();
	~Morphology();
	cv::Mat Kernel(int Size, int Type); //Creates a structuring element for Morphology - Size is 3,5 or 7 and type is 0 for circle and 1 for square
	void Erode(cv::Mat & Input, cv::Mat & Output, cv::Mat & Structure);//Erodes Input to a new Output using the struturing element
	void Dilate(cv::Mat & Input, cv::Mat & Output, cv::Mat & Structure);//Dilate  Input to a new Output using the struturing element
	void Opening(cv::Mat & Input, cv::Mat & Output, cv::Mat & Structure);//Performs an opening operation to Input in the Ouput matrix with Struturing element
	void Closing(cv::Mat & Input, cv::Mat & Output, cv::Mat & Structure);//Performs a closing operation to Input in the Ouput matrix with Struturing element
	
};

