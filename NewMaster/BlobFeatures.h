#pragma once

struct BlobFeatures {
	int area;
	int perimeter;
	float circularity;
	float boundingCircleRadius;
	int boundingBoxArea;
	float heightWidthRatio;
	float compactness;
	int CoMX;
	int CoMY;
	std::string label;
};