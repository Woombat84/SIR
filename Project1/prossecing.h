#pragma once


class prossecing
{
public:  //Methodes
	prossecing();
	~prossecing();

	int isIn(cv::Point myPoint);
	void rob_findCountor(cv::Mat& img, cv::Point myPoint, int tresholdValue);
	void rob_findContours(cv::Mat& img, int treshold);
	void drawImage(cv::Mat& img);
	void greyscale(cv::Mat& img);
	void threshold(cv::Mat& img);
	

private: //Methodes



public: // members
	

private: //members
	int dif = 1;
	int threshThreshold = 60;
	double wr = 0.3;
	double wb = 0.3;
	double wg = 0.3;
	std::vector<cv::Point>	my_vector;
	std::vector<std::vector<cv::Point>>  my_contours;
	
};

