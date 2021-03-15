#include "headers\card.h"

card::~card()
{
}

suitNumber card::getSuit()
{
	return suit;
}

figureNumber card::getFigure()
{
	return figure;
}

void card::uptade(sf::Vector2f mousePos)
{
	object::uptade(mousePos);
	if (isChosen() == true)
		setPosition(sf::Vector2f(getX(), 700));
	else 
		setPosition(sf::Vector2f(getX(), 800));
}

void card::setPosition(sf::Vector2f position)
{
	object::setPositon(position);
	name[0].setPosition(getX() - getWidth() / 2 + 3, getY() - getHeight() / 2);
	name[1].setPosition(getX() + getWidth() / 2 - 3, getY() + getHeight() / 2);
	spriteSuit[0].setPosition(getX() - getWidth() / 2,  getY() - getHeight() / 2 + textSize);
	spriteSuit[1].setPosition(getX() + getWidth() / 2,  getY() + getHeight() / 2 - textSize);
	frame.setPosition(position);
}

void card::frameSetFillColor(sf::Color color)
{
	frame.setFillColor(color);
}

bool card::ableToPlay(card* current, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, bool second)
{
	bool suitMatches;
	if (current->getSuit() == suit) suitMatches = true; else suitMatches = false;

	bool figureMatches;
	if (current->getFigure() == figure) figureMatches = true; else figureMatches = false;

	if (actionCardIsActive)
	{
		switch (current->getFigure())
		{
		case figureNumber::ace:
			if (figureMatches || (suit == currentSuit && !second))
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
			if (figureMatches || (current->getFigure() == figureNumber::three && suitMatches))
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
			if (figureMatches || (current->getFigure() == figureNumber::two && suitMatches))
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
			if (figureMatches || (figure == currentFigure && !second))
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
			if (figureMatches && (current->getSuit() == suitNumber::hearts || current->getSuit() == suitNumber::spades))
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
	else if ((current->getFigure() == figureNumber::queen || figure == figureNumber::queen) && !second) 
	{
		frame.setFillColor(sf::Color::Green);
		return true;
	}
	else if (!second)
	{
		if (getSuit() == current->getSuit() || getFigure() == current->getFigure())
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
		if (getFigure() == current->getFigure())
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

void card::draw(sf::RenderWindow& window)
{
	if (isChosen() == true)
		window.draw(frame);

	object::draw(window);
	for (int i = 0; i < 2; i++)
	{
		window.draw(name[i]);
		window.draw(spriteSuit[i]);
	}
}
