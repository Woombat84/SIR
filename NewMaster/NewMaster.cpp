#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
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


	Mat img = imread("C:\\Users\\Jonathan\\Pictures\\TestSquare.png", IMREAD_GRAYSCALE);
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
	Segment.Threshold(img, Segment.percent(img,0.2));
	//imshow("Thresholded", img); //Uncomment to see image after thresholding

	
	Mat Temp = Mat(img.rows, img.cols, CV_8UC1); //Used for the output of the Morphology
	Mat Kernel = Segment.Kernel(7, 0);
	Segment.Opening(img, Temp, Kernel);
	//imshow("Opened", Temp); //Uncomment to see image after opening

	Mat Kernel2 = Segment.Kernel(5, 0);
	Segment.Closing(Temp, img, Kernel2);
	//imshow("Closed", img); //Uncomment to see image after Closing
	
	//Blob Extraction
	std::vector<std::vector<cv::Point>> Blobs = BLOB.blob(img);

	//Feature Extraction
	vector<BlobFeatures> BLOBS;
	
	for (int i = 0; i < Blobs.size(); i++) {
		//Create instance of struct
		BlobFeatures Extract;
		
		//Add area to struct
		Extract.area = Blobs[i].size();
		
		//Add perimeter to struct
		//Extract.perimeter = Feature.perimeterBlob(Blobs[i], img.rows, img.cols);

		//Bounding circle to struct
		Extract.boundingCircle = Feature.BoundingCircle(Blobs[i], img.rows, img.cols);

		//Add circularity to struct
		//Extract.circularity = Feature.BlobCircularity(Extract.area, Extract.perimeter);
		
		//TODO add bouding box to struct
		//TODO add height width ratio to struct

		//Push struct to vector
		BLOBS.push_back(Extract);		
	}

	/* For Debugging 
	cout << "BLOBS.size() = ";
	cout << BLOBS.size() << endl;
	for (int i = 0; i < BLOBS.size(); i++) {
		cout << "BLOB" << i << " ";
		cout << BLOBS[i].perimeter << endl;
		waitKey(2000);
	}

	*/

	

	//Classification
		//TODO Compare structs to training data

	waitKey(0);
	return 0;
}

