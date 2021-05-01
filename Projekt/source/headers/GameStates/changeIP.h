#pragma once
#include "multiPlayerSettings.h"
class changeIP :
	public gameState
{
	sf::Font font;

	sf::Text currentIP;

	std::unique_ptr<button> b_back;

	multiPlayerSettings* prev = nullptr;

public:
	changeIP(multiPlayerSettings* _prev, Resources* _resources);
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

