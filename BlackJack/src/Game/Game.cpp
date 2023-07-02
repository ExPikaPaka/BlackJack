#include "Game.h"

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "[INFO] Subsystems Initialized." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "[INFO] Window created." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 35, 31, 42, 255);
			std::cout << "[INFO] Renderer created." << std::endl;
		}

		deckTexture = TextureLoader::loadTexture("assets/img/cards_classic.png", renderer);
		if (deckTexture) {
			std::cout << "[INFO] Textures loaded." << std::endl;
		}

		if (btn.init("assets/img/button.png", 20, 20, 400, 120, renderer)) {
			std::cout << "[INFO] Button created." << std::endl;
		}

		if (btn2.init("assets/img/button.png", 20, 200, 400, 120, renderer)) {
			std::cout << "[INFO] Button created." << std::endl;
		}

		audioManager.loadSound("1", "assets/audio/button_click.wav");
		audioManager.playMusic("assets/audio/Believer - Imagine Dragons - Violin VS Electric Guitar (Instrumental Cover).mp3");
		

		isRunning = true;
	} else {
		isRunning = false;
	}
}

void Game::handleEvents() {
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_q) {
				x--;
			}
			if (event.key.keysym.sym == SDLK_w) {
				x++;
			}
			if (event.key.keysym.sym == SDLK_a) {
				y--;
			}
			if (event.key.keysym.sym == SDLK_s) {
				y++;
			}
			if (x < 0) x = 0;
			if (x > 3) x = 3;
			if (y < 0) y = 0;
			if (y > 13) y = 13;
			break;
		default:
			break;
	}
}

void Game::update() {
	btn.update();
	btn2.update();

	if (btn.selected()) {
		audioManager.playSound("1");
	}
}

void Game::render() {
	SDL_RenderClear(renderer);


	SDL_Rect* cards = new SDL_Rect;
	SDL_Rect* bounding = new SDL_Rect;
	for (int i = 0; i < 4; i++) {
		cards->x = 359 * (x + i);
		cards->y = 501 * y;
		cards->w = 356;
		cards->h = 499;

		bounding->x = 264 / 2 * i;
		bounding->y = 0;
		bounding->w = 264;
		bounding->h = 370;
		SDL_RenderCopy(renderer, deckTexture, cards, bounding);
	}
	
	btn.draw();
	btn2.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "[INFO] Game Cleaned." << std::endl;
}

bool Game::running() {
	return isRunning;
}
