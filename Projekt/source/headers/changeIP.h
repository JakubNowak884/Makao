#pragma once
#include "gameState.h"
class changeIP :
	public gameState
{
	sf::Font font;

	sf::Text currentIP;

	std::unique_ptr<button> b_back;

	gameState* prev = nullptr;

public:
	changeIP(gameState* _prev);
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

