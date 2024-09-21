#include "Animation.h"
#include "math.h"

Animation::Animation() : startTime(0)
{
	
}

void Animation::SetStartTime()
{
	startTime = getCurrentTimeInMiliseconds();
}

float Animation::GetPowerParameter(float coefficient, int power, float stopValue) const
{
	long long timeNow = getCurrentTimeInMiliseconds();
	float timeElapsed = (timeNow - startTime) / 1000.0f;

	float parameter = coefficient * pow(timeElapsed, power);
	return parameter > stopValue ? stopValue: parameter;
}
