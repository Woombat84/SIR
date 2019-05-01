/*
%
% This Header Cpp files Prossecing is used to prossecing the image from the 
% Intel RealSense d435i.
%
% Author1: 19gr466
%
% Date : Spring 2019
% Course : Rob4 Computervision
%
*/

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


//this template is a template for + operation for vectors
// <T> means every type 
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
		if (find(my_contours[i].begin(), my_contours[i].end(), myPoint) != my_contours[i].end())  //find function takes as arguments first element from a vector, the index of the last one and the item to search 
			return 1;
	return 0;
}

std::vector<std::vector<cv::Point>> prossecing::rob_findContours(cv::Mat img, int treshold)

{
	//	img = contrast(img, 1);
	std::vector<cv::Point> anotherVector;
	cv::imshow("Frame", img);
	//this part goes throw the image
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols - 1; j++)
			//if finds 2 near pixels that have the intensity difference bigger or equal to treshold and that pixel is not in the my_contours, then it begins to find the contours from that point
			if ((abs(img.at<uchar>(i, j + 1) - img.at<uchar>(i, j)) >= treshold) && !isIn(cv::Point(j, i)))
			{
				rob_findCountor(img, cv::Point(j, i), treshold);
				//I copy my result boundary vector to another one and add it to the list of boundaries "my_contours"
				anotherVector = my_vector;
				my_contours.push_back(anotherVector);
				my_vector.clear();
			}

	return my_contours;
}



void prossecing::rob_findCountor(cv::Mat img, cv::Point myPoint,int tresholdValue)

{
	//	Point newPoint;
	//this is the coefficient that shows how many pixel distance to search from the given pixel for another boundary pixel
	int dif = 1;
	// adds the point given to the boundary vector
	my_vector.push_back(myPoint);
	//checks if the given point has at least "dif" points distance in every direction
	if ((myPoint.x >= dif || myPoint.x < img.cols - dif) && (myPoint.y >= dif || myPoint.y < img.rows - dif))
	{
		//goes around the given point and search for any near boundary point
		for (int i = -dif; i <= dif; i++)
			for (int j = -dif; j <= dif; j++)
			{
				cv::Point newPoint{ myPoint.x + i, myPoint.y + j };

				//if it finds one then it goes in the same function with the founded point
				if ((abs(img.at<uchar>(newPoint) - img.at<uchar>(myPoint)) >= tresholdValue) && (find(my_vector.begin(), my_vector.end(), newPoint) == my_vector.end()))
					rob_findCountor(img, newPoint, tresholdValue);
			}
	}
}


void prossecing::drawImage(cv::Mat img, std::vector<std::vector<cv::Point>> myContours)
{
//	makes the  image white
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			img.at<cv::Vec3b>(i, j) = cv::Vec3b{ 255,255,255 };

	int s = myContours.size();
	//draws the contours in red
	for (int i = 0; i < s; i++)
		for (int j = 0; j < myContours[i].size(); j++)
			img.at<cv::Vec3b>(myContours[i][j]) = cv::Vec3b{ 0,0,255 };


	imshow("bound", img);

}
/*
% Function : Coloured to greyscaled image.
%
% Description : This function converts a coloured image to a greyscaled image(B/W)
%
%
% Parameters : An image .
%
% Return : A openCV Mat.
%
*/

cv::Mat prossecing::greyscale(cv::Mat &img) {
	
	cv::Mat newImg = cv::Mat(img.rows,img.cols, CV_8UC1);
	for (int y = 0; y <= img.rows-1; y++) {
		for (int x = 0; x <= img.cols-1; x++) {
			
			 newImg.at<uchar>(y, x) = wr * img.at<cv::Vec3b>(y, x)[0] + wg * img.at<cv::Vec3b>(y, x)[1] + wb * img.at<cv::Vec3b>(y, x)[2];//weight
			
		}
	}
	return newImg;

}
/*
% Function : Greyscale to binary.
%
% Description : This function converts a greyscale image to a binary image(B/W)
%				Inverting so the object is with an background becomes black
%				tested at 245 works well with wite background
%
% Parameters : An image and a threshold.
%
% Return : Binary Mat.
%
*/
cv::Mat prossecing::threshold(cv::Mat& Old, int binaryThreshold)
{
	cv::Mat New = cv::Mat(Old.rows, Old.cols, CV_8UC1);
	for (int y = 0; y < Old.rows; y++) {
		for (int x = 0; x < Old.cols; x++) {
			if (Old.at <int8_t>(y, x) < binaryThreshold) {
				New.at<int8_t>(y, x) = 255;
			}
			else {
				New.at<int8_t>(y, x) = 0;
			}
		}
	}
	return New;
}


cv::Mat prossecing::rob_bluring(cv::Mat img, int k, int type)
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
						if (rob_distance(cv::Point{ i,j }, cv::Point{ i + ii,j + jj }) <= (k / 2)) {
							s += img.at<uchar>(i + ii, j + jj);
							nrOfEl++;
						}
				int c = round(s / (nrOfEl));
				img2.at<uchar>(i, j) = c;

			}
	}

	return img2;

}




/*
% Function : Gather all blobs .
%
% Description : This function runs thrugh the image until it findes a undeteted blob.
%				A helper function to run thruohg each blob is created called blobRecursiv.
%
%
% Parameters : An image.
%
% Return : A vector of vectors of points.
%
*/
std::vector<std::vector<cv::Point>> prossecing::blob(cv::Mat img)
{
	cv::Mat blobdet = cv::Mat(img.rows, img.cols, CV_8UC1);
	blobdet = img;
	int counterVec = 0;
	for (int y = 0; y < blobdet.rows; y++) {
		for (int x = 0; x < blobdet.cols; x++) {
			if (blobdet.at<int8_t>(y, x) == BitValue) {} //std::cout<< "NOT: " << x << "," << y << std::endl; }
			else {
				noPixLeft = false;
				//std::cout <<"in"<< std::endl;
				blobRecursiv(blobdet, x, y);
				counterVec++;
				std::cout << "vector size of number " << counterVec << ": " << blob_vector.size() << std::endl;

				Blobs_detected.push_back(blob_vector);
				blob_vector.clear();
			}

		}
	}
	return Blobs_detected;
}


/*
% Function : Recursive storing of points in a blob .
%
% Description : This function is deteting all pixels in a blob and stor them 
%				in a vetor.
%
% Parameters : An image, x and y coordinates.
%
% Return : nonthing.
%
*/
void prossecing::blobRecursiv(cv::Mat& blobNew, int x, int y) {
	
	//Using the cross mention in the grassfire algo
	//First burning the pixel that the cross lands on
	if (blobNew.at<uchar>(y, x) != 0) {
		blobNew.at<uchar>(y, x) = 0;
		//Storing the point in a a vector.
		blob_vector.push_back(cv::Point{ x, y });
	}
	while (noPixLeft == false){
		//When the max number of recusive function are reached the x,y coordinate has to be stored 
		//A holder is set to true to itorate back througe the functions
		if (counterBlob >= maxCounterBlob) {	
			countX = x;
			countY = y;
			counterBlob--;
			maxCounter = true;
			return;
		}
		//this goes back the recurecive function until x is left
		if (counterBlob >=750 && maxCounter == true) {
			counterBlob--;
			return;
		}
		//this releases the hold maxCounter add set the the new x,y coordinates
		if (counterBlob <=750 && maxCounter == true) {	
			x = countX;
			y = countY;
			maxCounter = false;
		}
		//Looking at the arms in this order: left,up, right, down.
		//Looking left 
		if (blobNew.at<uchar>(y, x - 1) > BitValue && maxCounter == false) {
			//std::cout << "Looking left: " << x - 1 << " , " << y << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x - 1, y);
		}
		//Looking up
		if (blobNew.at<uchar>(y - 1, x)> BitValue && maxCounter == false) {
			//std::cout << "Looking up: " << x << " , " << y - 1 << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x, y - 1);
		}
		//Looking right
		if (blobNew.at<uchar>(y, x + 1) > BitValue && maxCounter == false) {
			//std::cout << "Looking r" << x + 1 << " , " << y << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x + 1, y);
		}
		//Looking down	
		if (blobNew.at<uchar>(y + 1, x) > BitValue && maxCounter == false) {
			//std::cout << "Looking down: " << x << " , " << y + 1 << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x, y + 1);
		}
		else{
			counterBlob--; 
			return;
		}
	}	
}



float prossecing::rob_distance(cv::Point point1, cv::Point point2) {

	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}


/*
% Function :setting a threshold for binary image.
%
% Description : running through the new f(x,y) contra the old and setting a percentage for thresholding.
%
% Parameters : An image, x and y coordinates + a float "V" to set how many percentages we want.
%
% Return : nothing.
%
*/
void prossecing::binaryThreshold(cv::Mat& old, float V)
{
	int old_value = 0;
	int count=0;
	for (int y = 0; y < old.rows; y++) {
		for (int x = 0; x < old.cols; x++) {

			old_value = (old.at <int8_t>(y, x) + old_value);
			count++;
			

		}

	}
	float percent = (old_value / count) * 100;

	int percentValue = percent * V;
	
	return;
	
}