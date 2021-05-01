#pragma once
#include "gameState.h"
class changeName :
	public gameState
{
	sf::Font font;

	sf::Text currentName;

	std::unique_ptr<button> b_back;

public:
	changeName(Resources* _resources);
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

