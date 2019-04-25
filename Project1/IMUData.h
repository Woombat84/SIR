#pragma once

#include <chrono>

class IMUData
{
public:
	IMUData();
	~IMUData(); 
	float Roll(float Xgyro);
	float Pitch(float Ygyro);
	void setCompFliter(float S);

private: // methodes
	void YZdeg(float& Y, float& Z);
	void XZdeg(float& X, float& Z);

	float highPass(float deg);

	float lowPass(float deg);


public:  // members


private: // members
	float yzDeg;
	float xzDeg;
	float compAccel = 0.05f;
	float compGyro = 1 - compAccel;
	std::chrono::steady_clock::time_point rollTime;
	std::chrono::steady_clock::time_point pitchTime;
	std::chrono::steady_clock::time_point oldRollTime;
	std::chrono::steady_clock::time_point oldPitchTime;

};

