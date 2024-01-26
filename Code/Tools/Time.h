#pragma once
#include <ctime>

// Calculates time between two frames (delta time). Computers have got different operation times.
class Time 
{
public:
	static double DeltaTime();
private:
	static double priviousTime;
	static double currentTime;
	static const int MILLISEC_IN_SEC = 1000;
};