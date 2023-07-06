#include "Button.h"

Button::Button() {
}

bool Button::init(const char* texturePath, int x, int y, int w, int h, SDL_Renderer* ren) {
	renderer = ren;

	// Load texture
	buttonTex = TextureLoader::loadTexture(texturePath, renderer);
	SDL_QueryTexture(buttonTex, nullptr, nullptr, &srcrect.w, &srcrect.h);

	// Rectangles initialization
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w /= 3;
	
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = w;
	dstrect.h = h;

	// Mouse width & height to check intersection on hover
	mouse.w = 1;
	mouse.h = 1;

	isSelected = false;

	clickStart = 0;
	clickTime = 0;
	delay = 200;

	// Return 'false' if error occurred during texture load
	if (!buttonTex) {
		return false;
	}

	// Return 'true' if button initialized successful
	return true;
}

void Button::update() {
	// Update mouse position & state
	mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);

	// Check if mouse has intersection with button rectangle
	if (SDL_HasIntersection(&dstrect, &mouse)) {
		// Move drawing texture position (second image in file)
		srcrect.x = srcrect.w;

		// Update click and move texture if button pressed
		clickStart = SDL_GetTicks();

		// Delay check
		if (clickStart > clickTime + delay) {
			// Update state if left mouse button is pressed
			if (!isSelected && mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				// Move drawing texture position (third image in file)
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
	// Render button texture
	SDL_RenderCopy(renderer, buttonTex, &srcrect, &dstrect);
}

bool Button::selected() {
	return isSelected;
}
