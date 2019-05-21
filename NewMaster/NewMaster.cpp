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
	//C:\\Users\\Woombat\\Pictures\\P4\\tr.png
	for (int i = 1; i < 533; i++)
	{
		std::stringstream stream;
		
		stream << "C:\\Users\\dennis\\Pictures\\P4\\tr.png";
		
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
		PrePross.bluring(imgTop,5,0);
		//imshow("Blurred", img); //Uncomment to see image after blurring
	
		
		//Segmentation
		Segment.Threshold(img, Segment.percent(img, 0.95),1);
		Segment.Threshold(imgTop, Segment.percent(imgTop, 0.95),0);
		//imshow("Thresholded", img); //Uncomment to see image after thresholding

		Mat Temp = Mat(img.rows, img.cols, CV_8UC1); //Used for the output of the Morphology
		Mat Kernel = Segment.Kernel(7, 0);
		Segment.Opening(img, Temp, Kernel);
		Segment.Opening(imgTop, Temp, Kernel);
		//imshow("Opened", Temp); //Uncomment to see image after opening

		Mat Kernel2 = Segment.Kernel(5, 0);
		Segment.Closing(Temp, img, Kernel2);
		Segment.Closing(Temp, imgTop, Kernel2);
		//imshow("Closed", img); //Uncomment to see image after Closing

		Mat BotCropped = Segment.Cropping(img, 9);
		Mat TopCropped = Segment.Cropping(imgTop, 9);
		Mat srcCropped = Segment.Cropping(src, 9);
		//imshow("Cropped", Cropped); //Uncomment to see image after Cropping
		
		//Blob Extraction
		std::vector<std::vector<cv::Point>> Blobs = BLOB.blob(BotCropped);
		std::vector<std::vector<cv::Point>> Blobs1 = BLOB.blob(TopCropped);
		
		test.run(srcCropped, BotCropped, Blobs);
		test.run(srcCropped, TopCropped, Blobs);
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

