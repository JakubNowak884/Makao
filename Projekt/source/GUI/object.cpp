#include "..\headers\GUI\Object.h"

Object::Object()
	: x(0), y(0), width(0), height(0), chosen(false) {}

Object::Object(float _width, float _height, float _x, float _y, sf::Texture* texture, sf::Color color)
	: x(_x), y(_y), width(_width), height(_height), chosen(false)
{
	shape.setSize(sf::Vector2f(_width, _height));
	shape.setOrigin(sf::Vector2f(_width / 2, _height / 2));
	shape.setPosition(sf::Vector2f(_x, _y));
	shape.setTexture(texture);
}

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
	//sprawdzenie czy kursor myszy znajduje siê w granicach szerokoœci i wysokoœci obiektu.
	if (mousePos.x > getX() - getWidth() / 2 && mousePos.x < getX() + getWidth() / 2 && mousePos.y > getY() - getHeight() / 2 && mousePos.y < getY() + getHeight() / 2)
		chosen = true;
	else
		chosen = false;
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
