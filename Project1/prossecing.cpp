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
			if (Old.at <uchar>(y, x) > 245) {
				New.at<int8_t>(y, x) = 0;
			}
			else {
				New.at<int8_t>(y, x) = 255;
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
std::vector<std::vector<cv::Point>> prossecing::blob(cv::Mat img)
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
			primdet.at<uchar>(y , x) = img.at<uchar>(y , x);

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
					//getting a perimetor of a blob in the form of a vector
					perimeterVector = perimeterBlob(primdet, blob_vector[0].x, blob_vector[0].y);
					//pusing the perimetor vector of one blob in to a into a holding vector
					Perimetor.push_back(perimeterVector);
					std::cout << "blob vector size of number " << counterVec << ": " << blob_vector.size() << std::endl;
					std::cout << "perimitor vector size of number " << counterVec << ": " << perimeterVector.size() << std::endl;

				}
				// debugging

				counterVec++;
				//std::cout << perimeterVector[0] << std::endl;
				//std::cout << perimeterVector[perimeterVector.size()-1] << std::endl;

				//clearing the inner vector of blob and the perimetor to reuse it
				blob_vector.clear();
				perimeterVector.clear();

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
		//Looking at the arms in this order: right,up, left, down.
		//Looking right
		if (blobNew.at<uchar>(y, x + 1) > BitValue && maxCounter == false) {
			//std::cout << "Looking left: " << x - 1 << " , " << y << std::endl;
			counterBlob++;
			//std::cout << counterBlob << std::endl;
			blobRecursiv(blobNew, x + 1, y);
		}
		//Looking up
		if (blobNew.at<uchar>(y - 1, x)> BitValue && maxCounter == false) {
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
		else{
			counterBlob--;
			return;
		}
	}
}
/*
% Function : perimeterBlob.
%
% Description : This function findes the edges through the use of grass fire algorithem
%
%
% Parameters : An image, x and y coordinates.
%
% Return : nonthing.
%
*/
std::vector<cv::Point> prossecing::perimeterBlob(cv::Mat& img, int x ,int y) {

	std::vector<cv::Point> v;
	bool end = false;
	int startX = x;
	int startY = y+1;
	int xx = x;
	int yy = y;
	int endX = 0;
	int endY = 0;
	v.push_back(cv::Point{ xx, yy });
	std::cout << "start  : " << startX << " : " << startY << std::endl;
	while (end==false) {

		//Looking up, in a 9 x9 squrea top left pixel have to be black and the top middel have to be white
		if (img.at<uchar>(yy , xx-1) == 0 && img.at<uchar>(yy - 1, xx) == 255){
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			yy--; //moving up in the image
			endX = xx;
			endY = yy;
			//std::cout << "up   : " << xx << " : " << yy <<  std::endl;
			//std::cout << "up x : "<< endX << "  Y: "<< endY<< std::endl;
			//std::cout << "en x : " << startX << "  Y: " << startY << std::endl;
			if (startX == endX && startY == endY) {
				std::cout << "drop out" << std::endl;
				v.push_back(cv::Point{ xx, yy });

				return v;
			}
		}
		//Looking right, in a 9 x9 squrea top right pixel have to be black and the middel right have to be white
		if (img.at<uchar>(yy-1, xx) == 0 && img.at<uchar>(yy, xx+1) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			xx++; //moving right in the image
			endX = xx;
			endY = yy;
			if (startX == endX && startY == endY) {
				std::cout << "drop out" << std::endl;
				v.push_back(cv::Point{ xx, yy });

				return v;
			}
			//std::cout << "right: " << xx <<" : " << yy << std::endl;
		}
		//Looking down, in a 9 x9 squrea bottum right pixel have to be black and the bottum middel have to be white
		if (img.at<uchar>(yy , xx+1) == 0  && img.at<uchar>(yy + 1, xx) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			yy++;	//moving down in the image
			endX = xx;
			endY = yy;
			//std::cout << "down : " << xx << " : " << yy << std::endl;
		}
		//Looking left, in a 9 x9 squrea bottum left pixel have to be black and the middel left have to be white
		if (img.at<uchar>(yy+1, xx ) == 0 && img.at<uchar>(yy , xx-1) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			xx--;	//moving left in the image
			endX = xx;
			endY = yy;
			//std::cout << "left : " << xx << " : " << yy << std::endl;
		}




	}
}

/*
% Function : perimeterBlob .
%
% Description : This function findes the perimeter based on a vector that contains a single blob
%
%
% Parameters : nonthing.
%
% Return : A vector containing points.
%
*/
std::vector<cv::Point> prossecing::perimeterVec() {

	std::vector<cv::Point> v = blob_vector;

	int x = v[0].x;
	int y = v[0].y;
	unsigned int i = 0;
	bool done = false;
	bool release = false;
	int counterDone = 0;
	bool back = false;
	struct neighbors {
		bool square=false;
		int x = 0;
		int y = 0;
		unsigned int idx = 0;
	};

	neighbors n[9];

	while (done ==false)
	{
		v.push_back(cv::Point{ x, y });
		if(back==false){
			for (i ; i < blob_vector.size(); i++) {
			// top left squera
				if (v.at(i).x == x - 1 && v.at(i).y == y - 1) {
				n[0].square= true;

				}
				//top middel squera
				//neighbors
				if (v.at(i).x == x && v.at(i).y == y - 1) {
					n[1].square = true;
					n[1].x = v.at(i).x;
					n[1].y = v.at(i).y;
					n[1].idx = i;
					if (release == true && v.at(0).x == v.at(i).x && v.at(0).y == v.at(i).y - 1) {
						std::cout << "done" << std::endl;
						v.push_back(cv::Point{ v.at(i).x,v.at(i).y });
						done = true;
					return v;
					}
				}
				// top rigth squera
				if (v.at(i).x == x + 1 && v.at(i).y == y - 1) {
				n[2].square = true;
				}
				// middel left squera
				//neighbors
				if (v.at(i).x == x - 1 && v.at(i).y == y ) {
					n[3].square = true;
					n[3].x = v.at(i).x;;
					n[3].y = v.at(i).y;
					n[3].idx = i;
				}
				// middel middel squera
				if (v.at(i).x == x && v.at(i).y == y ) {
					n[4].square = true;

					//	std::cout << counterDone << std::endl;

				}
				// middel rigth squera
				//neighbors
				if (v.at(i).x == x + 1 && v.at(i).y == y ) {
					n[5].square = true;
					n[5].x = v.at(i).x;
					n[5].y = v.at(i).y;
					n[5].idx = i;
					if (release == true && v.at(0).x == v.at(i).x +1 && v.at(0).y == v.at(i).y) {
						//std::cout << "done" << std::endl;
						v.push_back(cv::Point{ v.at(i).x, v.at(i).y});
						done = true;
						return v;
					}
				}
				// bottom left squera
				if (v.at(i).x == x - 1 && v.at(i).y == y +1) {
					n[6].square = true;
				}
				//bottom middel squera
				//neighbors
				if (v.at(i).x == x && v.at(i).y == y + 1) {
					n[7].square = true;
					n[7].x = v.at(i).x;
					n[7].y = v.at(i).y;
					n[7].idx = i;
				}
				// bottom rigth squera
				if (v.at(i).x == x + 1 && v.at(i).y == y + 1) {
					n[8].square = true;

				}
				// If cross has moved two steps the relase bool is turned true, so it is possible to look for
				// Perimeter start
				if (counterDone>2) {
					release = true;
				}
				if (i == blob_vector.size()) {
					//std::cout << "true" <<std::endl;
					back = true;
				}
			}
		}
		if (back==true) {
			//std::cout << "going back" << std::endl;
			for (i; i > 0; i--) {
				// top left squera
				if (v.at(i).x == x - 1 && v.at(i).y == y - 1) {
					n[0].square = true;

				}
				//top middel squera
				//neighbors
				if (v.at(i).x == x && v.at(i).y == y - 1) {
					n[1].square = true;
					n[1].x = v.at(i).x;
					n[1].y = v.at(i).y;
					n[1].idx = i;
					if (release == true && v.at(0).x == v.at(i).x && v.at(0).y == v.at(i).y - 1) {
						//std::cout << "done" << std::endl;
						v.push_back(cv::Point{ v.at(i).x,v.at(i).y });
						done = true;
						return v;
					}
				}
				// top rigth squera
				if (v.at(i).x == x + 1 && v.at(i).y == y - 1) {
					n[2].square = true;
				}
				// middel left squera
				//neighbors
				if (v.at(i).x == x - 1 && v.at(i).y == y) {
					//std::cout << "SQ 3" << std::endl;
					n[3].square = true;
					n[3].x = v.at(i).x;;
					n[3].y = v.at(i).y;
					n[3].idx = i;
				}
				// middel middel squera
				if (v.at(i).x == x && v.at(i).y == y) {
					n[4].square = true;

					//	std::cout << counterDone << std::endl;

				}
				// middel rigth squera
				//neighbors
				if (v.at(i).x == x + 1 && v.at(i).y == y) {
					n[5].square = true;
					n[5].x = v.at(i).x;
					n[5].y = v.at(i).y;
					n[5].idx = i;
					if (release == true && v.at(0).x == v.at(i).x + 1 && v.at(0).y == v.at(i).y) {
						//std::cout << "done" << std::endl;
						v.push_back(cv::Point{ v.at(i).x, v.at(i).y });
						done = true;
						return v;
					}
				}
				// bottom left squera
				if (v.at(i).x == x - 1 && v.at(i).y == y + 1) {
					n[6].square = true;
				}
				//bottom middel squera
				//neighbors
				if (v.at(i).x == x && v.at(i).y == y + 1) {
					//std::cout << "SQ 3 false" << std::endl;
					n[7].square = true;
					n[7].x = v.at(i).x;
					n[7].y = v.at(i).y;
					n[7].idx = i;
				}
				// bottom rigth squera
				if (v.at(i).x == x + 1 && v.at(i).y == y + 1) {
					//std::cout << "SQ 3 false" << std::endl;
					n[8].square = true;

				}
				// If cross has moved two steps the relase bool is turned true, so it is possible to look for
				// Perimeter start
				if (counterDone > 2) {
					release = true;
				}
				if (i == 0) {
					back = false;
				}
			}
		}
		//std::cout << "stop for" << std::endl;
		/// Here the cross is moved
		// looking up
		if (n[3].square == false && n[6].square == false && n[1].square == true) {
			x = n[1].x;
			y = n[1].y;
			i = n[1].idx;
			//std::cout << "looking up" << std::endl;
			/// reseting struct variables
			for (int i = 0; i <9; i++) {

				n[i].square = false;
				n[i].x = 0;
				n[i].y = 0;
				n[i].idx = 0;
			}
			counterDone++;
		}
		// looking right
		if (n[0].square == false && n[1].square == false && n[5].square == true) {
			x = n[5].x;
			y = n[5].y;
			i = n[5].idx;
			//std::cout << "looking rigth" << std::endl;


			/// reseting struct variables
			for (int i = 0; i <9; i++) {

				n[i].square = false;
				n[i].x = 0;
				n[i].y = 0;
				n[i].idx = 0;

			}
			counterDone++;
		}
		// looking down
		if (n[2].square == false && n[5].square == false && n[7].square == true) {
			x = n[7].x;
			y = n[7].y;
			i = n[7].idx;
			if (i >= blob_vector.size()-1) {
				//std::cout << "true" << std::endl;
				back = true;
			}
			//std::cout << "looking down" << std::endl;
			/// reseting struct variables
			for (int i = 0; i < 9; i++) {

				n[i].square = false;
				n[i].x = 0;
				n[i].y = 0;
				n[i].idx = 0;
			}

		}
		// looking left
		if (n[7].square == false && n[8].square == false && n[3].square == true) {
			x = n[3].x;
			y = n[3].y;
			i = n[3].idx;
			//std::cout << "looking left" << std::endl;
			/// reseting struct variables
			for (int i = 0; i < 9; i++) {

				n[i].square = false;
				n[i].x = 0;
				n[i].y = 0;
				n[i].idx = 0;
			}

		}
		else {

		}
		//std::cout << i << std::endl;
	}
	

}
float prossecing::percent(int old_value,int count, int V) {

	float percent = (old_value / count) * V;

	return percent;
}
float prossecing::rob_distance(cv::Point point1, cv::Point point2) {

	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}
