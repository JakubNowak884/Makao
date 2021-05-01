#include "headers\AI.h"

AI::AI(std::list<std::shared_ptr<card>>& deck, sf::Font& font, sf::Texture* texture, int _ID, bool onlyOne)
{
	info.setFont(font);
	info.setCharacterSize(24);

	if (onlyOne)
	{
		info.setPosition(470, 10);
		cardBack = new object(120, 180, 400, 100, texture, sf::Color::White);
	}
	else {
		switch (_ID)
		{
		case 2:		
			info.setPosition(10, 210);
			cardBack = new object(120, 180, 70, 400, texture, sf::Color::White);
			break;
		case 3:
			info.setPosition(470, 10);
			cardBack = new object(120, 180, 400, 100, texture, sf::Color::White);
			break;
		case 4:
			info.setPosition(580, 210);
			cardBack = new object(120, 180, 640, 400, texture, sf::Color::White);
			break;
		default:
			break;
		}
	}

	cardBack->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));

	int j = 0;
	for (std::list<std::shared_ptr<card>>::iterator i = deck.begin(); i != deck.end(); ++i)
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

void AI::setDelay(int _delay)
{
	delay = _delay;
}

void AI::setTextColor(sf::Color color)
{
	info.setFillColor(color);
}

suitNumber AI::wantSuit()
{
	if (hand.size() > 0)
		return hand.front()->getSuit();
	else
		return suitNumber::clubs;
}

figureNumber AI::wantFigure()
{
	if (hand.size() > 0)
	{
		for (auto i = hand.begin(); i != hand.end(); ++i)
		{
			switch ((*i)->getFigure())
			{
			case figureNumber::five:
				return figureNumber::five;
				break;
			case figureNumber::six:
				return figureNumber::six;
				break;
			case figureNumber::seven:
				return figureNumber::seven;
				break;
			case figureNumber::eight:
				return figureNumber::eight;
				break;
			case figureNumber::nine:
				return figureNumber::nine;
				break;
			case figureNumber::ten:
				return figureNumber::ten;
				break;
			}
		}
	}
	return figureNumber::five;
}

bool AI::hasACardAbleToPlay(std::list<std::shared_ptr<card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure)
{
	for (std::vector<std::shared_ptr<card>>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure, second))
			return true;
	}
	second = false;
	return false;
}

card* AI::playACard(std::list<std::shared_ptr<card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure)
{
	for (std::vector<std::shared_ptr<card>>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure, second))
		{
			deck.push_front((*i));
			hand.erase(i);
			second = true;
			return deck.front().get();
		}
	}
	return nullptr;
}

card* AI::drawACard(std::list<std::shared_ptr<card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany)
{
	if (deck.back()->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure, second))
	{
		deck.push_front(deck.back());
		deck.pop_back();
		return deck.front().get();
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
