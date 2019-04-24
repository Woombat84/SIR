#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include "prossecing.h"



prossecing::prossecing()
{
}


prossecing::~prossecing()
{
}



template <typename T>
std::vector<T>operator+(const std::vector<T> &A, const std::vector<T> &B)
{
	std::vector<T> AB;
	AB.reserve(A.size() + B.size());                // preallocate memory
	AB.insert(AB.end(), A.begin(), A.end());        // add A;
	AB.insert(AB.end(), B.begin(), B.end());        // add B;
	return AB;
}

int prossecing::isIn(cv::Point myPoint)
{
	for (int i = 0; i < my_contours.size(); i++)
		if (find(my_contours[i].begin(), my_contours[i].end(), myPoint) != my_contours[i].end())
			return 1;
	return 0;
}

void prossecing::rob_findContours(cv::Mat &img, int treshold)

{
	//	img = contrast(img, 1);
	std::vector<cv::Point> anotherVector;
	cv::imshow("Frame", img);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols - 1; j++)
			if ((abs(img.at<uchar>(i, j + 1) - img.at<uchar>(i, j)) >= treshold) && !isIn(cv::Point(j, i)))
			{
				rob_findCountor(img, cv::Point(j, i), treshold);
				anotherVector = my_vector;
				my_contours.push_back(anotherVector);
				my_vector.clear();
			}

}



void prossecing::rob_findCountor(cv::Mat &img, cv::Point myPoint,int tresholdValue)

{
	//	Point newPoint;
	
	my_vector.push_back(myPoint);
	if ((myPoint.x >= dif || myPoint.x < img.cols - dif) && (myPoint.y >= dif || myPoint.y < img.rows - dif))
	{
		for (int i = -dif; i <= dif; i++)
			for (int j = -dif; j <= dif; j++)
			{
				cv::Point newPoint{ myPoint.x + i, myPoint.y + j };

				if ((abs(img.at<uchar>(newPoint) - img.at<uchar>(myPoint)) >= tresholdValue) && (find(my_vector.begin(), my_vector.end(), newPoint) == my_vector.end()))
					rob_findCountor(img, newPoint, tresholdValue);
			}
	}
}


void prossecing::drawImage(cv::Mat &img)
{
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			img.at<cv::Vec3b>(i, j) = cv::Vec3b{ 255,255,255 };

	int s = my_contours.size();
	for (int i = 0; i < s; i++)
		for (int j = 0; j < my_contours[i].size(); j++)
			img.at<cv::Vec3b>(my_contours[i][j]) = cv::Vec3b{ 0,0,255 };


	imshow("bound", img);

}


void prossecing::greyscale(cv::Mat &img) {

	cv::Mat newImg = cv::Mat(img.rows, img.cols, CV_8UC1);

	for (int x = 0; x < img.cols; x++) {//sætter x og y værdierne
		for (int y = 0; y < img.rows; y++) {
			 newImg.at<uchar>(y, x) = wr * img.at<cv::Vec3b>(y, x)[0] + wg * img.at<cv::Vec3b>(y, x)[0] + wb * img.at<cv::Vec3b>(y, x)[0];//weight
			
		}
	}

}

void prossecing::threshold(cv::Mat& img)
{
}


