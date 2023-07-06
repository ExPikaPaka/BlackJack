#pragma once

#include <SDL.h>
#include "..\TextureLoader\TextureLoader.h"

// Virtual Button interface 
class ButtonInterface {
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool selected() = 0;
};

// Button class
class Button : public ButtonInterface {
	SDL_Renderer* renderer;

	// Button texture
	SDL_Texture* buttonTex;

	// Button source & destination rectangles
	SDL_Rect srcrect, dstrect;

	// Mouse position & state
	SDL_Rect mouse;
	Uint32 mouseState;
	bool isSelected;

	// Variables to make delay between button clicks
	Uint32 clickStart, clickTime;
	int delay;

public:
	Button();


	// Initializes button with texture
	// I
	// Parameters:
	//     - x,y,w,h : button destination rectangle
	//     - ren         : pointer to the SDL_Renderer
	bool init(const char* texturePath, int x, int y, int w, int h, SDL_Renderer* ren);

	// Updates button state
	void update() override;

	// Draws button
	void draw() override;

	// Returns button state
		// I
		// Returns:
		//     - 'true'  : if mouse is on button & left mouse button is pressed
		//     - 'false' : otherwise
	bool selected() override;
};

