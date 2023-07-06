#include <string>
#include "Game\Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
    // Change console code page to Unciode
    system("chcp 65001&cls");

    // Default FPS value
    int FPS = 60; 

    // Fullscreen mode
    bool fullscreen = false;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        // Get the FPS value from the next argument
        if (arg == "--FPS" && i + 1 < argc) {
            FPS = std::stoi(argv[i + 1]); 
        }

        if (arg == "--FULLSCREEN" && i + 1 < argc) {
            fullscreen = std::stoi(argv[i + 1]);
        }
    }

    // Initialize the game
    game = new Game();
    game->init("BlackJack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, fullscreen);

    const int frameDelay = 1000 / FPS;
    Uint32 frameStart, frameTime;
    Uint32 frameCount = 0;
    Uint32 fpsTimer = SDL_GetTicks(); // Initialize the timer with current ticks

    // Game loop
    while (game->running()) {
        frameStart = SDL_GetTicks();

        // Handle events, update game state, and render the frame
        game->handleEvents();
        game->update();
        game->render();

        frameCount++;

        // Calculate and display FPS every second
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