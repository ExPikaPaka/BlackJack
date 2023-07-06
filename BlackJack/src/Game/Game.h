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

class Game {
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	AudioManager audioManager;
	TextRenderer textRenFS20;
	TextRendererTimer textRenFS50;
	TextRendererTimer textRenFS50Mes;
	TextRendererTimer textRenFS50Rules;
	Timer winTimer;
	Timer winMessageTimer;
	Timer dealerFlipCardTimer;
	Timer notEnoughMoneyTimer;

	SDL_Texture* backgroundTex;
	SDL_Texture* tableTex;
	SDL_Texture* menuBgTex;


	Button hitBtn;
	Button standBtn;
	Button bet10Btn;
	Button bet25Btn;
	Button bet50Btn;
	Button bet100Btn;
	Button bet500Btn;
	Button musicBtn;

	Button menuBtn;
	Button resumeBtn;
	Button newGameBtn;
	Button volumeBtn;
	Button exitBtn;

	Button skipTutorialBtn;

	// Sliders
	Slider musicVolumeSld;
	Slider soundVolumeSld;
	
	float currentMusicVolume;
	float currentSoundVolume;
	float previousMusicVolume;


	Button cardColWhiteBtn;
	Button cardColGreyBtn;
	Button cardColYellowBtn;
	Button cardColGreenRedBtn;
	Button cardColGoldBtn;
	std::vector<ButtonInterface*> buttons;
	std::vector<ButtonInterface*> menuButtons;

	bool playingMusic;
	bool playerTurn;
	bool displayMenu;

	PlayerDrawer playerDrawer;
	PlayerDrawer dealerDrawer;
	BlackJack blackJack;


	SDL_Rect srcTableRect;

	SDL_Rect winRect;
	SDL_Rect bgImageRect;

	SDL_Color white = { 230, 230 ,230 };
	SDL_Color lightGold = { 255, 236, 132 };
	SDL_Color lightBlue = { 150, 140, 234 };
	SDL_Color grey = { 71, 71, 71 };

	SDL_Rect messageRect = { 634, 335, 360, 61 };
	int xTextOffset = 15;
	int yTextOffset = 10;
	int textX = 0;
	int textY = 0;

	void standButtonLogic();
	void hitButtonLogic();
	void betButtonsLogic();

	void winnerLogic();
	void cardSkinLogic();
	void musicButtonLogic();
	
	void activateMoneyMessage();

	void renderWinMessage();
	void renderPlaceBetMessage();
	void renderRulesMessage();
	void renderNotEnoughMoneyMessage();

	void createANewLap();
	void startANewGame();
	void quitGame();
public: 
	Game();
	~Game(); 

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	SDL_Window* getWindow();
	bool running();
};

