#include "Test.h"
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iterator> 
#include <iostream>
#include <fstream>
#include <sstream>
#include "BlobFeatures.h"
#include "feature.h"

Test::Test()
{
	

}


Test::~Test()
{
}


void Test::run( cv::Mat img, cv::Mat srcC, std::vector<std::vector<cv::Point>> Blobs)
{
		feature Feature;
		std::fstream fs;
		std::string Classifier = "Class.txt";
		//Feature Extraction
		std::vector<BlobFeatures> BLOBS;

		for (int i = 0; i < Blobs.size(); i++) {
			//Create instance of struct
			BlobFeatures Extract;

			//Add area to struct
			float are = static_cast<float>(Blobs[i].size());
			Extract.area = 1. / (1. + are);

			//Add perimeter to struct
			std::vector<cv::Point> perimeter;
			float per = Feature.perimeterBlob(Blobs[i], img.rows, img.cols, perimeter);
			Extract.perimeter = 1 / (1 + per);

			//Bounding circle to struct
			Extract.boundingCircleRadius = 1 / (1.0 + Feature.BoundingCircle(Blobs[i], img.rows, img.cols, Extract.CoMX, Extract.CoMY));

			//Add circularity to struct
			Extract.circularity = 1 / (1.0 + Feature.BlobCircularity(Extract.area, Extract.perimeter));


			//Point of TopRigth corner and bottom left corner
			std::vector<cv::Point> BBpoints = Feature.BoundingBox(perimeter);

			//Add area of bounding box to struct
			Extract.boundingBoxArea = 1 / (1.0 + Feature.area(BBpoints));

			//Add the higth width ratio to struct
			Extract.heightWidthRatio = 1 / (1.0 + Feature.HeightWitdh(BBpoints));

			//Add the compactness of the blob to struct
			Extract.compactness = 1 / (1.0 + Feature.compactness(BBpoints, Blobs[i].size()));

			//drawing perimeter of what has to be trained


			for (int t = 0; t < perimeter.size() - 1; t++)
			{
				srcC.at<uchar>(perimeter[t].y, perimeter[t].x) = 255;
			}

			cv::imshow("Training blob", srcC);
			cv::waitKey(1);
			//selecting of what to do whit the data
			std::cout << "Traning data(1) or skip data(2)" << std::endl;
			int j = 0;
			std::cin >> j;
			if (j == 1) {
				//selecting if it is a fault or not
				std::cout << "Fault (1) or no faul (2) " << std::endl;
				int k = 0;
				std::cin >> k;
				if (k == 1) {
					int j = 0;
					std::cout << "The fault" << std::endl;
					std::cout << "Give the Fault a lable" << std::endl;
					std::cout << "Obstacle(1) Branch(2) Offset(3)" << std::endl;
					std::cin >> j;
					if (j == 1) {
						Extract.label = "Obstacles";
					}
					if (j == 2) {
						std::cout << "Up stream(1) Down stream(2)" << std::endl;
						int Br = 0;
						std::cin >> Br;
						if (Br == 1) {
							Extract.label = "BranchUp";
						}
						if (Br == 2) {
							Extract.label = "BranchDown";
						}
					}
					if (j == 3) {
						Extract.label = "Offset";
					}
					//storing the extracted features for a blob
					fs.open(Classifier, std::fstream::in | std::fstream::out | std::fstream::app);

					fs << Extract.area << ',' <<//notworking
						Extract.perimeter << ',' <<//notworking
						Extract.circularity << ',' <<//notworking
						Extract.boundingCircleRadius << ',' <<
						Extract.boundingBoxArea << ',' <<//notworking
						Extract.heightWidthRatio << ',' <<
						Extract.compactness << ',' <<
						Extract.CoMX << ',' <<//notworking
						Extract.CoMY << ',' <<//notworking
						Extract.label << std::endl;
					fs.close();
				}
				if (k == 2) {
					std::cout << "No fault" << std::endl;
					Extract.label = "No_fault";
					//storing the extracted features for a blob
					fs.open(Classifier, std::fstream::in | std::fstream::out | std::fstream::app);

						fs << Extract.area << ',' <<
						Extract.perimeter << ',' <<
						Extract.circularity << ',' <<
						Extract.boundingCircleRadius << ',' <<
						Extract.boundingBoxArea << ',' <<
						Extract.heightWidthRatio << ',' <<
						Extract.compactness << ',' <<
						Extract.CoMX << ',' <<
						Extract.CoMY << ',' <<
						Extract.label << std::endl;
						fs.close();

				}
				else {}
				// traning data save to file
				cv::destroyAllWindows();


			}
			else {}
		}
return;
}