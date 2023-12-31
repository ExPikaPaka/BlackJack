#include "Game.h"

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	// Window flags
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// SDL components initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "[INFO] Subsystems Initialized." << std::endl;

		// Creating game window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// Display info, if window created successful
		if (window) {
			std::cout << "[INFO] Window created." << std::endl;

			winRect.x = 0;
			winRect.y = 0;
			winRect.w = width;
			winRect.h = height;
		}

		// Creating SDL renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
			std::cout << "[INFO] Renderer created." << std::endl;
		}
		


		// Loading background image texture
		backgroundTex = TextureLoader::loadTexture("assets/img/background_green_dragon_light.png", renderer);
		if (backgroundTex) {
			std::cout << "[INFO] Background texture loaded." << std::endl;

			bgImageRect.x = 0;
			bgImageRect.y = 0;
			SDL_QueryTexture(backgroundTex, nullptr, nullptr, &bgImageRect.w, &bgImageRect.h);
		}

		// Loading bet & score table texture
		tableTex = TextureLoader::loadTexture("assets/img/table.png", renderer);
		if (tableTex) {
			std::cout << "[INFO] Table texture loaded." << std::endl;

			srcTableRect.x = 0;
			srcTableRect.y = 0;
			SDL_QueryTexture(tableTex, nullptr, nullptr, &srcTableRect.w, &srcTableRect.h);

		}

		// Loading menu texture
		menuBgTex = TextureLoader::loadTexture("assets/img/menu_background.png", renderer);
		if (tableTex) {
			std::cout << "[INFO] Menu Background texture loaded." << std::endl;
		}




		// Bet buttons initialization
		if (bet10Btn.init("assets/img/bet_10.png", 71, 566, 90, 90, renderer)) {
			std::cout << "[INFO] bet10 Button created." << std::endl;
		}
		if (bet25Btn.init("assets/img/bet_25.png", 172, 566, 90, 90, renderer)) {
			std::cout << "[INFO] bet25 Button created." << std::endl;
		}
		if (bet50Btn.init("assets/img/bet_50.png", 27, 652, 90, 90, renderer)) {
			std::cout << "[INFO] bet50 Button created." << std::endl;
		}
		if (bet100Btn.init("assets/img/bet_100.png", 122, 652, 90, 90, renderer)) {
			std::cout << "[INFO] bet100 Button created." << std::endl;
		}
		if (bet500Btn.init("assets/img/bet_500.png", 217, 652, 90, 90, renderer)) {
			std::cout << "[INFO] bet500 Button created." << std::endl;
		}


		// Menu buttons initialization
		if (menuBtn.init("assets/img/menu_button.png", 1280, 0, 86, 70, renderer)) {
			std::cout << "[INFO] Menu Button created." << std::endl;
		}
		if (resumeBtn.init("assets/img/resume_button.png", 543, 158, 482, 51, renderer)) {
			std::cout << "[INFO] Menu Resume Button created." << std::endl;
		}
		if (newGameBtn.init("assets/img/new_game_button.png", 528, 220, 516, 47, renderer)) {
			std::cout << "[INFO] Menu new game Button created." << std::endl;
		}
		if (volumeBtn.init("assets/img/volume_button.png", 529, 277, 516, 141, renderer)) {
			std::cout << "[INFO] Menu volume Button created." << std::endl;
		}
		if (exitBtn.init("assets/img/exit_button.png", 528, 428, 516, 47, renderer)) {
			std::cout << "[INFO] Menu exit Button created." << std::endl;
		}

		// 'Hit' & 'Stand' buttons initializationn
		if (hitBtn.init("assets/img/hit.png", 1220, 380, 90, 90, renderer)) {
			std::cout << "[INFO] Hit Button created." << std::endl;
		}
		if (standBtn.init("assets/img/stand.png", 1220, 250, 90, 90, renderer)) {
			std::cout << "[INFO] Stand Button created." << std::endl;
		}

		// Music button initialization
		if (musicBtn.init("assets/img/bg_music.png", 27, 256, 40, 33, renderer)) {
			std::cout << "[INFO] Music Button created." << std::endl;
		}

		// Skip tutorial button initialization
		if (skipTutorialBtn.init("assets/img/background_green_dragon_light.png", 0, 0, 1366, 768, renderer)) {
			std::cout << "[INFO] Skip tutorial Button created." << std::endl;
		}

		// Card deck skin change buttons initialization
		if (cardColWhiteBtn.init("assets/img/btn_white_card.png", 23, 102, 50, 66, renderer)) {
			std::cout << "[INFO] Card color white Button created." << std::endl;
		}
		if (cardColGreyBtn.init("assets/img/btn_grey_card.png", 87, 102, 50, 66, renderer)) {
			std::cout << "[INFO] Card color grey Button created." << std::endl;
		}
		if (cardColYellowBtn.init("assets/img/btn_yellow_card.png", 151, 102, 50, 66, renderer)) {
			std::cout << "[INFO] Card color yellow Button created." << std::endl;
		}
		if (cardColGreenRedBtn.init("assets/img/btn_green_red_card.png", 23, 180, 50, 66, renderer)) {
			std::cout << "[INFO] Card color green red Button created." << std::endl;
		}
		if (cardColGoldBtn.init("assets/img/btn_gold_card.png", 87, 180, 50, 66, renderer)) {
			std::cout << "[INFO] Card color Gold Button created." << std::endl;
		}

		// Slider initialization
		if (musicVolumeSld.init("assets/img/slider_rod.png", 554, 332, 467, 22,
								"assets/img/slider_ball.png", 554, 332, 23, 22, renderer)) {
			std::cout << "[INFO] Music volume Slider created." << std::endl;
		}
		if (soundVolumeSld.init("assets/img/slider_rod.png", 554, 387, 467, 22,
			"assets/img/slider_ball.png", 554, 387, 23, 22, renderer)) {
			std::cout << "[INFO] Sound volume Slider created." << std::endl;
		}
	


		// Adding buttons to interface array
		buttons.push_back(&bet10Btn);
		buttons.push_back(&bet25Btn);
		buttons.push_back(&bet50Btn);
		buttons.push_back(&bet100Btn);
		buttons.push_back(&bet500Btn);
		buttons.push_back(&hitBtn);
		buttons.push_back(&standBtn);
		buttons.push_back(&musicBtn);
		buttons.push_back(&cardColWhiteBtn);
		buttons.push_back(&cardColGreyBtn);
		buttons.push_back(&cardColYellowBtn);
		buttons.push_back(&cardColGreenRedBtn);
		buttons.push_back(&cardColGoldBtn);

		menuButtons.push_back(&resumeBtn);
		menuButtons.push_back(&newGameBtn);
		menuButtons.push_back(&volumeBtn);
		menuButtons.push_back(&exitBtn);



		// Player's & Dealer's hand drawers initialization 
		if (playerDrawer.init("assets/img/cards_classic.png", renderer, &blackJack.player, 490, 440, 200, 280, 1)) {
			std::cout << "[INFO] PlayerDrawer created." << std::endl;
		}
		if (dealerDrawer.init("assets/img/cards_gold.png", renderer, &blackJack.dealer, 490, 50, 200, 280, -1)) {
			std::cout << "[INFO] DealerDrawer created." << std::endl;
		}



		// Loading game sounds
		audioManager.loadSound("button_click", "assets/audio/button_click.wav");
		audioManager.loadSound("card_flip", "assets/audio/card_flip.wav");
		audioManager.loadSound("dealer_win", "assets/audio/dealer_win.wav");
		audioManager.loadSound("player_win", "assets/audio/player_win.wav");
		audioManager.loadSound("a_draw", "assets/audio/a_draw.wav");
		audioManager.playMusic("assets/audio/background_guitar_no_copyright.mp3");

		// Default game volume
		currentMusicVolume = 0.3;
		currentSoundVolume = 1.0;
		audioManager.setMusicVolume(currentMusicVolume);

		// Setting volume slider's position
		musicVolumeSld.setValue(currentMusicVolume);
		soundVolumeSld.setValue(currentSoundVolume);

		playingMusic = true;
		


		// Text renderers initialization
		if (textRenFS20.init("assets/font/STENCIL.ttf", 20, renderer)) {
			std::cout << "[INFO] TextRenderer(FontSize 20) created." << std::endl;
		}
		if (textRenFS50.init("assets/font/STENCIL.ttf", 50, renderer)) {
			std::cout << "[INFO] TextRenderer(FontSize 50) created." << std::endl;
		}
		if (textRenFS50Message.init("assets/font/STENCIL.ttf", 50, renderer)) {
			std::cout << "[INFO] TextRenderer(FontSize 50) Message created." << std::endl;
		}
		if (textRenFS50Rules.init("assets/font/STENCIL.ttf", 50, renderer)) {
			std::cout << "[INFO] TextRenderer(FontSize 50) Rules created." << std::endl;
			textRenFS50Rules.setTimer(15000);
		}


		// Creating BlackJack logic game
		blackJack.createNewGame();
		blackJack.player.init("Anonyms", 200);
		winTimer.setTimer(10'800'000);

		playerTurn = true;
		displayMenu = false;
		isRunning = true;
	} else {
		isRunning = false;
	}
}

void Game::handleEvents() {
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update() {
	// Update everything if no startup message is displayed anymore
	if (!textRenFS50Rules.active()) {
		// Game buttons update
		if (!displayMenu) {
			for (int i = 0; i < buttons.size(); i++) {
				buttons[i]->update();
			}
		}

		// Enter menu button update
		menuBtn.update();
		if (menuBtn.selected()) {
			if (displayMenu) {
				displayMenu = false;
			} else {
				displayMenu = true;
			}
		}

		// Update menu buttons & sliders, if menu enabled
		if (displayMenu) {
			// Update volume sliders
			musicVolumeSld.update();
			soundVolumeSld.update();

			// Update volume in case sliders value changed
			if (musicVolumeSld.getValue() != currentMusicVolume) {
				currentMusicVolume = musicVolumeSld.getValue();
				audioManager.setMusicVolume(currentMusicVolume);
			}
			if (soundVolumeSld.getValue() != currentSoundVolume) {
				currentSoundVolume = soundVolumeSld.getValue();
				audioManager.setAllSoundsVolume(currentSoundVolume);
			}


			// Update menu buttons
			for (int i = 0; i < menuButtons.size(); i++) {
				menuButtons[i]->update();
			}

			// Resume button update
			if (resumeBtn.selected()) {
				audioManager.playSound("button_click");
				displayMenu = false;
			}
			// Exit button update
			if (exitBtn.selected()) {
				audioManager.playSound("button_click");
				quitGame();
			}
			// Start a new game button update
			if (newGameBtn.selected()) {
				startANewGame();
				audioManager.playSound("button_click");
				displayMenu = false;
			}
		}



		// Play sound when a new card added
		if (playerDrawer.animationStarted()) {
			audioManager.playSound("card_flip");
		}
		if (dealerDrawer.animationStarted()) {
			audioManager.playSound("card_flip");
		}


		// Update game buttons logic
		hitButtonLogic();
		standButtonLogic();
		betButtonsLogic();

		winnerLogic();

		musicButtonLogic();
		cardSkinLogic();


		// Create a new lap if old is done and waiting time >= timerTime
		if (!winTimer.active()) {
			winTimer.setTimer(10'800'000);
			createANewLap();
		}

		// Play sound on button click
		for (int i = 0; i < buttons.size(); i++) {
			if (buttons[i]->selected()) {
				audioManager.playSound("button_click");
			}
		}
		if (menuBtn.selected()) {
			audioManager.playSound("button_click");
		}

	} else {
		// Update skipTutorial button
		skipTutorialBtn.update();

		if (skipTutorialBtn.selected()) {
			textRenFS50Rules.setTimer(0);
		}
	}
}

void Game::render() {
	// Clear previous frame
	SDL_RenderClear(renderer);

	// Draw background
	SDL_RenderCopy(renderer, backgroundTex, &bgImageRect, &winRect);

	// Render player's & dealer's 'hand'
	playerDrawer.drawHand();
	dealerDrawer.drawHand();

	// Render bet & score table
	SDL_RenderCopy(renderer, tableTex, &srcTableRect, &srcTableRect);
	

	// Render buttons
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->draw();
	}


	// Render score text
	textRenFS20.renderText(std::string("Balance:   ") + std::to_string(blackJack.player.getBalance()), 25, 25, white);
	textRenFS20.renderText(std::string("Bet:   ") + std::to_string(blackJack.player.getBet()), 25, 55, white);

	// Render text "First place a bet" if bet is 0
	renderPlaceBetMessage();

	// Render win message
	if (winMessageTimer.active()) {
		renderWinMessage();
	}


	// Render menu button
	menuBtn.draw();

	// Render menu, if menu button is selected
	if (displayMenu) {
		// Render Menu box
		SDL_RenderCopy(renderer, menuBgTex, nullptr, nullptr);

		// Render menu buttons
		for (int i = 0; i < menuButtons.size(); i++) {
			menuButtons[i]->draw();
		}

		// Render volume sliders
		musicVolumeSld.draw();
		soundVolumeSld.draw();
	}

	// Render NotEnoughMoney message in case if bet > balance
	renderNotEnoughMoneyMessage();

	// Render rules at the beginning of the game
	renderRulesMessage();

	// Present render frame
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "[INFO] Game Cleaned." << std::endl;
}

SDL_Window* Game::getWindow() {
	return window;
}

bool Game::running() {
	return isRunning;
}


void Game::standButtonLogic() {
	// Stand button update
	if (standBtn.selected()) {
		// Do action if player hand != 0
		if (blackJack.player.hand.size()) {
			if (blackJack.player.getBet() != 0) {
				// Dealer takes the cards, while total value < 17
				while (blackJack.dealer.getScore() < 17) {
					blackJack.dealer.addCardToHand(blackJack.deck.cards.back());
					blackJack.deck.cards.pop_back();
					dealerFlipCardTimer.setTimer(1000);
				}

				winnerLogic();
			}
			playerTurn = false;
		}
	}
}

void Game::hitButtonLogic() {
	// Hit button update
	if (hitBtn.selected()) {
		// Stop displaying winner text
		textRenFS50.setTimer(0);


		// Give 2 cards to each
		if (blackJack.player.hand.size() == 0 && blackJack.dealer.hand.size() == 0) {
			// Check player bet, to avoid game with zero bet
			if (blackJack.player.getBet() != 0) {
				for (int i = 0; i < 2; i++) {
					blackJack.player.addCardToHand(blackJack.deck.cards.back());
					blackJack.deck.cards.pop_back();

					blackJack.dealer.addCardToHand(blackJack.deck.cards.back());
					blackJack.deck.cards.pop_back();
				}

				blackJack.dealer.hand.at(0).hidden = true;
			} else {
				// Display message "Bet can't be zero!"
				textRenFS50Message.setTimer(1000);
			}
		} else {
			// If both already have at least 2 cards

			// Add card to hand from deck
			if (!blackJack.deck.cards.empty()) {
				blackJack.player.addCardToHand(blackJack.deck.cards.back());
				blackJack.deck.cards.pop_back();
			}

			// Create new game, if dealers card is not hidden
			createANewLap();
		}
	}
}

void Game::betButtonsLogic() {
	// Player bet update if hand is clear
	if (!blackJack.player.hand.size()) {

		// Bet button with value '10' logic
		if (bet10Btn.selected()) {
			// Checking if player can afford bet
			if (blackJack.player.getBalance() >= blackJack.player.getBet() + 10) {
				blackJack.player.setBet(blackJack.player.getBet() + 10);
			} else {
				activateMoneyMessage();
			}
		}

		// Bet button with value '25' logic
		if (bet25Btn.selected()) {
			// Checking if player can afford bet
			if (blackJack.player.getBalance() >= blackJack.player.getBet() + 25) {
				blackJack.player.setBet(blackJack.player.getBet() + 25);
			} else {
				activateMoneyMessage();
			}
		}

		// Bet button with value '50' logic
		if (bet50Btn.selected()) {
			// Checking if player can afford bet
			if (blackJack.player.getBalance() >= blackJack.player.getBet() + 50) {
				blackJack.player.setBet(blackJack.player.getBet() + 50);
			} else {
				activateMoneyMessage();
			}
		}

		// Bet button with value '100' logic
		if (bet100Btn.selected()) {
			// Checking if player can afford bet
			if (blackJack.player.getBalance() >= blackJack.player.getBet() + 100) {
				blackJack.player.setBet(blackJack.player.getBet() + 100);
			} else {
				activateMoneyMessage();
			}
		}

		// Bet button with value '500' logic
		if (bet500Btn.selected()) {
			// Checking if player can afford bet
			if (blackJack.player.getBalance() >= blackJack.player.getBet() + 500) {
				blackJack.player.setBet(blackJack.player.getBet() + 500);
			} else {
				activateMoneyMessage();
			}
		}
	}
}

void Game::winnerLogic() {
	// Winner update logic, if dealer has cards in his 'hand'
	if (blackJack.dealer.hand.size()) {

		// Continue logic, if first dealer card is hidden
		if (blackJack.dealer.hand[0].hidden) {

			// Continue logic, if dealer has enough cards, card animation ended,
			// and player selected 'Stand' button
			if (blackJack.dealer.getScore() >= 17 && !dealerFlipCardTimer.active() && !playerTurn) {
				blackJack.dealer.hand.at(0).hidden = false;

				// A Draw
				if (blackJack.checkWinner() == 0) {
					blackJack.player.setBet(0);
					textRenFS50.setTimer(30000);
					audioManager.playSound("a_draw");
				}

				// Player win
				if (blackJack.checkWinner() == 1) {
					blackJack.player.setBalance(blackJack.player.getBalance() + blackJack.player.getBet());
					blackJack.player.setBet(0);
					textRenFS50.setTimer(30000);
					audioManager.playSound("player_win");
				}

				// Dealer win
				if (blackJack.checkWinner() == -1) {
					blackJack.player.setBalance(blackJack.player.getBalance() - blackJack.player.getBet());
					blackJack.player.setBet(0);
					textRenFS50.setTimer(30000);
					audioManager.playSound("dealer_win");
				}

				// Setting messages timers
				winTimer.setTimer(5000);
				winMessageTimer.setTimer(5000);
				dealerFlipCardTimer.clear();

				// Return control to the player
				playerTurn = true;
			}
		}
	}
}

void Game::cardSkinLogic() {
	// Change card deck texture
	if (cardColWhiteBtn.selected()) {
		playerDrawer.useTexture("assets/img/cards_classic.png");
	}
	if (cardColGreyBtn.selected()) {
		playerDrawer.useTexture("assets/img/cards_black.png");
	}
	if (cardColYellowBtn.selected()) {
		playerDrawer.useTexture("assets/img/cards_yellow.png");
	}
	if (cardColGreenRedBtn.selected()) {
		playerDrawer.useTexture("assets/img/cards_unusual.png");
	}
	if (cardColGoldBtn.selected()) {
		playerDrawer.useTexture("assets/img/cards_gold.png");
	}
}

void Game::musicButtonLogic() {
	// Mute/unmute button update
	if (musicBtn.selected()) {
		if (playingMusic) {
			playingMusic = false;
			audioManager.setMusicVolume(0);
			musicVolumeSld.setValue(0);
			previousMusicVolume = currentMusicVolume;
		} else {
			playingMusic = true;
			audioManager.setMusicVolume(previousMusicVolume);
			musicVolumeSld.setValue(previousMusicVolume);
		}
	}
}

void Game::activateMoneyMessage() {
	// Activating 'Not enough money' message
	int moneyMessageTime = 700;
	notEnoughMoneyTimer.setTimer(moneyMessageTime);
	audioManager.playSound("a_draw");
}

void Game::renderWinMessage() {
	// Message rectangle position
	messageRect = { 690, 335, 240, 61 };

	// Display message if winner message timer is active
	if (textRenFS50.active()) {
		// Rectangle color
		SDL_SetRenderDrawColor(renderer, grey.r, grey.r, grey.b, grey.a);

		// Displaying 'a draw' message
		if (blackJack.checkWinner() == 0) {

			textX = messageRect.x + xTextOffset;
			textY = messageRect.y + yTextOffset;
			SDL_RenderFillRect(renderer, &messageRect);
			textRenFS50.renderText("A Draw!", textX, textY, white);
		}

		// Displaying 'player win' message
		if (blackJack.checkWinner() == 1) {
			messageRect.x -= 49;
			messageRect.w = 270;

			textX = messageRect.x + xTextOffset;
			textY = messageRect.y + yTextOffset;
			SDL_RenderFillRect(renderer, &messageRect);
			textRenFS50.renderText("You win!", textX, textY, lightGold);
		}

		// Displaying 'dealer win' message
		if (blackJack.checkWinner() == -1) {
			messageRect.w = 340;
			SDL_RenderFillRect(renderer, &messageRect);
	
			textX = messageRect.x + xTextOffset;
			textY = messageRect.y + yTextOffset;
			textRenFS50.renderText("Dealer win!", textX, textY, lightBlue);
		}

		// Rendering player's & dealer's hand value (Score)
		textRenFS50.renderText(std::to_string(blackJack.dealer.getScore()), dealerDrawer.getXStart() + 100, dealerDrawer.getYStart() - 45, white);
		textRenFS50.renderText(std::to_string(blackJack.player.getScore()), playerDrawer.getXStart() + 100, playerDrawer.getYStart() - 45, white);
	}
}

void Game::renderPlaceBetMessage() {
	// Message rectangle position
	messageRect = { 500, 335, 500, 61 };

	// Display message if bet message timer is active
	if (textRenFS50Message.active()) {
		SDL_RenderFillRect(renderer, &messageRect);

		textX = messageRect.x + xTextOffset;
		textY = messageRect.y + yTextOffset;
		textRenFS50.renderText("Bet can't be zero!", textX, textY, white);
	}
}

void Game::renderRulesMessage() {
	// Message rectangle position
	messageRect = { 510, 150, 550, 420 };

	// Display message if rules message timer is active
	if (textRenFS50Rules.active()) {
		SDL_RenderFillRect(renderer, &messageRect);

		// Variables used to make space between lines
		int rowOffset = 50;
		int nextLineOffset = 7;

		// Header
		textX = 690;
		textY = 168;
		textRenFS50Rules.setFont("assets/font/STENCIL.ttf", 30);
		textRenFS50Rules.renderText("Rules :", textX, textY, white, 40);

		// First line
		textX = 540;
		textY = 240;
		textRenFS50Rules.setFont("assets/font/BRITANIC.ttf", 30);
		textRenFS50Rules.renderText("1. Place a bet. Bet can't be zero.", textX, textY, white);

		// Second line
		textY = 240 + rowOffset * 1 - nextLineOffset * 0;
		textRenFS50Rules.renderText("2. Press 'Hit' to start game or to", textX, textY, white);

		// Second's first line subline
		textY = 240 + rowOffset * 2 - nextLineOffset * 2;
		textRenFS50Rules.renderText("    take one more card.", textX, textY, white);

		// Third line
		textY = 240 + rowOffset * 3 - nextLineOffset * 0;
		textRenFS50Rules.renderText("3. Press 'Stand' to end your turn.", textX, textY, white);

		// Fourth line
		textY = 240 + rowOffset * 4 - nextLineOffset * 0;
		textRenFS50Rules.renderText("4. The goal of blackjack is to beat", textX, textY, white);

		// Fourth's first line subline
		textY = 240 + rowOffset * 5 - nextLineOffset * 2;
		textRenFS50Rules.renderText("     the dealer's hand without going", textX, textY, white);

		// Fourth's second line subline
		textY = 240 + rowOffset * 6 - nextLineOffset * 4;
		textRenFS50Rules.renderText("     over 21.", textX, textY, white);
	}
}

void Game::renderNotEnoughMoneyMessage() {
	// Render 'Not enough money' message, if timer is active
	if (notEnoughMoneyTimer.active()) {
		messageRect = { 534, 335, 420, 61 };

		SDL_RenderFillRect(renderer, &messageRect);

		textX = 548;
		textY = 350;
		textRenFS50Rules.setFont("assets/font/STENCIL.ttf", 30);
		textRenFS50Rules.renderText("Not enough money!", textX, textY, white, 40);
	}
}

void Game::createANewLap() {
	// Create a new game lap, if dealer has cards
	if (blackJack.dealer.hand.size()) {

		// Continue logic, if dealer first card in not hidden
		if (!blackJack.dealer.hand[0].hidden) {
			blackJack.createNewGame();
			playerDrawer.clearHand();
			dealerDrawer.clearHand();
		}
	}
}



void Game::startANewGame() {
	// Create a new game, as on game startup
	winMessageTimer.clear();
	blackJack.createNewGame();
	playerDrawer.clearHand();
	dealerDrawer.clearHand();

	blackJack.player.setBalance(200);
	blackJack.player.setBet(0);
}

void Game::quitGame() {
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}
