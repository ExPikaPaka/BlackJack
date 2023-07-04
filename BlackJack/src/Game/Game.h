#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "..\TextureLoader\TextureLoader.h"
#include "..\Input\Button.h"
#include "..\Audio\AudioManager.h"
#include "..\BlackJack\BlackJack.h"

class Game {
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	AudioManager audioManager;
	PlayerDrawer playerDrawer;
	BlackJack blackJack;
	SDL_Texture* background;
	Button btn;
	Button btn2;


	Card A;
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

