#pragma once



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


	// it is a  recursive function that check if any of the neighbours of the Point myPoint has a 
	void rob_findCountor(cv::Mat img, cv::Point myPoint, int tresholdValue);

	// its the function that finds the contours
	vector<vector<Point>> rob_findContours(cv::Mat img, int treshold);


	//draws the conours
	void drawImage(cv::Mat img, vector<vector<Point>> myContours);
	void greyscale(cv::Mat& img);
	void threshold(cv::Mat& img); 
	Mat rob_bluring(Mat img, int k);
	Mat rob_dilation(Mat img, int k);
	Mat rob_erosion(Mat img, int k);

	

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

