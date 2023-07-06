#pragma once

#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include "..\TextureLoader\TextureLoader.h"

enum class Suit {
    DIAMONDS,
    SPADES,
    HEARTS,
    CLUBS,
};

enum class CardName {
	ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
};

class Card {
public:
    Card();

    CardName name;
    Suit suit;
    int value;
    bool hidden;

    std::string getName();
    std::string getSuit();
};

class Deck {
public:
    std::vector<Card> cards;

    void init();
    void shuffle();

};

class Player {
    std::string name;
    int score;
    int balance;
    int bet;
    void updateScore();

public:
    std::vector<Card> hand;
    void init(std::string name, int startingBalance);

    void setName(std::string name);
    void setScore(int val);
    void setBalance(int val);
    void setBet(int bet);

    std::string getName();
    int getScore();
    int getBalance();
    int getBet();   

    void addCardToHand(Card& card);
    void clearHand();
};

class BlackJack {
public:
    Deck deck;
    Player dealer;
    Player player;

    // Returns:
    //      0 : draw
    //      1 : player win
    //     -1 : dealer win
    int checkWinner();
    void createNewGame();
};

class PlayerDrawer {
    SDL_Texture* deckTex;
    SDL_Renderer* renderer;
    Player* player;

    SDL_Rect srcCard;
    SDL_Rect dstScreen;
    
    int xStart, yStart;
    int cardWidth, cardHeight;

    float animatedCardY;
    int lastCardCount;
    int animationDirection;

    bool isAnimating;
    bool animating;
    bool block;

public:

    // First initialization.
    // animationDirection parameter:
    //    -1  : smooth appearance from top to bottom
    //     0  : no smooth appearence
    //     1  : smooth appearence from bottom to top
    bool init(std::string texturePath, SDL_Renderer* ren, Player* pl, int xStart, int yStart, int cardWidth, int cardHeight, int animationDirection);
    
    // Upload texture
    bool useTexture(std::string texturePath);

    // Clears variables used for hand drawing
    void clearHand();

    // Draws player hand. 
    void drawHand();

    // Returns true if any card started animating
    bool animationStarted();

    // Returns true if animating
    bool animatingStatus();

    int getXStart();
    int getYStart();
};

