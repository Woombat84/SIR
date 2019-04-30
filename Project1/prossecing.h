#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>



using namespace std;
using namespace cv;
class prossecing
{
public:  //Methodes
	prossecing();
	~prossecing();

	//this function checks if the Point myPoint is in the my_contours already
	// returns 1 if yes and 0 if no
	int isIn(cv::Point myPoint);
<<<<<<< HEAD
	void rob_findCountor(cv::Mat& img, cv::Point myPoint, int tresholdValue);
	void rob_findContours(cv::Mat& img, int treshold);
	void drawImage(cv::Mat& img);
	cv::Mat greyscale(cv::Mat& img);
	cv::Mat threshold(cv::Mat& Old, int binaryThreshold);
	

	std::vector<std::vector<cv::Point>> blob(cv::Mat img);

	void blobRecursiv(cv::Mat& blob, int x, int y);
=======


	// it is a  recursive function that check if any of the neighbours of the Point myPoint has a 
	void rob_findCountor(cv::Mat img, cv::Point myPoint, int tresholdValue);

	// its the function that finds the contours
	vector<vector<Point>> rob_findContours(cv::Mat img, int treshold);


	//draws the conours
	void drawImage(Mat img, vector<vector<Point>> myContours);
	void greyscale(cv::Mat& img);
	void threshold(cv::Mat& img); 
	Mat rob_bluring(Mat img, int k);
	Mat rob_dilation(Mat img, int k);
	Mat rob_erosion(Mat img, int k);

>>>>>>> Mihai
	

private: //Methodes



public: // members
	

private: //members
	int dif = 1;
	int threshThreshold = 60;
	double wr = 0.3;
	double wb = 0.4;
	double wg = 0.3;
	int8_t BitValue = 0;
	std::vector<cv::Point>	my_vector;
	std::vector<std::vector<cv::Point>>  my_contours;
	std::vector<std::vector<cv::Point>> Blobs_detected;
	//variabels for blob detection
	std::vector<cv::Point> blob_vector;
	int counterBlob = 0;
	int maxCounterBlob =2000;
	int countX = 0;
	int countY = 0;
	bool maxCounter = false;
	bool noPixLeft = false;
	
	
};

