#pragma once
#include <SDL.h>
#include "..\TextureLoader\TextureLoader.h"

// Slider class
class Slider {
	SDL_Renderer* renderer;
	
	// Textures
	SDL_Texture* rodTex;
	SDL_Texture* sliderTex;

	// Boundaries 
	SDL_Rect rodSrcRect, rodDstRect;
	SDL_Rect sliderSrcRect, sliderDstRect;

	// Mouse position
	SDL_Rect mouse;
	SDL_Point lastMousePos; 
	Uint32 mouseState;

	// Slider state
	bool isSelected;

	// Variables to make delay between button clicks
	Uint32 clickStart, clickTime;
	int delay;
public:

	Slider();

	// Initializes slider with rod & slider textures
	// I
	// Parameters:
	//     - rx,ry,rw,rh : rod destination rectangle
	//     - sx,sy,sw,sh : slider destination rectangle
	//     - ren         : pointer to the SDL_Renderer
	bool init(const char* rodTexturePath, int rx, int ry, int rw, int rh, 
			  const char* sliderTexturePath, int sx, int sy, int sw, int sh, SDL_Renderer* ren);

	// Updates slider state & position
	void update();

	// Draws slider
	void draw();

	// Returns slider state
	// I
	// Returns:
	//     - 'true'  : if mouse is on slider & left mouse button is pressed
	//     - 'false' : otherwise
	bool selected();

	// Returns slider value in range [0,1]
	float getValue();

	// Sets slider value & slider position to the specified percentage in range [0,1]
	void setValue(float value);
};

