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


void Test::training( cv::Mat &img, cv::Mat &srcC, std::vector<std::vector<cv::Point>> Blobs, std::string Classifier)
{
	
		feature Feature;
		
		std::fstream fs;

		//Feature Extraction
		//std::vector<BlobFeatures> BLOBS;
		//std::cout << Blobs.size() << std::endl;
		for (int i = 0; i < Blobs.size(); i++) {
			cv::destroyAllWindows();
			//Create instance of struct
			BlobFeatures Extract;

			//Add area to struct
			Extract.area = 1. / (1.0 + Blobs[i].size());

			//Add perimeter to struct
			std::vector<cv::Point> perimeter;
			Extract.perimeter = 1 / (1.0 + Feature.perimeterBlob(Blobs[i], srcC.rows, srcC.cols, perimeter));
			
			//Bounding circle to struct
			Extract.boundingCircleRadius = 1 / (1.0 + Feature.BoundingCircle(Blobs[i], srcC.rows, srcC.cols, Extract.CoMX, Extract.CoMY));

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
			
			cv::Mat show = cv::Mat(img.rows, img.cols, CV_8UC1);
			for (int y = 0; y < show.rows; y++) {
				for (int x = 0; x < show.cols; x++) {
					show.at<uchar>(y, x) = img.at<uchar>(y, x);
				}
			}
			for (int t = 0; t < perimeter.size(); t++)
			{
				
				show.at<uchar>(perimeter[t].y, perimeter[t].x) = 0;
			}

			cv::imshow("Training blob", show);
			
			//selecting of what to do whit the data
			std::cout << "Traning data(1) or skip data(2)" << std::endl;
			cv::waitKey(100);
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
				


			}
			else {}
			
		}
		
		cv::destroyAllWindows();
return;
}