#pragma once

#include <SDL.h>
#include "..\TextureLoader\TextureLoader.h"

// Button interface used for draw function
class ButtonInterface {
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool selected() = 0;
};

class Button : public ButtonInterface {
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
	void update() override;
	void draw() override;
	bool selected() override;
};

