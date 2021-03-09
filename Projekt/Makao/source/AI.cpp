#include "headers\AI.h"

AI::AI(std::list<card*>& deck, sf::Font& font, int _ID)
{
	amountOfCards.setFont(font);
	amountOfCards.setCharacterSize(48);
	amountOfCards.setPosition(480, 80);

	cardBack = new object(120, 180, 400, 100, sf::Color::White);

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

bool AI::handEmpty()
{
	return hand.empty();
}

void AI::setWon(int _won)
{
	won = _won;
}

bool AI::hasACardAbleToPlay(std::list<card*>& deck, bool addDraw)
{
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front(), addDraw))
			return true;
	}
	return false;
}

card* AI::playACard(std::list<card*>& deck, bool addDraw)
{
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front(), addDraw))
		{
			deck.push_front((*i));
			i = hand.erase(i);
			return deck.front();
		}
	}
}

card* AI::drawACard(std::list<card*>& deck, bool addDraw, int howMany)
{
	if (howMany == 0) return nullptr;
	if (deck.back()->ableToPlay(deck.front(), addDraw))
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

	amountOfCards.setString("x" + amountText);

	window.draw(amountOfCards);
	cardBack->draw(window);
}
