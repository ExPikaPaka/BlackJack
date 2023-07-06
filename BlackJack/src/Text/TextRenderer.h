#pragma once
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class TextRenderer {
    std::string fontPath;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Surface* textSurface;
    SDL_Renderer* renderer;

    int font_size;

public:
    TextRenderer();
    ~TextRenderer();

    bool init(const std::string& fontPath, int fontSize, SDL_Renderer* renderer);

    bool setFont(const std::string& fontPath, int fontSize);
    void setFontSize(int size);
    void renderText(const std::string& text, int x, int y, SDL_Color textColor);
    void renderText(const std::string& text, int x, int y, SDL_Color textColor, int fontSize);
};
