#include "TextRendererTimer.h"

TextRendererTimer::TextRendererTimer() : TextRenderer() {
	renderEnd = 0;
}

void TextRendererTimer::setTimer(int milliseconds) {
	renderEnd = SDL_GetTicks() + milliseconds;
}

bool TextRendererTimer::active() {
	return SDL_GetTicks() < renderEnd;
}
