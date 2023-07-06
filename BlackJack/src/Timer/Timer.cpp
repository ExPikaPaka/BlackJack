#include "Timer.h"

Timer::Timer() {
	renderEnd = 0;
}

void Timer::setTimer(int milliseconds) {
	renderEnd = SDL_GetTicks() + milliseconds;
}

bool Timer::active() {
	return SDL_GetTicks() < renderEnd && renderEnd;
}

void Timer::clear() {
	renderEnd = 0;
}

