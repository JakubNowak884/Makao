#pragma once

#include <vector>
#include <list>
#include <string>

#include "GUI\card.h"

class AI
{
	object* cardBack = nullptr;
	sf::Text info;
	std::vector<std::shared_ptr<card>> hand;

	int ID;
	int won;
	int delay;
	bool second = false;

public:
	AI(std::list<std::shared_ptr<card>>& deck, sf::Font& font, sf::Texture* texture, int _ID, bool onlyOne = false);
	~AI();

	int getID();
	int getWon();
	int& getDelay();
	bool handEmpty();

	void setWon(int _won);
	void setDelay(int _delay);
	void setTextColor(sf::Color color);

	suitNumber wantSuit();
	figureNumber wantFigure();
	bool hasACardAbleToPlay(std::list<std::shared_ptr<card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	card* playACard(std::list<std::shared_ptr<card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	card* drawACard(std::list<std::shared_ptr<card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
	void draw(sf::RenderWindow& window);
};

