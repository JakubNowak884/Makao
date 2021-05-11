#pragma once
#include "MultiPlayerSettings.h"
class ChangeIP :
	public GameState
{
	sf::Text currentIP;                     /*!< Tekst wy�wietlaj�cy aktualne IP. */

	std::unique_ptr<Button> b_back;         /*!< Przycisk powrotu do poprzedniego stanu gry. */

	MultiPlayerSettings* prev = nullptr;    /*!< Wska�nik na obiekt poprzedniego stanu gry. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _prev wska�nik na poprzedni stan gry.
       * \param _resources wska�nik na obiekt klasy przechowuj�cej zasoby gry.
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

