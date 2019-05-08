#pragma once
#include "Pre_prossesing.h"



Pre_prossesing::Pre_prossesing()
{
}


Pre_prossesing::~Pre_prossesing()
{
}


cv::Mat Pre_prossesing::bluring(cv::Mat img, int k, int type)
{
	cv::Mat img2 = img;
	int nrOfEl = 0;
	if (type == 1) {
		nrOfEl = k * k;
		//goes from the size of kernel /2, to the size of the image - (size of kernel /2)
		for (int i = k / 2; i < img.rows - (k / 2); i++)
			for (int j = k / 2; j < img.cols - (k / 2); j++)
			{
				int s = 0;
				//sums all the points around the point Point{j,i}, - left or top points, + right or botton points
				for (int ii = -k / 2; ii <= k / 2; ii++)
					for (int jj = -k / 2; jj <= k / 2; jj++)
						s += img.at<uchar>(i + ii, j + jj);
				//finds the average value;
				int c = round(s / (nrOfEl));
				img2.at<uchar>(i, j) = c;

			}
	}
	else if (type == 0) {
		for (int i = k / 2; i < img.rows - (k / 2); i++)
			for (int j = k / 2; j < img.cols - (k / 2); j++)
			{
				int s = 0;
				for (int ii = -k / 2; ii <= k / 2; ii++)
					for (int jj = -k / 2; jj <= k / 2; jj++)
						//checks if the Point{i+ii,j+ii} is in the radius of the middle point Point{i,j}
						if (distance(cv::Point{ i,j }, cv::Point{ i + ii,j + jj }) <= (k / 2)) {
							s += img.at<uchar>(i + ii, j + jj);
							nrOfEl++;
						}
				int c = round(s / (nrOfEl));
				img2.at<uchar>(i, j) = c;

			}
	}

	return img2;

}

float Pre_prossesing::distance(cv::Point point1, cv::Point point2) {

	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}