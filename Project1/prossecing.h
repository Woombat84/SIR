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
	void threshold(void*);
	

private: //Methodes



public: // members
	

private: //members
	int dif = 1;
	std::vector<cv::Point>	my_vector;
	std::vector<std::vector<cv::Point>>  my_contours;
	
};

