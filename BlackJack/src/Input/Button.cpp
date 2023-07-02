#include "Button.h"

Button::Button() {
}

bool Button::init(const char* texturePath, int x, int y, int w, int h, SDL_Renderer* ren) {
	renderer = ren;
	texture = TextureLoader::loadTexture(texturePath, renderer);
	SDL_QueryTexture(texture, nullptr, nullptr, &srcrect.w, &srcrect.h);
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 100;
	
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = w;
	dstrect.h = h;

	mouse.w = 1;
	mouse.h = 1;

	isSelected = false;

	clickStart = 0;
	clickTime = 0;
	delay = 200;

	if (!texture) {
		return false;
	}
	return true;
}

void Button::update() {
	mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);

	// Move texture if mouse hover over button
	if (SDL_HasIntersection(&dstrect, &mouse)) {
		srcrect.x = srcrect.w;

		// Update click and move texture if button pressed
		clickStart = SDL_GetTicks();

		if (clickStart > clickTime + delay) {
			if (!isSelected && mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				srcrect.x = srcrect.w * 2;

				isSelected = true;

				clickTime = SDL_GetTicks();
			} else {
				isSelected = false;
			}
		} else {
			isSelected = false;
			srcrect.x = srcrect.w * 2;
		}
	} else {
		isSelected = false;
		srcrect.x = 0;

	}
}

void Button::draw() {
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

bool Button::selected() {
	return isSelected;
}
