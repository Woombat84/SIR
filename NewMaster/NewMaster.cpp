#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include "Pre_prossesing.h"
#include "Segmentation.h"
#include "Blob_extration.h"
#include "feature.h"
#include "BlobFeatures.h"


using namespace std;
using namespace cv;


int main()
{
	Pre_prossesing PrePross;
	Segmentation Segment;
	Blob_extration BLOB;
	feature Feature;
	//C:\\Users\\Woombat\\Pictures\\P4\\tr.png
	Mat img = imread("C:\\Users\\Jonathan\\Pictures\\P4\\IR.png", IMREAD_GRAYSCALE);
	if (!img.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	//imshow("Image", img); //Uncomment to see image before blurring
	

	//Mat MeanBlur = Mat(img.rows, img.cols, CV_8UC1);
	//cv::blur(img, MeanBlur, cv::Size(7, 7));
	//imshow("MeanBlurred", MeanBlur); //Uncomment to see image after blurring
	//imwrite("C:\\Users\\Jonathan\\Pictures\\P4\\MeanBlur.png", MeanBlur);


	//Pre-Prosessing
	PrePross.bluring(img, 7, 1);
	//imshow("Blurred", img); //Uncomment to see image after blurring
	//imwrite("C:\\Users\\Jonathan\\Pictures\\P4\\MedianBlur.png", img);

	//Mat Sub = Mat(img.cols, img.rows, CV_8UC1);

	//Sub = MeanBlur - img;
	//imshow("Subtract", Sub);

	




	
	//Segmentation
	Segment.Threshold(img, Segment.percent(img,0.05));
	imshow("Thresholded", img); //Uncomment to see image after thresholding
	//imwrite("C:\\Users\\Jonathan\\Pictures\\P4\\Thresh3.png", img);

	
	Mat Temp = Mat(img.rows, img.cols, CV_8UC1); //Used for the output of the Morphology
	Mat Kernel = Segment.Kernel(7, 0);
	Segment.Opening(img, Temp, Kernel);
	imshow("Open", Temp); //Uncomment to see image after opening
	//imwrite("C:\\Users\\Jonathan\\Pictures\\P4\\Open7.png", img);

	Mat Kernel2 = Segment.Kernel(3, 0);
	Segment.Closing(Temp, img, Kernel2);
	imshow("Closed", img); //Uncomment to see image after Closing
	//imwrite("C:\\Users\\Jonathan\\Pictures\\P4\\Closed3.png", img);

	Mat Cropped = Segment.Cropping(img, 7);
	imshow("Cropped", Cropped); //Uncomment to see image after Cropping
	imwrite("C:\\Users\\Jonathan\\Pictures\\P4\\Cropped.png", img);
		
	/*
	//Blob Extraction
	std::vector<std::vector<cv::Point>> Blobs = BLOB.blob(Cropped);

	//Feature Extraction
	vector<BlobFeatures> BLOBS;
	
	for (int i = 0; i < Blobs.size(); i++) {
		//Create instance of struct
		BlobFeatures Extract;
		
		//Add area to struct
		Extract.area = Blobs[i].size();
		std::vector<cv::Point> perimeter;
		//Add perimeter to struct
		Extract.perimeter = Feature.perimeterBlob(Blobs[i], img.rows, img.cols,perimeter);

		//Bounding circle to struct
		Extract.boundingCircleRadius = Feature.BoundingCircle(Blobs[i], img.rows, img.cols);

		//Add circularity to struct
		Extract.circularity = Feature.BlobCircularity(Extract.area, Extract.perimeter);
		
		std::vector<cv::Point> BBpoints = Feature.BoundingBox(perimeter);

		Extract.boundingBoxArea = Feature.area(BBpoints);

		

		Extract.heightWidthRatio = Feature.HeightWitdh(BBpoints);
		
		Extract.compactness = Feature.compactness(BBpoints, Blobs[i].size());

		//Push struct to vector
		BLOBS.push_back(Extract);		
	}
	cout << "Traning data(1) or test data(2)" << endl;
	int j = 0;
	cin >> j;
	if (j == 1) {
		string label = "";
		cout << "Fault (1) or no faul (2) " << endl;
		int k = 0;
		cin >> k;
		if (k ==1 ) {
			cout << "The fault" << endl;
			cin >> label;
			
		}
		if (k == 2) {
			cout << "No fault" << endl;
			label = "No_fault";

		}
		else cout << "try again" << endl;
		// traning data save to file

	}

	else
	/* For Debugging 
	cout << "BLOBS.size() = ";
	cout << BLOBS.size() << endl;
	for (int i = 0; i < BLOBS.size(); i++) {
		cout << "BLOB" << i << " ";
		cout << BLOBS[i].circularity << endl;
		waitKey(2000);
	}
	*/
		
	

	
	
	//Classification
		//TODO Compare structs to training data

	waitKey(0);
	return 0;
}

