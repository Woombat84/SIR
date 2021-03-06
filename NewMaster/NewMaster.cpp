#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iterator> 
#include <iostream>
#include <fstream>
#include <sstream>
#include "Pre_prossesing.h"
#include "Segmentation.h"
#include "Blob_extration.h"
#include "feature.h"
#include "BlobFeatures.h"
#include"Test.h"

using namespace std;
using namespace cv;


int main()
{	
	Pre_prossesing PrePross;
	Segmentation Segment;
	Blob_extration BLOB;
	feature Feature;
	Test test;
	std::vector<BlobFeatures> pipeVector;
	std::vector<BlobFeatures> obsVector;
	//test.loadData( pipeVector,  obsVector);
	//C:\\Users\\Woombat\\Pictures\\P4\\tr.png
	for (int i = 1; i < 533; i++)
	{
		std::stringstream stream;
		
		stream << "C:\\Users\\Dennis\\Desktop\\picSewerimg\\obstacles\\shoe1\\validation\\"<<i<<".jpg";
		
		Mat img = imread(stream.str(), IMREAD_GRAYSCALE);
		Mat imgTop= imread(stream.str(), IMREAD_GRAYSCALE);
		Mat src = imread(stream.str(), IMREAD_GRAYSCALE);
		if (!img.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			return -1;
		}
		
		//Pre-Prosessing
		PrePross.bluring(img, 5, 1);
		PrePross.bluring(imgTop,5,1);
		//imshow("Blurred", imgTop); //Uncomment to see image after blurring
	
		
		//Segmentation
		Segment.Threshold(img, Segment.percent(img,0.02),0);
		Segment.Threshold(imgTop, Segment.percent(imgTop, 0.95),1);
		//imshow("Thresholded", img); //Uncomment to see image after thresholding
		//imshow("ThresholdedTop", imgTop); //Uncomment to see image after thresholding
		//waitKey(10);

		Mat Temp = Mat(img.rows, img.cols, CV_8UC1); //Used for the output of the Morphology
		Mat TempTOP = Mat(imgTop.rows, imgTop.cols, CV_8UC1);
		Mat Kernel = Segment.Kernel(3, 0);
		Segment.Opening(img, Temp, Kernel);
		Segment.Opening(imgTop, TempTOP, Kernel);
		//imshow("Opened", Temp); //Uncomment to see image after opening

		Mat Kernel2 = Segment.Kernel(7, 0);
		Segment.Closing(Temp, img, Kernel2);
		Segment.Closing(TempTOP, imgTop, Kernel2);
		//imshow("Closed", img); //Uncomment to see image after Closing

		Mat BotCropped = Segment.Cropping(img, 9);
		Mat TopCropped = Segment.Cropping(imgTop, 9);
		Mat srcCropped = Segment.Cropping(src, 9);
		//imshow("TOPCropped", TopCropped); //Uncomment to see image after Cropping
		//imshow("BotCropped", BotCropped); //Uncomment to see image after Cropping
		//waitKey(10);

		//Blob Extraction
		std::vector<std::vector<cv::Point>> Blobs = BLOB.blob(BotCropped);
		std::vector<std::vector<cv::Point>> Blobs1 = BLOB.blob(TopCropped);

		test.training(srcCropped, BotCropped, Blobs,"pipes.txt",pipeVector);
		test.training(srcCropped, TopCropped, Blobs1, "obstacles.txt",obsVector);
			//Push struct to vector

		
	}
		
	

	
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

	//waitKey(0);
	return 0;
}

