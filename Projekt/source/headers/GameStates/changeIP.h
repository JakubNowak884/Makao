#pragma once
#include "MultiPlayerSettings.h"
class ChangeIP :
	public GameState
{
	sf::Text currentIP;                     /*!< Tekst wyœwietlaj¹cy aktualne IP. */

	std::unique_ptr<Button> b_back;         /*!< Przycisk powrotu do poprzedniego stanu gry. */

	MultiPlayerSettings* prev = nullptr;    /*!< WskaŸnik na obiekt poprzedniego stanu gry. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _prev wskaŸnik na poprzedni stan gry.
       * \param _resources wskaŸnik na obiekt klasy przechowuj¹cej zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
	ChangeIP(MultiPlayerSettings* _prev, std::shared_ptr<Resources> _resources);
    /**
       * \see GameState::update(sf::Event event, sf::RenderWindow& window)
       */
	gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
    /**
        * \see GameState::draw(sf::RenderWindow& window)
        */
	void draw(sf::RenderWindow& window) override;
};

