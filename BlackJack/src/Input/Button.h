#pragma once

#include <SDL.h>
#include "..\TextureLoader\TextureLoader.h"

class Button {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect srcrect, dstrect;
	SDL_Rect mouse;
	Uint32 mouseState;
	bool isSelected;

	// Variables to make delay between button clicks
	Uint32 clickStart, clickTime;
	int delay;
public:

	Button();

	bool init(const char* texturePath, int x, int y, int w, int h, SDL_Renderer* ren);
	void update();
	void draw();
	bool selected();
};

