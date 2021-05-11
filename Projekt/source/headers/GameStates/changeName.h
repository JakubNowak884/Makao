#pragma once
#include "GameState.h"
class ChangeName :
	public GameState
{
	sf::Text currentName; /*!< Tekst wyœwietlaj¹cy aktualn¹ nazwê gracza. */

	std::unique_ptr<Button> b_back; /*!< Przycisk powrotu do poprzedniego stanu gry. */

public:
	/**
	  * \see GameState::GameState(std::shared_ptr<Resources> _resources)
	  */
	ChangeName(std::shared_ptr<Resources> _resources);
	/**
	  * \see GameState::update(sf::Event event, sf::RenderWindow& window)
	  */
	gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
	/**
	  * \see GameState::draw(sf::RenderWindow& window)
	  */
	void draw(sf::RenderWindow& window) override;
};

