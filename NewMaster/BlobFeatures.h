#pragma once

struct BlobFeatures {
	float area;
	float perimeter;
	float circularity;
	float boundingCircleRadius;
	float boundingBoxArea;
	float heightWidthRatio;
	float compactness;
	int CoMX;
	int CoMY;
	std::string label;
};