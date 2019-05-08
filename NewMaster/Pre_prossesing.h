#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
class Pre_prossesing
{
public: //Methodes
	Pre_prossesing();
	~Pre_prossesing();
	cv::Mat bluring(cv::Mat img, int k, int type);// Input image, size of the kernel k and type (Either 1 or 0)

	float distance(cv::Point point1, cv::Point point2); //Used to calculate the distance between two points


private: //Methodes



public: //Members



private:  //Members





};

