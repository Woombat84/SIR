#pragma once

struct BlobFeatures {
	int area;
	int perimeter;
	float circularity;
	float boundingCircle;
	float boundingBox;
	float heightWidthRatio;
};