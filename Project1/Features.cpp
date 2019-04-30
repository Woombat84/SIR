#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include "Features.h"



Features::Features()
{
}


Features::~Features()
{
}

float Features::BlobCircularity(int BlobArea, int BlobPerimeter)
{
	float Circularity = (4 * PI * BlobArea) / (BlobPerimeter * BlobPerimeter);
	return Circularity;
}
