#include "Game.h"


Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game();
	game->init("BlackJack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}