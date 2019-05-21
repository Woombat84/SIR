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


using namespace std;
using namespace cv;


int main()
{
	Pre_prossesing PrePross;
	Segmentation Segment;
	Blob_extration BLOB;
	feature Feature;
	std::fstream fs;
	string Classifier = "Class.txt";
	//C:\\Users\\Woombat\\Pictures\\P4\\tr.png
	for (int i = 1; i < 533; i++)
	{
		std::stringstream stream;
		
		stream << "C:\\Users\\dennis\\Pictures\\P4\\tr.png";
		
		Mat img = imread(stream.str(), IMREAD_GRAYSCALE | IMREAD_ANYDEPTH);
		Mat src = imread(stream.str(), IMREAD_GRAYSCALE);
		if (!img.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			return -1;
		}
		//imshow("Image", img); //Uncomment to see image before blurring
		//Mat new_image = Mat::zeros(img.rows,img.cols, CV_16UC1);
		//for (int y = 0; y < img.rows; y++) {
		//	for (int x = 0; x < img.cols; x++) {
		//		new_image.at<ushort>(y, x)=
		//				30 * img.at<ushort>(y, x) ;
		//	}
		//}
		//img = new_image;
		//imshow("B", new_image);
		//Pre-Prosessing
		PrePross.bluring(img, 5, 1);
		//imshow("Blurred", img); //Uncomment to see image after blurring
		//waitKey(1);
		//Segmentation
		Segment.Threshold(img, Segment.percent(img, 0.95));
		//imshow("Thresholded", img); //Uncomment to see image after thresholding


		Mat Temp = Mat(img.rows, img.cols, CV_8UC1); //Used for the output of the Morphology
		Mat Kernel = Segment.Kernel(7, 0);
		Segment.Opening(img, Temp, Kernel);
		//imshow("Opened", Temp); //Uncomment to see image after opening

		Mat Kernel2 = Segment.Kernel(5, 0);
		Segment.Closing(Temp, img, Kernel2);
		//imshow("Closed", img); //Uncomment to see image after Closing

		Mat Cropped = Segment.Cropping(img, 9);
		Mat srcCropped = Segment.Cropping(src, 9);
		//imshow("Cropped", Cropped); //Uncomment to see image after Cropping
		
		//Blob Extraction
		std::vector<std::vector<cv::Point>> Blobs = BLOB.blob(Cropped);
		
		
		//Feature Extraction
		vector<BlobFeatures> BLOBS;

		for (int i = 0; i < Blobs.size(); i++) {
			//Create instance of struct
			BlobFeatures Extract;
			float are = static_cast<float>(Blobs[i].size());
			cout << are << endl;
			//Add area to struct
			Extract.area = 1. / (1. + are);
			cout << "Area: " << Extract.area << endl;

			std::vector<cv::Point> perimeter;
			float per = Feature.perimeterBlob(Blobs[i], img.rows, img.cols, perimeter);
			//Add perimeter to struct
			
			Extract.perimeter = 1 / (1 + per);
			cout << "perimeter: " << Extract.perimeter << endl;
			//Bounding circle to struct
			
			Extract.boundingCircleRadius = 1 / (1.0 + Feature.BoundingCircle(Blobs[i], img.rows, img.cols, Extract.CoMX, Extract.CoMY));
			cout << "BCR: " << Extract.boundingCircleRadius << endl;
			cout << "COM X: " << Extract.CoMX << endl;
			cout << "COM Y: " << Extract.CoMY << endl;
			//Add circularity to struct
			
			Extract.circularity = 1 / (1.0 + Feature.BlobCircularity(Extract.area, Extract.perimeter));
			cout << "CR: " << Extract.circularity << endl;
			//Point of TopRigth corner and bottom left corner
			std::vector<cv::Point> BBpoints = Feature.BoundingBox(perimeter);

			//Add area of bounding box to struct
			Extract.boundingBoxArea = 1 / (1.0 + Feature.area(BBpoints));
			cout << "BBA: " << Extract.boundingBoxArea << endl;

			//Add the higth width ratio to struct
			Extract.heightWidthRatio = 1 / (1.0 + Feature.HeightWitdh(BBpoints));
			cout << "HWR: " << Extract.heightWidthRatio << endl;
			//Add the compactness of the blob to struct
			Extract.compactness = 1 / (1.0 + Feature.compactness(BBpoints, Blobs[i].size()));
			cout << "Compa: " << Extract.heightWidthRatio << endl;
			//drawing perimeter of what has to be trained
			
			
			for (int t = 0; t < perimeter.size() - 1; t++)
			{
				
				srcCropped.at<uchar>(perimeter[t].y, perimeter[t].x) = 255;
				
			}	//BLOBS.push_back(Extract);
			imshow("Training blob", srcCropped);
			waitKey(1);
			//selecting of what to do whit the data
			cout << "Traning data(1) or skip data(2)" << endl;
			int j = 0;
			cin >> j;
			if (j == 1) {
				//selecting if it is a fault or not
				cout << "Fault (1) or no faul (2) " << endl;
				int k = 0;
				cin >> k;
				if (k == 1) {
					int j = 0;

					cout << "The fault" << endl;
					cout << "Give the Fault a lable" << endl;
					cout << "Obstacle(1) Branch(2) Offset(3)" << endl;
					cin >> j;
					if (j == 1) {
						Extract.label = "Obstacles";
					}
					if (j == 2) {
						cout << "Up stream(1) Down stream(2)" << endl;
						int Br = 0;
						cin >> Br;
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
						Extract.label << endl;
					fs.close();
				}
				if (k == 2) {
					cout << "No fault" << endl;
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
						Extract.label << endl;
					fs.close();

				}
				else{}
				// traning data save to file
				destroyAllWindows();


			}
			else {}
			//Push struct to vector
			
		}
		

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

