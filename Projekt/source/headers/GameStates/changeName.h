#pragma once
#include "GameState.h"
class ChangeName :
	public GameState
{
	sf::Text currentName;

	std::unique_ptr<Button> b_back;

public:
	ChangeName(Resources* _resources);
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

