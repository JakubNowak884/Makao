#include "headers\object.h"

float object::getX()
{
	return x;
}

float object::getY()
{
	return y;
}

float object::getWidth()
{
	return width;
}

float object::getHeight()
{
	return height;
}

bool object::isChosen()
{
	return chosen;
}

void object::setChosen(bool newChosen)
{
	chosen = newChosen;
}

void object::setPosition(sf::Vector2f position)
{
	x = position.x;
	y = position.y;
	shape.setPosition(position);
}

void object::setShapeColor(sf::Color color)
{
	shape.setFillColor(color);
}

void object::uptade(sf::Vector2f mousePos)
{
	if (mousePos.x > getX() - getWidth() / 2 && mousePos.x < getX() + getWidth() / 2 && mousePos.y > getY() - getHeight() / 2 && mousePos.y < getY() + getHeight() / 2)
		chosen = true;
	else
		chosen = false;
}

void object::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
