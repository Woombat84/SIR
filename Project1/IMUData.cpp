/*
%
% This Header Cpp files IMUDATA is used to calculate an oriantation of a sewer robot, through an IMU sensor
% that is placed whit-in an Intel RealSense d435i.
%
% Author1: 19gr466
%  
% Date : Spring 2019
% Course : Rob4 Computervision
%
*/
#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include "IMUData.h"
#include <math.h>
#include <chrono>

/*
% Function : Constructor
%
% Description : Every time a object is created from IMUDATA this constructer is called.
%				This function initats the timer oldRollTime and oldPitchTime
% Parameters : non.
%
% Return : nothing.
%
*/

IMUData::IMUData()
{
	 oldRollTime = std::chrono::steady_clock::now();
	 oldPitchTime = std::chrono::steady_clock::now();
}

/*
% Function : Deconstructor
%
% Description : When the program shuts down or the object of IMUDATA is deleted, this
%				this function is called. Nothing is happening here.
%				
% Parameters : non.
%
% Return : nothing.
%
*/
IMUData::~IMUData()
{
}
/*
% Function : Complimentary filtering of roll
%
% Description : This function returns a estemated roll oriantation in degrees 
%				chrono is used to find the time passed between each meassurements,
%				this is used to intergrat in discret time.
%
% Parameters : Rotation about the X axis of the gyro.
%
% Return : est of the Roll in a float.
%
*/ 
float IMUData::Roll(float Xgyro)
{		
	//End timer to find the time passed
	rollTime = std::chrono::steady_clock::now();
	float rT = float(std::chrono::duration_cast< std::chrono::nanoseconds> (rollTime - oldRollTime).count());
	//Converting from nanosec to sec. 1e9 = 1.000.000.000
	rT = rT / 1e9;
	//Complimentary filtering
	float roll = (xzDeg*compAccel)+((Xgyro * rT) *compGyro);
	//Resting in timer
	oldRollTime = std::chrono::steady_clock::now();
	return roll;
}
/*
% Function : Complimentary filtering of Pitch.
%
% Description : This function returns a estemated Pitch oriantation in degrees
%				chrono is used to find the time passed between each meassurements,
%				this is used to intergrat in discret time.
%
% Parameters : Rotation about the Y axis of the gyro.
%
% Return : est of the Pitch in a float.
%
*/
float IMUData::Pitch(float Ygyro)
{	
	//End timer to find the time passed
	pitchTime = std::chrono::steady_clock::now();
	float pT = float(std::chrono::duration_cast<std::chrono::nanoseconds>(pitchTime - oldPitchTime).count());
	
	//Converting from nanosec to sec. 1e9 = 1.000.000.000
	pT = pT / 1e9;
	
	//Complimentary filtering
	float pitch = (yzDeg * compAccel) + ((Ygyro * pT) * compGyro);
	
	//Resting in timer
	oldPitchTime = std::chrono::steady_clock::now();
	
	return pitch;
}
/*
% Function : Complimentary filtering of Pitch.
%
% Description : This function sets the amount of acceleration components is used in complimentary filter
%
%
% Parameters : A float between 0.0f - 1.0f.
%
% Return : nothing.
%
*/
void IMUData::setCompFliter(float S)
{
	compAccel = S;


}
/*
% Function : Calculating the rotation of YZ plane.
%
% Description : This function returns a estemated Pitch oriantation in degrees from the accelerometer alone.
%
%
% Parameters : Acceleration in Y and Z direction.
%
% Return : Nothing.
%
*/
void IMUData::YZdeg(float& Y, float& Z)
{
	yzDeg = sin(abs(Z) / sqrtf(Y * Y + Z * Z));
}

/*
% Function : Calculating the rotation of XZ plane.
%
% Description : This function returns a estemated Pitch oriantation in degrees from the accelerometer alone.
%
%
% Parameters : Acceleration in X and Z direction.
%
% Return : Nothing.
%
*/
void IMUData::XZdeg(float& X, float& Z)
{
	xzDeg = sin(abs(Z) / sqrtf(X * X + Z * Z));
}

/*
% Function : High pass Filtering .
%
% Description : This function returns a high-pass filtered signal.
%
%
% Parameters : A deg that needs filtering.
%
% Return : A filterede float.
%
*/
float IMUData::highPass(float deg)
{
	return 0.0f;
}


/*
% Function : Low pass Filtering .
%
% Description : This function returns a low-pass filtered signal.
%
%
% Parameters : A deg that needs low-pass filtering.
%
% Return : A filterede float.
%
*/
float IMUData::lowPass(float deg)
{

	return 0.0f;
}