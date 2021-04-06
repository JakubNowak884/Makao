#pragma once

#include <vector>
#include <list>
#include <string>

#include "card.h"

class AI
{
	object* cardBack = nullptr;
	sf::Text info;
	std::vector<card*> hand;

	int ID;
	int won;
	int delay;

public:
	AI(std::list<card*>& deck, sf::Font& font, int _ID, bool onlyOne = false);
	~AI();

	int getID();
	int getWon();
	int& getDelay();
	bool handEmpty();

	void setWon(int _won);

	bool hasACardAbleToPlay(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	card* playACard(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	card* drawACard(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
	void draw(sf::RenderWindow& window);
};

