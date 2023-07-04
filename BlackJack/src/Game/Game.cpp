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
		
		background = TextureLoader::loadTexture("assets/img/background_green_dragon_victim.png", renderer);
		if (background) {
			std::cout << "[INFO] Background texture loaded." << std::endl;
		}

		if (btn.init("assets/img/hit.png", 700, 110, 90, 90, renderer)) {
			std::cout << "[INFO] Button created." << std::endl;
		}

		if (btn2.init("assets/img/stand.png", 700, 30, 90, 90, renderer)) {
			std::cout << "[INFO] Button created." << std::endl;
		}

		if (playerDrawer.init("assets/img/cards_classic.png", renderer, &blackJack.player, 20, 400, 200, 280, 1)) {
			std::cout << "[INFO] PlayerDrawer created." << std::endl;
		}

		audioManager.loadSound("button_click", "assets/audio/card_flip.wav");
		audioManager.playMusic("assets/audio/background_guitar_no_copyright.mp3");
		audioManager.setMusicVolume(40);
		
		

		blackJack.deck.init();
		blackJack.deck.shuffle();
		blackJack.player.init("Alex", 200);

		A.name = CardName::ACE;
		A.suit = Suit::CLUBS;
		A.value = 1;

		blackJack.player.addCardToHand(A);

		A.name = CardName::SIX;
		A.suit = Suit::DIAMONDS;
		A.value = 6;

		blackJack.player.addCardToHand(A);

		A.name = CardName::QUEEN;
		A.suit = Suit::HEARTS;
		A.value = 10;

		blackJack.player.addCardToHand(A);

		A.name = CardName::KING;
		A.suit = Suit::SPADES;
		A.value = 10;

		blackJack.player.addCardToHand(A);

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

		default:
			break;
	}
}

void Game::update() {
	btn.update();
	btn2.update();

	if (playerDrawer.animationStarted()) {
		audioManager.playSound("button_click");

	}

	if (btn.selected()) {
	
		A.name = CardName::KING;
		A.suit = Suit::SPADES;
		A.value = 10;

		if (!blackJack.deck.cards.empty()) {
			std::cout << "ADD CARD\n";
			blackJack.player.addCardToHand(blackJack.deck.cards.back()); /// CRASHES HEEEEERE
			blackJack.deck.cards.pop_back();
		}
	}
	if (btn2.selected()) {
		
		
	}

}

void Game::render() {
	SDL_RenderClear(renderer);

	SDL_Rect image;
	SDL_Rect screen;

	image.x = 0;
	image.y = 0;
	image.w = 1920;
	image.h = 1080;

	screen.x = 0;
	screen.y = 0;
	
	SDL_GetWindowSize(window, &screen.w, &screen.h);

	SDL_RenderCopy(renderer, background, &image, &screen);

	
	playerDrawer.drawHand();


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
