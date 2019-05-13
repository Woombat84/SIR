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
	Mat img = imread("C:\\Users\\Dennis\\Desktop\\billdere\\Course material-20190227\\invSq.png", IMREAD_GRAYSCALE);
	if (!img.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	//imshow("Image", img); //Uncomment to see image before blurring
	
	//Pre-Prosessing
	PrePross.bluring(img, 5, 1);
	//imshow("Blurred", img); //Uncomment to see image after blurring

	//Segmentation
	Segment.Threshold(img, Segment.percent(img,1.0));
	//imshow("Thresholded", img); //Uncomment to see image after thresholding

	
	Mat Temp = Mat(img.rows, img.cols, CV_8UC1); //Used for the output of the Morphology
	Mat Kernel = Segment.Kernel(7, 0);
	Segment.Opening(img, Temp, Kernel);
	//imshow("Opened", Temp); //Uncomment to see image after opening

	Mat Kernel2 = Segment.Kernel(5, 0);
	Segment.Closing(Temp, img, Kernel2);
	//imshow("Closed", img); //Uncomment to see image after Closing

	Mat Cropped = Segment.Cropping(img, 7);
	//imshow("Cropped", Cropped); //Uncomment to see image after Cropping
		
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
		Extract.perimeter = 1/(1+Feature.perimeterBlob(Blobs[i], img.rows, img.cols,perimeter));

		//Bounding circle to struct
		Extract.boundingCircleRadius = 1 / (1 + Feature.BoundingCircle(Blobs[i], img.rows, img.cols, Extract.CoMX, Extract.CoMY));

		//Add circularity to struct
		Extract.circularity = 1 / (1 + Feature.BlobCircularity(Extract.area, Extract.perimeter));
		
		//Point of TopRigth corner and bottom left corner
		std::vector<cv::Point> BBpoints =  Feature.BoundingBox(perimeter);

		//Add area of bounding box to struct
		Extract.boundingBoxArea = 1 / (1 + Feature.area(BBpoints));

		
		//Add the higth width ratio to struct
		Extract.heightWidthRatio = 1 / (1 + Feature.HeightWitdh(BBpoints));
		//Add the compactness of the blob to struct
		Extract.compactness = 1 / (1 + Feature.compactness(BBpoints, Blobs[i].size()));
		cout << "Traning data(1) or test data(2)" << endl;
			int j = 0;
			cin >> j;
			if (j == 1) {
				cout << "Fault (1) or no faul (2) " << endl;
				int k = 0;
				cin >> k;
				if (k ==1 ) {
					cout << "The fault" << endl;
					cin >> Extract.label;
			
				}
				if (k == 2) {
					cout << "No fault" << endl;
					Extract.label = "No_fault";

				}
				else cout << "try again" << endl;
				// traning data save to file

			}
			else
		//Push struct to vector
		BLOBS.push_back(Extract);		
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

	waitKey(0);
	return 0;
}

