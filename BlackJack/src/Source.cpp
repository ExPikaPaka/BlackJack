#include "Game\Game.h"

Game* game = nullptr;

#include "BlackJack/BlackJack.h"
int main(int argc, char* argv[]) {
	system("chcp 65001&cls");

	game = new Game();
	game->init("BlackJack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, 0);

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart, frameTime;

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}


