#pragma once
#include <SDL.h>

// Timer class.
class Timer {
	Uint32 endTime;

public:
	Timer();

	// Sets timer active till endTime in milliseconds
	void setTimer(int endTimeMilliseconds);

	// Returns 'true' if currentTime < endTime. Otherwise returns 'false'
	bool active();

	// Sets renderEnd to 0, to make active() return 'false'
	void clear();
};