#include "Game\Game.h"

Game* game = nullptr;

#include "BlackJack/BlackJack.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    system("chcp 65001&cls");

    int FPS = 60; // Default FPS value

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--FPS" && i + 1 < argc) {
            FPS = std::stoi(argv[i + 1]); // Get the FPS value from the next argument
        }
    }

    game = new Game();
    game->init("BlackJack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, 0);

    const int frameDelay = 1000 / FPS;

    Uint32 frameStart, frameTime;
    Uint32 frameCount = 0;
    Uint32 fpsTimer = SDL_GetTicks(); // Initialize the timer with current ticks

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameCount++;

        // Calculate FPS every second
        if (SDL_GetTicks() - fpsTimer >= 1000) {
            std::string windowTitle = "BlackJack - FPS: " + std::to_string(frameCount);
            SDL_SetWindowTitle(game->getWindow(), windowTitle.c_str());

            frameCount = 0;
            fpsTimer = SDL_GetTicks(); // Reset the timer
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}



