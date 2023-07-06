#pragma once
#include <SDL.h>

class Timer {
	Uint32 renderEnd;

public:
	Timer();

	void setTimer(int milliseconds);
	bool active();

	void clear();

};

