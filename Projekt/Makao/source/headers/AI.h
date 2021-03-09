#pragma once

#include <vector>
#include <list>
#include <string>

#include "cards\card_ace.h"
#include "cards\card_two.h"
#include "cards\card_three.h"
#include "cards\card_four.h"
#include "cards\card_five.h"
#include "cards\card_six.h"
#include "cards\card_seven.h"
#include "cards\card_eight.h"
#include "cards\card_nine.h"
#include "cards/card_ten.h"
#include "cards\card_jack.h"
#include "cards\card_queen.h"
#include "cards\card_king.h"

class AI
{
	object* cardBack;
	sf::Text amountOfCards;
	std::vector<card*> hand;

	int ID;
	int won;

public:
	AI(std::list<card*>& deck, sf::Font& font, int _ID);
	~AI();

	int getID();
	int getWon();
	bool handEmpty();

	void setWon(int _won);

	bool hasACardAbleToPlay(std::list<card*>& deck, bool addDraw);
	card* playACard(std::list<card*>& deck, bool addDraw);
	card* drawACard(std::list<card*>& deck, bool addDraw, int howMany = 1);
	void draw(sf::RenderWindow& window);
};

