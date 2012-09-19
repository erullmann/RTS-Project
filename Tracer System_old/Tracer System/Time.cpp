#include "stdafx.h"
#include "SFML\System\Clock.hpp"
#include "Time.h"

int Time::fpsCap = 120;

float Time::GetTimeSinceLastFrame()
{
	sf::Time time;
	time = frameTime.GetElapsedTime();
	return (time.AsSeconds());
}

void Time::ResetFrameTime()
{
	frameTime.Restart();
}

float Time::GetTimerTime()
{
	sf::Time time;
	time = timerTime.GetElapsedTime();
	return (time.AsSeconds());
}

void Time::ResetTimerTime()
{
	timerTime.Restart();
}