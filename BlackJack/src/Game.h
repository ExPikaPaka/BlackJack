#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "TextureLoader.h"

class Game {
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int cnt = 0;
	SDL_Texture* deckTexture;
	int x = 0;
	int y = 0;
public: 
	Game();
	~Game(); 

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();
};

