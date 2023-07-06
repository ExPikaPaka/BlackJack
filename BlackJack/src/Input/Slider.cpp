#include "Slider.h"

Slider::Slider() {
}

bool Slider::init(const char* rodTexturePath, int rx, int ry, int rw, int rh,
				  const char* sliderTexturePath, int sx, int sy, int sw, int sh, SDL_Renderer* ren) {
	renderer = ren;

	// Loading rod texture
	rodTex = TextureLoader::loadTexture(rodTexturePath, renderer);
	SDL_QueryTexture(rodTex, nullptr, nullptr, &rodSrcRect.w, &rodSrcRect.h);
	rodSrcRect.x = 0;
	rodSrcRect.y = 0;
	rodSrcRect.w /= 3;

	rodDstRect.x = rx;
	rodDstRect.y = ry;
	rodDstRect.w = rw;
	rodDstRect.h = rh;

	// Loading slider texture
	sliderTex = TextureLoader::loadTexture(sliderTexturePath, renderer);
	SDL_QueryTexture(sliderTex, nullptr, nullptr, &sliderSrcRect.w, &sliderSrcRect.h);
	sliderSrcRect.x = 0;
	sliderSrcRect.y = 0;
	sliderSrcRect.w /= 3;

	sliderDstRect.x = sx;
	sliderDstRect.y = sy;
	sliderDstRect.w = sw;
	sliderDstRect.h = sh;

	mouse.w = 1;
	mouse.h = 1;

	isSelected = false;

	clickStart = 0;
	clickTime = 0;
	delay = 200;

	if (!rodTex || !sliderTex) {
		return false;
	}

	return true;
}

void Slider::update() {
	mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_HasIntersection(&rodDstRect, &mouse) || SDL_HasIntersection(&sliderDstRect, &mouse)) {
		rodSrcRect.x = rodSrcRect.w;
		rodSrcRect.x = rodSrcRect.w;

		sliderSrcRect.x = sliderSrcRect.w;
		sliderSrcRect.x = sliderSrcRect.w;

		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			if (!isSelected) {
				isSelected = true;
				clickStart = SDL_GetTicks();
			}

			sliderSrcRect.x = sliderSrcRect.w * 2;
			sliderSrcRect.x = sliderSrcRect.w * 2;

			Uint32 clickDuration = SDL_GetTicks() - clickStart;

			// Calculate the new slider position based on the mouse movement
			int newSliderPosX = mouse.x - sliderDstRect.w / 2;

			// Limit the slider position by the rod dimensions
			if (newSliderPosX < rodDstRect.x) {
				newSliderPosX = rodDstRect.x;
			}
			if (newSliderPosX > rodDstRect.x + rodDstRect.w - sliderDstRect.w) {
				newSliderPosX = rodDstRect.x + rodDstRect.w - sliderDstRect.w;
			}

			// Update the slider position
			sliderDstRect.x = newSliderPosX;

			// Update the click start time if the slider position changes
			if (newSliderPosX != sliderDstRect.x) {
				clickStart = SDL_GetTicks();
			}
		}
	} else {
		isSelected = false;
		rodSrcRect.x = 0;
		sliderSrcRect.x = 0;
	}
}



void Slider::draw() {
	SDL_RenderCopy(renderer, rodTex, &rodSrcRect, &rodDstRect);
	SDL_RenderCopy(renderer, sliderTex, &sliderSrcRect, &sliderDstRect);
}

bool Slider::selected() {
	return isSelected;
}

float Slider::getValue() {
	int sliderRange = rodDstRect.w - sliderDstRect.w;
	int sliderPos = sliderDstRect.x - rodDstRect.x;
	return (float)(sliderPos) / (float)sliderRange;
}

void Slider::setValue(float value) {
	// Calculate the new position for the slider
	int sliderRange = rodDstRect.w - sliderDstRect.w;
	int newSliderPos = rodDstRect.x + (int)(value * sliderRange);

	// Update the slider position
	sliderDstRect.x = newSliderPos;
}
