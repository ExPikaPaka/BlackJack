#pragma once
#include <SDL.h>
#include "..\TextureLoader\TextureLoader.h"

class Slider {
	SDL_Renderer* renderer;
	SDL_Texture* rodTex;
	SDL_Texture* sliderTex;
	SDL_Rect rodSrcRect, rodDstRect;
	SDL_Rect sliderSrcRect, sliderDstRect;
	SDL_Rect mouse;
	SDL_Point lastMousePos; // Store the previous mouse position
	Uint32 mouseState;
	bool isSelected;

	// Variables to make delay between button clicks
	Uint32 clickStart, clickTime;
	int delay;
public:

	Slider();

	bool init(const char* rodTexturePath, int rx, int ry, int rw, int rh, 
			  const char* sliderTexturePath, int sx, int sy, int sw, int sh, SDL_Renderer* ren);
	void update();
	void draw();
	bool selected();

	float getValue();
	void setValue(float value);
};

