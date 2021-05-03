#include "..\headers\GUI\card.h"

Card::~Card()
{
}

suitNumber Card::getSuit()
{
	return suit;
}

figureNumber Card::getFigure()
{
	return figure;
}

void Card::uptade(sf::Vector2f mousePos)
{
	Object::uptade(mousePos);
	if (isChosen() == true)
		setPosition(sf::Vector2f(getX(), 700));
	else 
		setPosition(sf::Vector2f(getX(), 800));
}

void Card::setPosition(sf::Vector2f position)
{
	Object::setPosition(position);
	frame.setPosition(position);
}

void Card::frameSetFillColor(sf::Color color)
{
	frame.setFillColor(color);
}

bool Card::ableToPlay(Card* current, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, bool second)
{
	bool suitMatches;
	if (current->getSuit() == getSuit()) 
		suitMatches = true; 
	else 
		suitMatches = false;

	bool figureMatches;
	if (current->getFigure() == getFigure()) 
		figureMatches = true;
	else 
		figureMatches = false;

	if (actionCardIsActive)
	{
		switch (current->getFigure())
		{
		case figureNumber::ace:
			if (figureMatches || (getSuit() == currentSuit && !second))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		case figureNumber::two:
			if (figureMatches || (getFigure() == figureNumber::three && suitMatches))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		case figureNumber::three:
			if (figureMatches || (getFigure() == figureNumber::two && suitMatches))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		case figureNumber::four:
			if (figureMatches)
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		case figureNumber::jack:
			if (figureMatches || (getFigure() == currentFigure && !second))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		case figureNumber::king:
			if (figureMatches && (getSuit() == suitNumber::hearts || getSuit() == suitNumber::spades))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		default:
			return false;
			break;
		}
	}
	else if ((current->getFigure() == figureNumber::queen || getFigure() == figureNumber::queen) && !second) 
	{
		frame.setFillColor(sf::Color::Green);
		return true;
	}
	else if (!second)
	{
		if (suitMatches || figureMatches)
		{
			frame.setFillColor(sf::Color::Green);
			return true;
		}
		else
		{
			frame.setFillColor(sf::Color::Red);
			return false;
		}
	}
	else
	{
		if (figureMatches)
		{
			frame.setFillColor(sf::Color::Green);
			return true;
		}
		else
		{
			frame.setFillColor(sf::Color::Red);
			return false;
		}
	}
}

void Card::draw(sf::RenderWindow& window)
{
	if (isChosen() == true)
		window.draw(frame);

	Object::draw(window);
}
