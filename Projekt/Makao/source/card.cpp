#include "headers\card.h"

card::~card()
{
}

suitNumber card::getSuit()
{
	return suit;
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
	sprite[0].setPosition(getX() - getWidth() / 2,  getY() - getHeight() / 2 + textSize);
	sprite[1].setPosition(getX() + getWidth() / 2,  getY() + getHeight() / 2 - textSize);
	frame.setPosition(position);
}

void card::frameSetFillColor(sf::Color color)
{
	frame.setFillColor(color);
}

bool card::ableToPlay(card* current, bool addDraw, bool second)
{
	if (!second)
	{
		if (getSuit() == current->getSuit() || typeid(*this).name() == typeid(*current).name())
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
		if (typeid(*this).name() == typeid(*current).name())
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
		window.draw(sprite[i]);
	}
}
