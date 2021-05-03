#pragma once

#include <vector>
#include <list>
#include <string>

#include "GUI\Card.h"

class Resources;
class AI
{
	struct howManyCards
	{
		howManyCards(suitNumber _suit)
			: suit(_suit), figure(figureNumber::null), howMany(0) {}
		howManyCards(figureNumber _figure)
			: figure(_figure), suit(suitNumber::null), howMany(0) {}

		suitNumber suit;
		figureNumber figure;
		int howMany;
		bool operator <(const howManyCards& obj)
		{
			if (howMany < obj.howMany)
				return true;
			else
				return false;
		}
	};

	struct cardPlayed
	{
		cardPlayed(suitNumber _suit, figureNumber _figure)
			: suit(_suit), figure(_figure) {}
		suitNumber suit;
		figureNumber figure;
	};
	Resources* resources;

	Object* cardBack = nullptr;
	sf::Text info;
	std::vector<std::shared_ptr<Card>> hand;
	std::list<std::unique_ptr<cardPlayed>> cardsPlayed;

	int ID;
	int won;
	int delay;
	bool second = false;

public:
	AI(std::list<std::shared_ptr<Card>>& deck, Resources* _resources, int _ID, bool onlyOne = false);
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
	void rememberCard(suitNumber suit, figureNumber figure);
	bool hasACardAbleToPlay(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	Card* playACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	Card* drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
	void draw(sf::RenderWindow& window);
};

