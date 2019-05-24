#pragma once

struct BlobFeatures {
	float area;
	float perimeter;
	float circularity;
	float boundingCircleRadius;
	float boundingBoxArea;
	float heightWidthRatio;
	float compactness;
	float CoMX;
	float CoMY;
	std::string label;
};

struct DistFeatures {
	double dist;
	std::string label;
};