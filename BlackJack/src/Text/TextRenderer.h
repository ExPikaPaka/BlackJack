#pragma once
#include <SDL_ttf.h>
#include <string>
#include <iostream>

// .ttf TextRenderer class
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

    // Initializes object with font, font size
    // I
    // Parameters:
    //     - fontPath : path to the .ttf font
    //     - fontSize : font size 
    //     - renderer : pointer to the SDL_Renderer object
    // I
    // Returns:
    //     - 'true'   : if initialization was succesful
    //     - 'false'  : otherwise (error during file operations)
    bool init(const std::string& fontPath, int fontSize, SDL_Renderer* renderer);

    // Reloads current font with new one
    bool setFont(const std::string& fontPath, int fontSize);

    // Changes font size (current font reload with specified size)
    void setFontSize(int size);

    // Renders text on specified place, with given color
    void renderText(const std::string& text, int x, int y, SDL_Color textColor);

    // Changes font size & renders on specified place, with given color
    void renderText(const std::string& text, int x, int y, SDL_Color textColor, int fontSize);
};
