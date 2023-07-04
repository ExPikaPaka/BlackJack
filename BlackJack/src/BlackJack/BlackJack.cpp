#include "BlackJack.h"

std::string Card::getName() {
	switch (name) {
		case CardName::ACE:
			return std::string("ACE");
			break;

		case CardName::JACK:
			return std::string("JACK");
			break;

		case CardName::QUEEN:
			return std::string("QUEEN");
			break;

		case CardName::KING:
			return std::string("KING");
			break;

		default:
			return std::to_string((int)name);
			break;
	}
}

std::string Card::getSuit() {
	switch (suit) {
		case Suit::CLUBS:
			return std::string("CLUBS");
			break;

		case Suit::DIAMONDS:
			return std::string("DIAMONDS");
			break;

		case Suit::HEARTS:
			return std::string("HEARTS");
			break;

		case Suit::SPADES:
			return std::string("SPADES");
			break;

		default:
			return std::string("NONE");
			break;
	}
}

void Deck::init() {
	// Initializes cards with standard order
	for (int group = (int)Suit::DIAMONDS; group <= (int)Suit::CLUBS; group++) {
		for (int card = (int)CardName::ACE; card <= (int)CardName::KING; card++) {
			Card c;
			c.suit = (Suit)group;
			c.name = (CardName)card;

			if (c.name == CardName::JACK || c.name == CardName::QUEEN || c.name == CardName::KING) {
				c.value = 10;
			} else {
				c.value = (int)c.name;
			}

			int index = group * 13 + card - 1;
			cards.insert(cards.begin() + index, c);
		}
	}
}

void Deck::shuffle() {
	// Shuffle the deck
	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(cards.begin(), cards.end(), gen);
}

void Player::updateScore() {
	score = 0;
	int aceCnt = 0;

	// Sum values. Ace is counted as 11.
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].value == 1) {
			score += 11;
			aceCnt++;
		} else {
			score += hand[i].value;
		}
	}

	// Change Ace value to 1 to make best hand
	while (score > 21 && aceCnt > 0) {
		score -= 10;
		aceCnt--;
	}
}

void Player::addCardToHand(Card& card) {
	hand.push_back(card);
	updateScore();
}

void Player::clearHand() {
	hand.clear();
}

void Player::init(std::string name, int startingBalance) {
	score = 0;
	bet = 0;
	balance = startingBalance;
	this->name = name;
}

void Player::setName(std::string name) {
	this->name = name;
}

void Player::setScore(int val) {
	score = val;
}

void Player::setBalance(int val) {
	balance = val;
}

void Player::setBet(int val) {
	bet = val;
}

std::string Player::getName() {
	return name;
}

int Player::getScore() {
	return score;
}

int Player::getBalance() {
	return balance;
}

int Player::getBet() {
	return bet;
}

int BlackJack::checkWinner() {
	int dealerScore = dealer.getScore();
	int playerScore = player.getScore();

	if (dealerScore > 21 && playerScore > 21) {
		return 0; // Draw

	} else if (dealerScore > 21) {
		return 1; // Player won

	} else if (playerScore > 21) {
		return -1; // Dealer won

	} else if (dealerScore > playerScore) {
		return -1; // Dealer won

	} else if (playerScore > dealerScore) {
		return 1; // Player won

	} else {
		return 0; // Draw
	}
}

bool PlayerDrawer::init(std::string texturePath, SDL_Renderer* ren, Player* pl, int xStart, int yStart, int cardWidth, int cardHeight, int animationDirection) {
	renderer = ren;
	bool error = false;
	if (!renderer) {
		std::cerr << "[ERROR] PlayerDrawer: SDL_Renderer* = nullptr" << std::endl;
		error = true;
	}

	deckTex = TextureLoader::loadTexture(texturePath.c_str(), renderer);
	if (!deckTex) {
		std::cerr << "[ERROR] PlayerDrawer: Unable to load texture" << std::endl;
		error = true;
	}

	player = pl;
	if (!deckTex) {
		std::cerr << "[ERROR] PlayerDrawer: Player* = nullptr" << std::endl;
		error = true;
	}

	isAnimating = false;
	block = false;

	lastCardCount = 0;
	this->xStart = xStart;
	this->yStart = yStart;

	this->cardWidth = cardWidth;
	this->cardHeight = cardHeight;

	this->animationDirection = animationDirection;

	// Setting card hidden position, dependent on animation direction 
	animatedCardY = animationDirection == -1 ? yStart - cardWidth * 2 : animationDirection == 1 ? yStart + cardWidth * 2 : yStart;

	return !error;
}

void PlayerDrawer::drawHand() {
	// Used to avoid some pixels in texture 
	int xOffset = 3; 
	int yOffset = 2;

	// Constant parameters
	int cardsInTex = 13;
	float widthMultiplier = 0.4;
	srcCard.w = 356;
	srcCard.h = 499;

	dstScreen.y = yStart;
	dstScreen.w = cardWidth;
	dstScreen.h = cardHeight;

	// Display card
	for (int i = 0; i < lastCardCount; i++) {
		// Change suit
		srcCard.x = (int)player->hand.at(i).suit * srcCard.w + (int)player->hand.at(i).suit * xOffset;

		// Change value
		srcCard.y = cardsInTex * srcCard.h + (cardsInTex - (int)player->hand.at(i).value) * yOffset - (int)player->hand.at(i).value * srcCard.h;

		// Change card on screen displacement by X
		dstScreen.x = xStart + cardWidth * widthMultiplier * i;
		

		// Render
		SDL_RenderCopy(renderer, deckTex, &srcCard, &dstScreen);
	}



	// Animate last card appearance if animation enabled
	if (animationDirection != 0 && lastCardCount < player->hand.size()) {
		if (block) {
			isAnimating = false;
		}
		if (!block) {
			isAnimating = true;
			block = true;
		}

		// Change suit
		srcCard.x = (int)player->hand.at(lastCardCount).suit * srcCard.w + (int)player->hand.at(lastCardCount).suit * xOffset;

		// Change value
		srcCard.y = cardsInTex * srcCard.h + (cardsInTex - (int)player->hand.at(lastCardCount).value) * yOffset - (int)player->hand.at(lastCardCount).value * srcCard.h;
		
		// Change card on screen displacement by X
		dstScreen.x = xStart + cardWidth * widthMultiplier * lastCardCount;

		
		if (animationDirection == -1) {
			// Change card on screen displacement by Y;
			if (animatedCardY < yStart) {
				animatedCardY += pow(log(1.0 + yStart - animatedCardY), 3) * 0.35;

				// Tolerance correction
				if ((float)yStart - animatedCardY < 1) animatedCardY = yStart;

				// Applying value
				dstScreen.y = animatedCardY;
			}
		}

		if (animationDirection == 1) {
			// Change card on screen displacement by Y;
			if (animatedCardY > yStart) {
				animatedCardY -= pow(log(1.0 + animatedCardY - yStart), 3) * 0.35;

				// Tolerance correction
				if (animatedCardY - (float)yStart < 1) animatedCardY = yStart;

				// Applying value
				dstScreen.y = animatedCardY;
			}
		}
		
		// Rendering
		SDL_RenderCopy(renderer, deckTex, &srcCard, &dstScreen);

		// Prepare for the next card if current is already animated
		if (animationDirection == -1) {
			if (animatedCardY >= yStart) {
				animatedCardY = yStart - cardWidth * 2;
				lastCardCount++;
				block = false;
			}
		} 
		if (animationDirection == 1) {
			if (animatedCardY <= yStart) {
				animatedCardY = yStart + cardWidth * 2;
				lastCardCount++;
				block = false;
			}
		}
	}

}

bool PlayerDrawer::animationStarted() {
	return isAnimating;
}
