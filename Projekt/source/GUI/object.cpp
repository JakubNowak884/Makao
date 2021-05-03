#include "..\headers\GUI\Object.h"

float Object::getX()
{
	return x;
}

float Object::getY()
{
	return y;
}

float Object::getWidth()
{
	return width;
}

float Object::getHeight()
{
	return height;
}

bool Object::isChosen()
{
	return chosen;
}

sf::RectangleShape& Object::getShape()
{
	return shape;
}

void Object::setChosen(bool newChosen)
{
	chosen = newChosen;
}

void Object::setPosition(sf::Vector2f position)
{
	x = position.x;
	y = position.y;
	shape.setPosition(position);
}

void Object::setShapeColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Object::uptade(sf::Vector2f mousePos)
{
	if (mousePos.x > getX() - getWidth() / 2 && mousePos.x < getX() + getWidth() / 2 && mousePos.y > getY() - getHeight() / 2 && mousePos.y < getY() + getHeight() / 2)
		chosen = true;
	else
		chosen = false;
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
