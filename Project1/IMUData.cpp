#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include "IMUData.h"
#include <math.h>
#include <chrono>
#include<stdlib.h>
IMUData::IMUData()
{
	 oldRollTime = std::chrono::steady_clock::now();
	 oldPitchTime = std::chrono::steady_clock::now();
}


IMUData::~IMUData()
{
}
// Complimentary filtering of roll
float IMUData::Roll(float Xgyro)
{
	rollTime = std::chrono::steady_clock::now();
	float rT = float(std::chrono::duration_cast< std::chrono::nanoseconds> (rollTime - oldRollTime).count());
	rT = rT / 1e9;
	float roll = (xzDeg*compAccel)+((Xgyro * rT) *compGyro);
	oldRollTime = std::chrono::steady_clock::now();
	return roll;
}
// Complimentery filtering of pitch
float IMUData::Pitch(float Ygyro)
{	
	pitchTime = std::chrono::steady_clock::now();
	float pT = float(std::chrono::duration_cast<std::chrono::nanoseconds>(pitchTime - oldPitchTime).count());
	pT = pT / 1e9;
	float pitch = (yzDeg * compAccel) + ((Ygyro * pT) * compGyro);
	oldPitchTime = std::chrono::steady_clock::now();
	return pitch;
}
void IMUData::setCompFliter(float S)
{
	compAccel = S;


}
// Calculating the rotation of YZ plane
void IMUData::YZdeg(float& Y, float& Z)
{
	yzDeg = sin(abs(Z) / sqrtf(Y * Y + Z * Z));
}
// Calculating the rotaion  of XZ plane
void IMUData::XZdeg(float& X, float& Z)
{
	xzDeg = sin(abs(Z) / sqrtf(X * X + Z * Z));
}

