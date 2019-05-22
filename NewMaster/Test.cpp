#include "Test.h"
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iterator> 
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "BlobFeatures.h"
#include "feature.h"
#include <algorithm>
#include <map>
Test::Test()
{
	

}


Test::~Test()
{
}


void Test::training( cv::Mat &img, cv::Mat &srcC, std::vector<std::vector<cv::Point>> Blobs, std::string Classifier, std::vector<BlobFeatures>vector)
{
	
		feature Feature;
		
		std::fstream fs;
		std::vector<BlobFeatures> Bf;
		//Feature Extraction
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
			cv::namedWindow(Classifier,CV_WINDOW_AUTOSIZE);
			cv::imshow(Classifier, show);
			
			//selecting of what to do whit the data
			std::cout << "Traning data(1), skip data(2) or Test data(3)" << std::endl;
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
					std::cout << "No fault,label Noise(1) Centerpipe(2)" << std::endl;
					int h=0;
					std::cin >> h;
					if(h==1){
					Extract.label = "Noise";
					}
					if(h==2){
						Extract.label = "Centerpipe";
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
				else {}
			}
			if (j==3) {
				std::string faultLable = DistanceCalc(vector, Extract);
				std::cout << faultLable << std::endl;
				cv::waitKey(1000);
			}
			else {}	
		}
		cv::destroyAllWindows();
return;
}

std::string Test::DistanceCalc(std::vector<BlobFeatures>vector, BlobFeatures feat){

	DistFeatures f;
	std::vector<DistFeatures> v;
	for (int i = 0; i < vector.size() ; i++) {
		
		f.dist=sqrt((feat.area - vector[i].area) * (feat.area - vector[i].area)
			+ (feat.perimeter - vector[i].perimeter) * (feat.perimeter - vector[i].perimeter)
			+ (feat.circularity - vector[i].circularity) * (feat.circularity - vector[i].circularity)
			+ (feat.boundingCircleRadius - vector[i].boundingCircleRadius) * (feat.boundingCircleRadius - vector[i].boundingCircleRadius)
			+ (feat.boundingBoxArea - vector[i].boundingBoxArea) * (feat.boundingBoxArea - vector[i].boundingBoxArea)
			+ (feat.heightWidthRatio - vector[i].heightWidthRatio) * (feat.heightWidthRatio - vector[i].heightWidthRatio)
			+ (feat.compactness - vector[i].compactness) * (feat.compactness - vector[i].compactness)
			+ (feat.CoMX - vector[i].CoMX) * (feat.CoMX - vector[i].CoMX)
			+ (feat.CoMY - vector[i].CoMY) * (feat.CoMY - vector[i].CoMY));
			f.label = vector[i].label;
		v.push_back(f);
	}
	//Sort distances
	std::sort(v.begin(), v.end(), [](const DistFeatures & d1, const DistFeatures & d2) { return d1.dist < d2.dist; });
	//finding K nearset neibourg
	std::string lable = knearest(v);

	return lable;
}

void Test::loadData(std::vector<BlobFeatures> &pipeVec, std::vector<BlobFeatures> &obsVec) {

	std::ifstream pipeslist("pipes.txt");
	
		if (!pipeslist)
		{
				std::cout << "File can't be opened! " << std::endl;
				system("PAUSE");
		}

	BlobFeatures pipes;
	std::string s="";
	while (getline(pipeslist,s, ',')) {
		pipes.area = stof(s);
		getline(pipeslist,s , ',');
		pipes.perimeter = stof(s);
		getline(pipeslist,s , ',');
		pipes.circularity = stof(s);
		getline(pipeslist,s, ',');
		pipes.boundingCircleRadius = stof(s);
		getline(pipeslist, s, ',');
		pipes.boundingBoxArea = stof(s);
		getline(pipeslist,s, ',');
		pipes.heightWidthRatio = stof(s);
		getline(pipeslist,s, ',');
		pipes.compactness = stof(s);
		getline(pipeslist,s, ',');
		pipes.CoMX = stoi(s);
		getline(pipeslist,s , ',');
		pipes.CoMY = stoi(s);
		getline(pipeslist,pipes.label, '\n');
		pipeVec.push_back(pipes);
		
	}
	
	pipeslist.close();
	
	
	std::ifstream obslist("obstacles.txt");
	BlobFeatures obstacles;
		if (!obslist)
		{
				std::cout << "File can't be opened! " << std::endl;
				system("PAUSE");
		}
	
	while (getline(obslist,s ,','))
	{
			obstacles.area = stof(s);
			getline(obslist, s, ',');
			obstacles.perimeter = stof(s);
			getline(obslist, s, ',');
			obstacles.circularity = stof(s);
			getline(obslist, s, ',');
			obstacles.boundingCircleRadius = stof(s);
			getline(obslist, s, ',');
			obstacles.boundingBoxArea = stof(s);
			getline(obslist, s, ',');
			obstacles.heightWidthRatio = stof(s);
			getline(obslist, s, ',');
			obstacles.compactness = stof(s);
			getline(obslist, s, ',');
			obstacles.CoMX = stoi(s);
			getline(obslist, s, ',');
			obstacles.CoMY = stoi(s);
			getline(obslist, obstacles.label, '\n');

			obsVec.push_back(obstacles);
	}
	
	obslist.close();

	return;
}

std::string Test::knearest(std::vector<DistFeatures> v) {
	std::string s = "";
	int label[6] = {0,0,0,0,0,0};
	for (int k = 0; k < Kneighbors; k++) {
		if (v[k].label == "Offset" ) {
			label[0]++;
		}
		if (v[k].label == "Centerpipe" ) {
			label[1]++;
		}
		if (v[k].label == "BranchDown" ) {
			label[2]++;
		}
		if (v[k].label ==  "BranchUp" ) {
			label[3]++;
		}
		if (v[k].label ==  "Obstacles" ) {
			label[4]++;
		}
		if (v[k].label == "Noise" ) {
			label[5]++;
		}

	}
	for (auto label : label)std::cout << label << ' ' << std::endl;
	int max =0;
	int idx;
	for (int i = 0; i < 6; i++)
	{
		if (max < label[i]) {
			max = label[i];
			idx = i+1;
		}
	}
	std::cout << idx <<std::endl;
	switch(idx) {
		case 1: s = "Offset";  break;
		case 2: s = "Centerpipe"; break;
		case 3: s = "BranchDown"; break;
		case 4: s = "BranchUp"; break;
		case 5: s = "Obstacles"; break;
		case 6: s = "Noise"; break;
	}
	return s;
}

