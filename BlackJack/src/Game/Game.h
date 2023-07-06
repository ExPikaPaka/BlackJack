#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "..\TextureLoader\TextureLoader.h"
#include "..\Input\Button.h"
#include "..\Input\Slider.h"
#include "..\Audio\AudioManager.h"
#include "..\BlackJack\BlackJack.h"
#include "..\Text\TextRenderer.h"
#include "..\Text\TextRendererTimer.h"
#include "..\Timer\Timer.h"

// BlackJack game class
class Game {
public: 
	Game();
	~Game(); 

	// Initializes game.
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	// Handle events
	void handleEvents();

	// Updates game logic
	void update();

	// Renders frame
	void render();

	// Frees resources 
	void clean();

	// Returns pointer to the SDL_Window
	SDL_Window* getWindow();

	// Returns current game state
	// I
	// Returns:
	//     - 'true'  : If game is running
	//     - 'false' : If close event handled
	bool running();

public:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Audio mixer
	AudioManager audioManager;

	// Text renderers. 'FS' stand for 'FontSize'
	TextRenderer textRenFS20;
	TextRendererTimer textRenFS50;
	TextRendererTimer textRenFS50Message;
	TextRendererTimer textRenFS50Rules;

	// Timers for displaying different messages
	Timer winTimer;
	Timer winMessageTimer;
	Timer dealerFlipCardTimer;
	Timer notEnoughMoneyTimer;

	// Menu, background, bet & score table textures
	SDL_Texture* backgroundTex;
	SDL_Texture* tableTex;
	SDL_Texture* menuBgTex;

	// Hit & Stand buttons
	Button hitBtn;
	Button standBtn;

	// Bet buttons
	Button bet10Btn;
	Button bet25Btn;
	Button bet50Btn;
	Button bet100Btn;
	Button bet500Btn;

	// Music mute button
	Button musicBtn;

	// Menu buttons
	Button menuBtn;
	Button resumeBtn;
	Button newGameBtn;
	Button volumeBtn;
	Button exitBtn;

	// Transparent button, to skip tutorial message on startup
	Button skipTutorialBtn;

	// Volume sliders in menu
	Slider musicVolumeSld;
	Slider soundVolumeSld;

	// Music & sound volume in SoundManager 
	float currentMusicVolume;
	float currentSoundVolume;
	float previousMusicVolume;

	// Card deck skin changing buttons
	Button cardColWhiteBtn;
	Button cardColGreyBtn;
	Button cardColYellowBtn;
	Button cardColGreenRedBtn;
	Button cardColGoldBtn;

	// Gameplay button array
	std::vector<ButtonInterface*> buttons;
	// Menu button array
	std::vector<ButtonInterface*> menuButtons;

	// Gameplay state flags
	bool playingMusic;
	bool playerTurn;
	bool displayMenu;

	// Card deck drawers
	PlayerDrawer playerDrawer;
	PlayerDrawer dealerDrawer;


	// BlackJack logic object
	BlackJack blackJack;
	

	// Bet & score table rectangle
	SDL_Rect srcTableRect;

	// Winner message rectangle
	SDL_Rect winRect;

	// BackGround image rectangle
	SDL_Rect bgImageRect;

	// Message rectangle
	SDL_Rect messageRect = { 634, 335, 360, 61 };


	// Colors used for TextRenderer objects (messages)
	SDL_Color white = { 230, 230 ,230 };
	SDL_Color lightGold = { 255, 236, 132 };
	SDL_Color lightBlue = { 150, 140, 234 };
	SDL_Color grey = { 71, 71, 71 };

	// TextRenderer (messages) variables
	int xTextOffset = 15;
	int yTextOffset = 10;
	int textX = 0;
	int textY = 0;



	// Performs 'Stand' button logic if button is selected
	void standButtonLogic();

	// Performs 'Hit' button logic if button is selected
	void hitButtonLogic();

	// Performs 'bet' buttons logic if button is selected 
	void betButtonsLogic();

	// Determines winner, transfers money, displays score,
	// and activates winner message timer if 'Stand' button selected
	void winnerLogic();

	// Reloads card deck texture  if button is selected
	void cardSkinLogic();

	// Mutes music if button is selected
	void musicButtonLogic();


	// Activates 'Not enough money' message, if player is trying
	// to place a bet bigger than player's balance
	void activateMoneyMessage();


	// Renders winner message
	void renderWinMessage();

	// Renders 'Place a bet' message, if player is trying to start
	// a game, with zero bet
	void renderPlaceBetMessage();

	// Renders rules on startup. Player can skip, by clicking 
	// anywhere on game screen
	void renderRulesMessage();

	// Renders 'Not enough money' message
	void renderNotEnoughMoneyMessage();


	// Creates a new game lap, when player or dealer wins.
	void createANewLap();

	// Starts a new game. Clears player score, balance.
	void startANewGame();

	// Creates 'Exit' event
	void quitGame();
};

