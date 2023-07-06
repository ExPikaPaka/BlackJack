#include "Timer.h"

Timer::Timer() {
	endTime = 0;
}

void Timer::setTimer(int endTimeMilliseconds) {
	endTime = SDL_GetTicks() + endTimeMilliseconds;
}

bool Timer::active() {
	return SDL_GetTicks() < endTime && endTime;
}

void Timer::clear() {
	endTime = 0;
}

