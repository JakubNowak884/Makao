#include "headers\AI.h"

AI::AI(std::list<card*>& deck, sf::Font& font, int _ID, bool onlyOne)
{
	info.setFont(font);
	info.setCharacterSize(24);

	if (onlyOne)
	{
		info.setPosition(470, 10);
		cardBack = new object(120, 180, 400, 100, sf::Color::White);
	}
	else {
		switch (_ID)
		{
		case 2:		
			info.setPosition(10, 210);
			cardBack = new object(120, 180, 70, 400, sf::Color::White);
			break;
		case 3:
			info.setPosition(470, 10);
			cardBack = new object(120, 180, 400, 100, sf::Color::White);
			break;
		case 4:
			info.setPosition(580, 210);
			cardBack = new object(120, 180, 640, 400, sf::Color::White);
			break;
		default:
			break;
		}
	}

	int j = 0;
	for (std::list<card*>::iterator i = deck.begin(); i != deck.end(); i++)
	{
		if (j == 5) break;
		hand.push_back((*i));
		j++;
	}

	for (int i = 0; i < 5; i++)
		deck.pop_front();

	ID = _ID;
	won = 0;
	delay = 0;
}

AI::~AI()
{
	delete cardBack;
}

int AI::getID()
{
	return ID;
}

int AI::getWon()
{
	return won;
}

int& AI::getDelay()
{
	return delay;
}

bool AI::handEmpty()
{
	return hand.empty();
}

void AI::setWon(int _won)
{
	won = _won;
}

bool AI::hasACardAbleToPlay(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure)
{
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front(), actionCardIsActive, currentSuit, currentFigure))
			return true;
	}
	return false;
}

card* AI::playACard(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure)
{
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front(), actionCardIsActive, currentSuit, currentFigure))
		{
			deck.push_front((*i));
			i = hand.erase(i);
			return deck.front();
		}
	}
}

card* AI::drawACard(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany)
{
	if (deck.back()->ableToPlay(deck.front(), actionCardIsActive, currentSuit, currentFigure))
	{
		deck.push_front(deck.back());
		deck.pop_back();
		return deck.front();
	}
	else
	{
		for (int i = 0; i < howMany; i++)
		{
			if (deck.front() == deck.back()) break;
			hand.push_back(deck.back());
			deck.pop_back();
		}
		return nullptr;
	}
}

void AI::draw(sf::RenderWindow& window)
{
	size_t amount = hand.size();
	std::string amountText = std::to_string(amount);

	info.setString("Komputer " + std::to_string(ID - 1) + "\nIlosc kart: " + std::to_string(hand.size()) + "\nOpoznienie: " + std::to_string(delay));
	window.draw(info);

	cardBack->draw(window);
}
