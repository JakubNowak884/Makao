#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <thread>

class Object
{
	sf::RectangleShape shape;
	float x;
	float y;
	float width;
	float height;
	bool chosen;

public:
	Object()
		: x(0), y(0), width(0), height(0), chosen(false) {}
	Object(float _width, float _height, float _x, float _y, sf::Texture* texture, sf::Color color = sf::Color::Black)
		: x(_x), y(_y), width(_width), height(_height), chosen(false)
	{
		shape.setSize(sf::Vector2f(_width, _height));
		shape.setOrigin(sf::Vector2f(_width/2, _height/2));
		shape.setPosition(sf::Vector2f(_x, _y));
		shape.setTexture(texture);
	}

	float getX();
	float getY();
	float getWidth();
	float getHeight();
	bool isChosen();

	sf::RectangleShape& getShape();

	void setChosen(bool newChosen);
	virtual void setPosition(sf::Vector2f position);
	void setShapeColor(sf::Color color);

	virtual void uptade(sf::Vector2f mousePos);
	virtual void draw(sf::RenderWindow& window);
};

