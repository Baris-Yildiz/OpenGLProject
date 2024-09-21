#pragma once
#include <chrono>


using namespace std::chrono;
class Animation
{
private:
	long long startTime;

	inline static long long getCurrentTimeInMiliseconds() {
		long long milis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		return milis;
	}
public:
	Animation();
	void SetStartTime();
	float GetPowerParameter(float coefficient, int power, float stopValue) const;
};

