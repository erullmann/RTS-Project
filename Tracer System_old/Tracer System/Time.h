#pragma once
#include "stdafx.h"
#include "SFML\System\Clock.hpp"

class Time
{
public:
	float GetTimeSinceLastFrame(); // returns time, in secounds, since last frame

	void ResetFrameTime(); // must be called every frame

	float GetTimerTime(); // returns current time in secounds

	void ResetTimerTime(); // resets timer

private:
	sf::Clock frameTime; // holds frame time

	sf::Clock timerTime; // holds timer time

	static int fpsCap;
};