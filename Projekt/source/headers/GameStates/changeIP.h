#pragma once
#include "MultiPlayerSettings.h"
class ChangeIP :
	public GameState
{
	sf::Text currentIP;

	std::unique_ptr<Button> b_back;

	MultiPlayerSettings* prev = nullptr;

public:
	ChangeIP(MultiPlayerSettings* _prev, Resources* _resources);
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

