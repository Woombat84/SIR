#include "feature.h"
#include <vector>



feature::feature()
{
}


feature::~feature()
{
}


/*
% Function : perimeterBlob.
%
% Description : This function finds the edges through the use of grass fire algorithm
%
%
% Parameters : An image, x and y coordinates.
%
% Return : nothing.
%
*/
int feature::perimeterBlob(std::vector<cv::Point> BLOB, int Height, int Width, std::vector<cv::Point> &v) {

	//Create the BLOB in a new Matrix
	cv::Mat img = cv::Mat::zeros(Height, Width, CV_8UC1);

	for (int i = 0; i < BLOB.size(); i++) {
		img.at<uchar>(BLOB[i].y, BLOB[i].x) = 255;
	}
	//cv::imshow("start", img);
	//std::cout << "here"<< std::endl;
	bool end = false;
	int startX = BLOB[0].x;
	int startY = BLOB[0].y;
	int xx = startX;
	int yy = startY;
	int endX = 0;
	int endY = 0;
	v.push_back(cv::Point{ xx, yy });
	//std::cout << "start  : " << startX << " : " << startY << std::endl;
	while (end == false) {

		//Looking up, in a 9 x9 squrea top left pixel have to be black and the top middel have to be white
		if (img.at<uchar>(yy, xx - 1) == 0 && img.at<uchar>(yy - 1, xx) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			yy--; //moving up in the image
			endX = xx;
			endY = yy;
			//std::cout << "up   : " << xx << " : " << yy <<  std::endl;
			//std::cout << "up x : "<< endX << "  Y: "<< endY<< std::endl;
			//std::cout << "en x : " << startX << "  Y: " << startY << std::endl;
			if (startX == endX && startY+1 == endY) {
				//std::cout << "drop out" << std::endl;
				v.push_back(cv::Point{ xx, yy });
				//std::cout << "up: " << xx << " : " << yy <<" last stand"<< std::endl;
				
				return v.size();
			}
			//std::cout << "up: " << xx << " : " << yy << std::endl;
		}
		//Looking right, in a 9 x9 squrea top right pixel have to be black and the middel right have to be white
		else if (img.at<uchar>(yy - 1, xx) == 0 && img.at<uchar>(yy, xx + 1) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			xx++; //moving right in the image
			endX = xx;
			endY = yy;
			if (startX == endX && startY+1 == endY) {
				//std::cout << "drop out" << std::endl;
				
				//std::cout << "right: " << xx << " : " << yy << " last stand" << std::endl;
				return v.size();
			}
			//std::cout << "right: " << xx <<" : " << yy << std::endl;
		}
		//Looking down, in a 9 x9 squrea bottum right pixel have to be black and the bottum middel have to be white
		else if (img.at<uchar>(yy, xx + 1) == 0 && img.at<uchar>(yy + 1, xx) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			yy++;	//moving down in the image
			endX = xx;
			endY = yy;
			//std::cout << "down : " << xx << " : " << yy << std::endl;
		}
		//Looking left, in a 9 x9 squrea bottum left pixel have to be black and the middel left have to be white
		else if (img.at<uchar>(yy + 1, xx) == 0 && img.at<uchar>(yy, xx - 1) == 255) {
			img.at<uchar>(yy, xx) = 0;// "burning" the pixel
			v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
			xx--;	//moving left in the image
			endX = xx;
			endY = yy;
			//std::cout << "left : " << xx << " : " << yy << std::endl;
		}
		else
		{
			//Looking up, in a 9 x9 squrea top left pixel have to be black and the top middel have to be black and the top right have to be white
			if (img.at<uchar>(yy, xx - 1) == 0 && img.at<uchar>(yy - 1, xx) == 0 && img.at<uchar>(yy - 1, xx+1) == 255) {
				img.at<uchar>(yy, xx) = 0;// "burning" the pixel
				v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
				yy--; //moving up in the image
				xx++;
				endX = xx;
				endY = yy;
				//std::cout << "up   : " << xx << " : " << yy <<  std::endl;
				//std::cout << "up x : "<< endX << "  Y: "<< endY<< std::endl;
				//std::cout << "en x : " << startX << "  Y: " << startY << std::endl;
				if (startX == endX && startY + 1 == endY) {
					//std::cout << "drop out" << std::endl;
					v.push_back(cv::Point{ xx, yy });
					//std::cout << "up _right: " << xx << " : " << yy <<" last stand"<< std::endl;

					return v.size();
				}
				//std::cout << "up_right: " << xx << " : " << yy << std::endl;
			}
			//Looking right, in a 9 x9 squrea top right pixel have to be black and the middel right have to be black and bottum right have to wihte
			else if (img.at<uchar>(yy - 1, xx) == 0 && img.at<uchar>(yy, xx + 1) == 0  && img.at<uchar>(yy + 1, xx + 1) == 255) {
				img.at<uchar>(yy, xx) = 0;// "burning" the pixel
				v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
				xx++; //moving right in the image
				yy++;
				endX = xx;
				endY = yy;
				if (startX == endX && startY + 1 == endY) {
					std::cout << "drop out" << std::endl;
					std::cout << "down_right: " << xx << " : " << yy << " last stand" << std::endl;
					return v.size();
				}
				//std::cout << "down_right: " << xx <<" : " << yy << std::endl;
			}
			//Looking down, in a 9 x9 squrea bottum right pixel have to be black and the bottum middel have to be black
			else if (img.at<uchar>(yy, xx + 1) == 0 && img.at<uchar>(yy + 1, xx) == 0 && img.at<uchar>(yy + 1, xx - 1) == 255) {
				img.at<uchar>(yy, xx) = 0;// "burning" the pixel
				v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
				yy++;	//moving down in the image
				xx--;
				endX = xx;
				endY = yy;
				//std::cout << "left_down : " << xx << " : " << yy << std::endl;
			}
			//Looking left, in a 9 x9 squrea bottum left pixel have to be black and the middel left have to be white
			else if (img.at<uchar>(yy + 1, xx) == 0 && img.at<uchar>(yy, xx - 1) == 0 && img.at<uchar>(yy -1, xx -1 ) == 255) {
				img.at<uchar>(yy, xx) = 0;// "burning" the pixel
				v.push_back(cv::Point{ xx, yy }); // storing the points in the vector "v"
				xx--;	//moving left in the image
				yy--;
				endX = xx;
				endY = yy;
				//std::cout << "top_left : " << xx << " : " << yy << std::endl;
				
			}	
			//cv::imshow("end", img);
			//cv::waitKey(1);
		}	
	}
	return v.size();
}

float feature::BlobCircularity(int BlobArea, double BlobPerimeter)
{
	float Circularity = (4 * PI * BlobArea) / (BlobPerimeter * BlobPerimeter);
	return Circularity;
}

float feature::BoundingCircle(std::vector<cv::Point> BLOB, int Height, int Width, int &xAvr, int &yAvr)
{
	//Find the centre of the BLOB
	xAvr = 0;
	yAvr = 0;
	for (int i = 0; i < BLOB.size(); i++) {
		xAvr += BLOB[i].x;
		yAvr += BLOB[i].y;
	}
	xAvr = xAvr / BLOB.size(); //Centre x-coordinate
	yAvr = yAvr / BLOB.size(); //Centre y-coordinate

	//Create the BLOB in a new Matrix
	cv::Mat Calc = cv::Mat::zeros(Height, Width, CV_8UC1);

	for (int i = 0; i < BLOB.size(); i++) {
		Calc.at<uchar>(BLOB[i].y, BLOB[i].x) = 255;
	}

	//find radii with 15deg intervals

	float Radius = 0;
	float TempRadius = 0;
	int pointX = xAvr;
	int pointY = yAvr;

	//Cosine right
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Up
		if (Degrees[i] >= 0) {
			for (int r = 1; r < Width - xAvr && yAvr - (r*Degrees[i]) > 0; r++) {
				if (Calc.at<uchar>(yAvr - (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr - (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
		//Down
		else {
			for (int r = 1; r < Width - xAvr && (-r * Degrees[i]) < Height - yAvr; r++) {
				if (Calc.at<uchar>(yAvr - (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr - (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}


	//Sine down
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Right
		if (Degrees[i] >= 0) {
			for (int r = 1; r < Height - yAvr && (r*Degrees[i]) < Width - xAvr; r++) {
				if (Calc.at<uchar>(yAvr + r, xAvr + (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
		//Left
		else {
			for (int r = 1; r + yAvr < Height && xAvr + (r * Degrees[i]) > 0; r++) {
				if (Calc.at<uchar>(yAvr + r, xAvr + (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}



	//Cosine left
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Up
		if (Degrees[i] >= 0) {
			for (int r = -1; xAvr + r > 0 && yAvr + (r*Degrees[i]) > 0; r--) {
				if (Calc.at<uchar>(yAvr + (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}

		//Down
		else {
			for (int r = -1; xAvr + r > 0 && (r * Degrees[i]) < Height - yAvr; r--) {
				if (Calc.at<uchar>(yAvr + (r*Degrees[i]), xAvr + r)) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}

	//Sine up
	for (int i = 0; i < sizeof(Degrees) / sizeof(*Degrees); i++) {
		//Right
		if (Degrees[i] >= 0) {
			for (int r = -1; yAvr + r > 0 && (-r * Degrees[i]) < Width - xAvr; r--) {
				if (Calc.at<uchar>(yAvr + r, xAvr - (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr + (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
		//Left
		else {
			for (int r = -1; yAvr + r > 0 && xAvr - (r * Degrees[i]) > 0; r--) {
				if (Calc.at<uchar>(yAvr + r, xAvr - (r*Degrees[i]))) {

					pointX = xAvr + r;
					pointY = yAvr - (r*Degrees[i]);
				}
				TempRadius = sqrt((pointX - xAvr) * (pointX - xAvr) + (pointY - yAvr) * (pointY - yAvr));
				if (TempRadius > Radius) {
					Radius = TempRadius;
				}
			}
		}
	}

	return Radius;
}
/*
% Function :  boundary box.
%
% Description : This function finds a boundary box based on a perimeter.
%
%
% Parameters : A vector of points of a perimeter.
%
% Return : A vector of points of top left and bottoum rigth.
%
*/
std::vector<cv::Point> feature::BoundingBox(std::vector<cv::Point> perimeter) {
	auto min_X = 10000;
	auto max_X = 0;
	auto min_Y = 100000;
	auto max_Y = 0;
	

	std::vector < cv::Point > v;
	for (int i=0 ; i < perimeter.size(); i++){
		//x less than min_x set x y
		if (perimeter[i].x < min_X) min_X = perimeter[i].x;
		//x more than max_x set x y
		if (perimeter[i].x > max_X) max_X = perimeter[i].x;
		//y less than max_x set x y
		if (perimeter[i].x > min_Y) min_Y = perimeter[i].y;
		//y more than max_y set x y
		if (perimeter[i].y > max_Y) max_Y = perimeter[i].y; 
	}
	// push top left corner coordinate
	v.push_back(cv::Point{min_X, min_Y});
	// push bottum left corner coordinate
	v.push_back(cv::Point{max_X, max_Y});

	return v;
}
float feature::HeightWitdh(std::vector<cv::Point> v) {
	
	return ((v[1].y - v[0].y) / (v[1].x - v[0].x));

}
/*
% Function : Compactness.
%
% Description : This function finds compactness of a square
%
%
% Parameters : A vector of points of top left and bottoum rigth and an area.
%
% Return : Compactness
%
*/
float feature::compactness(std::vector<cv::Point> v, int area) {
	return(area / ((v[1].y - v[0].y) * (v[1].x - v[0].x)));
}
/*
% Function : Area of the boundary box.
%
% Description : This function finds area of the boundary box
%
%
% Parameters : A vector of points of top left and bottoum rigth.
%
% Return : Area of the boundary box
%
*/
int feature::area(std::vector<cv::Point> v)
{
	return (v[1].y - v[0].y) * (v[1].x - v[0].x);
}
