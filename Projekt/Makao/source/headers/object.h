#pragma once

#include <SFML/Graphics.hpp>

class object
{
	sf::RectangleShape shape;
	float x;
	float y;
	float width;
	float height;
	bool chosen;

public:
	object()
		: x(0), y(0), width(0), height(0), chosen(false) {}
	object(float _width, float _height, float _x, float _y, sf::Color color = sf::Color::Black)
		: x(_x), y(_y), width(_width), height(_height), chosen(false)
	{
		shape.setSize(sf::Vector2f(_width, _height));
		shape.setOrigin(sf::Vector2f(_width/2, _height/2));
		shape.setPosition(sf::Vector2f(_x, _y));
		shape.setFillColor(color);
	}

	float getX();
	float getY();
	float getWidth();
	float getHeight();
	bool isChosen();

	void setChosen(bool newChosen);
	void setPositon(sf::Vector2f position);
	void setShapeColor(sf::Color color);

	virtual void uptade(sf::Vector2f mousePos);
	virtual void draw(sf::RenderWindow& window);
};

