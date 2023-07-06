#include "TextRenderer.h"

TextRenderer::TextRenderer() {
}

TextRenderer::~TextRenderer() {
    // Cleanup resources
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);
}

bool TextRenderer::init(const std::string& fontPath, int fontSize, SDL_Renderer* renderer) {
    font = nullptr;
    texture = nullptr;
    textSurface = nullptr;
    this->renderer = renderer;

    bool isError = false;

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        std::cerr << "[ERROR] Couldn't initialize sdl_ttf.lib" << std::endl;
        isError = true;
    }

    setFont(fontPath, fontSize);
    
    // Return 'true' if success. Otherwise 'false'
    return !isError;
}

void TextRenderer::setFontSize(int size) {
    // Reload current font with specified size
    font_size = size;
    TTF_CloseFont(font);
    font = TTF_OpenFont(fontPath.c_str(), size);
    if (!font) {
        std::cerr << "[ERROR] Couldn't load font. Font: " << fontPath << std::endl;
    }
}

bool TextRenderer::setFont(const std::string& fontPath, int fontSize) {
    // Reload current font with new one, with specified size
    bool isError = false;
    TTF_CloseFont(font);

    // Load the font
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "[ERROR] Couldn't load font. Font: " << fontPath << std::endl;
    }
    this->fontPath = fontPath;
    this->font_size = fontSize;

    // Return 'true' if success. Otherwise 'false'
    return !isError;
}

void TextRenderer::renderText(const std::string& text, int x, int y, SDL_Color textColor) {
    // Create a surface with the rendered text
    textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "[ERROR] Couldn't create textSurface during text rendering" << std::endl;
        return;
    }

    // Create a texture from the surface
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!texture) {
        std::cerr << "[ERROR] Couldn't create textTexture during text rendering" << std::endl;
        return;
    }

    // Render the texture
    SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    // Free resources
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);
}

void TextRenderer::renderText(const std::string& text, int x, int y, SDL_Color textColor, int fontSize) {
    // Renders text with specified size
    setFontSize(fontSize);
    renderText(text, x, y, textColor);
}

