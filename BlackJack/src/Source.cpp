#include "Game\Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	system("chcp 65001&cls");

	game = new Game();
	game->init("BlackJack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, 0);

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

/*	SDL_Init(SDL_INIT_EVERYTHING);

	int numDevices = SDL_GetNumAudioDevices(0);
	if (numDevices < 1) {
		std::cerr << "No audio devices found." << std::endl;
	}

	// Print the names of the available audio devices
	std::cout << "Available audio devices:" << std::endl;
	for (int i = 0; i < numDevices; ++i) {
		const char* deviceName = SDL_GetAudioDeviceName(i, 0);
		std::cout << "Device " << i << ": " << deviceName << std::endl;
	}*/