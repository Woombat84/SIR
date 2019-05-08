//Uncomment the following line if you are compiling this code in Visual Studio
//#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>
//

#include "prossecing.h"
///20190328_113102    IMG_20190402_093815
using namespace cv;
using namespace std;

String picName = "C:/Users/Dennis/rmstilprek.png";
Mat src; Mat src_gray;

prossecing P;

int main(int argc, char** argv)
{

	Mat src = imread("C:/Users/Dennis/Desktop/billdere/Course material-20190227/cr.png");

	/// Convert imagPe to gray and blur it

	/// Create Window
	String source_window = "Source";
	namedWindow(source_window, WINDOW_NORMAL);
	imshow(source_window, src);

	Mat a = P.greyscale(src);
	Mat b = P.threshold(a, 245);
	Mat c = b;
	namedWindow("Greyscaled", WINDOW_NORMAL);
	imshow("Greyscaled", a);
	namedWindow("Binary scaled", WINDOW_NORMAL);
	imshow("Binary scaled", c);

	std::vector<std::vector<cv::Point>> v = P.blob(b);

	/// Show in a window
	for (int k = 0; k < P.Perimetor.size(); k++) {
		for (int i = 0; i < P.Perimetor[k].size(); i++) {
			a.at<uchar>(P.Perimetor[k][i].y, P.Perimetor[k][i].x) = 0;

		}
	}
	namedWindow("perimetor", cv::WINDOW_NORMAL);
	imshow("perimetor", a);
	//namedWindow("Blobs left", WINDOW_NORMAL);
	//imshow("Blobs left", b);

	waitKey(10000);
	return(0);

}


/*
Mat threshold_output;
/// Detect edges using Threshold
threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);
Mat elem = getStructuringElement(MORPH_ELLIPSE, Size(50, 50));
morphologyEx(threshold_output, threshold_output, MORPH_OPEN, elem);
/// Find contours
Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
*/
