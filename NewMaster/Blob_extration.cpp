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
#include "Blob_extration.h"



Blob_extration::Blob_extration()
{
}


Blob_extration::~Blob_extration()
{
}


/*
% Function : Gather all blobs .
%
% Description : This function runs thrugh the image until it findes a undeteted blob and
%				the perimetor.
%				A helper function to run thruohg each blob is created called blobRecursiv.
%				Another helper function called perimeterBlob is use to find the egdes of the blob.
%
% Parameters : An image.
%
% Return : A vector of vectors of points.
%
*/
std::vector<std::vector<cv::Point>> Blob_extration::blob(cv::Mat img)
{
	//Declaring a new image to blob detection
	cv::Mat blobdet = cv::Mat(img.rows, img.cols, CV_8UC1);
	for (int y = 0; y < blobdet.rows; y++) {
		for (int x = 0; x < blobdet.cols; x++) {
			blobdet.at<uchar>(y, x) = img.at<uchar>(y, x);

		}
	}
	//Declaring a new image to find the egde"perimetor" of the blob
	cv::Mat primdet = cv::Mat(img.rows, img.cols, CV_8UC1);
	for (int y = 0; y < primdet.rows; y++) {
		for (int x = 0; x < primdet.cols; x++) {
			primdet.at<uchar>(y, x) = img.at<uchar>(y, x);

		}
	}
	// variabel to use in debugging for how many blobs in the frame
	int counterVec = 0;

	//Looking for the first whit pixel in the frame
	for (int y = 0; y < blobdet.rows; y++) {
		for (int x = 0; x < blobdet.cols; x++) {
			if (blobdet.at<int8_t>(y, x) == BitValue) {} //std::cout<< "NOT: " << x << "," << y << std::endl; }
			else {

				int yy = y;
				int xx = x;
				//std::cout <<"in"<< std::endl;

				//getting a blob in vector form
				blobRecursiv(blobdet, x, y);
				//pusing the blob vector of one blob in to a into a holding vector
				//If the area of the blob is larger than x store the vector
				//std::cout << "blob vector size of number " << counterVec << ": " << blob_vector.size() << std::endl;

				if (blob_vector.size() > 6) {
					//std::cout <<  blob_vector[0] << std::endl;
					Blobs_detected.push_back(blob_vector);
					
					std::cout << "blob vector size of number " << counterVec << ": " << blob_vector.size() << std::endl;
					
				}
				// debugging

				counterVec++;
				//std::cout << perimeterVector[0] << std::endl;
				//std::cout << perimeterVector[perimeterVector.size()-1] << std::endl;

				//clearing the inner vector of blob and the perimetor to reuse it
				blob_vector.clear();
				//getting a perimetor of a blob in the form of a vector
					//pusing the perimetor vector of one blob in to a into a holding vector
					//Perimetor.push_back(perimeterVector);
					//std::cout << "perimitor vector size of number " << counterVec << ": " << perimeterVector.size() << std::endl;
				//perimeterVector = perimeterBlob(primdet, blob_vector[0].x, blob_vector[0].y);
				//perimeterVector.clear();

			}

		}

	}

	//std::cout << "done" << std::endl;
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
void Blob_extration::blobRecursiv(cv::Mat& blobNew, int x, int y) {

	//Using the cross mention in the grassfire algo
	//First burning the pixel that the cross lands on
	if (blobNew.at<uchar>(y, x) != 0) {
		blobNew.at<uchar>(y, x) = 0;
		//Storing the point in a a vector.
		blob_vector.push_back(cv::Point{ x, y });
	}
	while (noPixLeft == false) {
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
		if (counterBlob >= 750 && maxCounter == true) {
			counterBlob--;
			return;
		}
		//this releases the hold maxCounter add set the the new x,y coordinates
		if (counterBlob <= 750 && maxCounter == true) {
			x = countX;
			y = countY;
			maxCounter = false;
		}
		//Looking at the arms in this order: right,up, left, down.
		//Looking right
		if (blobNew.at<uchar>(y, x + 1) > BitValue && maxCounter == false) {
			//std::cout << "Looking left: " << x - 1 << " , " << y << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x + 1, y);
		}
		//Looking up
		if (blobNew.at<uchar>(y - 1, x) > BitValue && maxCounter == false) {
			//std::cout << "Looking up: " << x << " , " << y - 1 << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x, y - 1);
		}
		//Looking left
		if (blobNew.at<uchar>(y, x - 1) > BitValue && maxCounter == false) {
			//std::cout << "Looking r" << x + 1 << " , " << y << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x - 1, y);
		}
		//Looking down
		if (blobNew.at<uchar>(y + 1, x) > BitValue && maxCounter == false) {
			//std::cout << "Looking down: " << x << " , " << y + 1 << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x, y + 1);
		}
		else {
			counterBlob--;
			return;
		}
	}
}
