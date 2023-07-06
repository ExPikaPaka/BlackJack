#pragma once

#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include "..\TextureLoader\TextureLoader.h"

// Card suit enumeration
enum class Suit {
    DIAMONDS,
    SPADES,
    HEARTS,
    CLUBS,
};

// Card name enumeration
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

// Card class
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

// Deck class
class Deck {
public:
    std::vector<Card> cards;

    // Initializes a new deck of cards with 'usual' order
    void init();

    // Mixes cards in the deck
    void shuffle();

};

// Game Player class
class Player {
private: 
    std::string name;

    // Player hand value
    int score;

    int balance;
    int bet;

    // Updates player hand value
    void updateScore();

public:
    // Player's cards in 'hand'
    std::vector<Card> hand;

    // Initializes player with specified name & balance
    void init(std::string name, int startingBalance);

    void setName(std::string name);
    void setScore(int val);
    void setBalance(int val);
    void setBet(int bet);

    std::string getName();
    int getScore();
    int getBalance();
    int getBet();   

    // Adds card to players 'hand'
    void addCardToHand(Card& card);

    // Removes all cards from 'hand'
    void clearHand();
};

// BlackJack Game class
class BlackJack {
public:
    // Deck of cards
    Deck deck; 

    Player dealer;
    Player player;

    // Determines winner trough dealer's & player's 'hand' value
    // Returns:
    //      0 : draw
    //      1 : player win
    //     -1 : dealer win
    int checkWinner();

    // Creates a new mixed deck of cards. Clearers player's & dealer's 'hand'.
    void createNewGame();
};

// Game PlayerDrawer class. Renders player's hand on screen with/without animation
class PlayerDrawer {
public:
    // Initializes drawer with specified texture, given location & animation state.
    // I
    // Parameters:
    //     pl                    : Pointer to the player
    //     xStart, yStart        : top left rendering position of the 'hand' 
    //     cardWidth, cardHeight : width & height of one card, rendered on screen
    // I
    // animationDirection:
    //    -1  : Smooth appearance from top to bottom
    //     0  : No smooth appearance
    //     1  : Smooth appearance from bottom to top
    bool init(std::string texturePath, SDL_Renderer* ren, Player* pl, int xStart, int yStart, int cardWidth, int cardHeight, int animationDirection);
    
    // Upload texture
    bool useTexture(std::string texturePath);

    // Clears variables used for hand drawing
    void clearHand();

    // Draws player hand. 
    void drawHand();

    // Returns true if any card started animating
    bool animationStarted();

    // Returns true if currently animating
    bool animatingStatus();

    // Return top left render position
    int getXStart();
    // Return top left render position
    int getYStart();

private:
    SDL_Renderer* renderer;

    // Card deck texture
    SDL_Texture* deckTex;

    // Pointer to the player
    Player* player;

    // Card source & destination rectangles
    SDL_Rect srcCard;
    SDL_Rect dstScreen;

    // Top left render position
    int xStart, yStart;

    // Width & height of on card on screen
    int cardWidth, cardHeight;

    // Current Y position of card, that is animating
    float animatedCardY;

    // Number of the card, that is animating
    int lastCardCount;

    // Animating direction.
    //    -1  : Smooth appearance from top to bottom
    //     0  : No smooth appearance
    //     1  : Smooth appearance from bottom to top
    int animationDirection;

    // Trigger-bool on beginning of a new card animation
    bool animatingStartedbl;

    // Current animating status
    bool animating;

    // Used for trigger-bool
    bool block;
};

