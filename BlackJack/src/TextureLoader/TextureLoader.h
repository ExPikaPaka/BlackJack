#pragma once

#include <SDL.h>
#include <SDL_image.h>

// Texture loader class
class TextureLoader {

public:
	// Loads texture from given filePath.
	// I
	// You can use TextureLoader::loadTexture(...) function without class object
	// due to the static function
	static SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
};

