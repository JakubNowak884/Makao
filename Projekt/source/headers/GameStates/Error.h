#pragma once

#include "GameState.h"

class Error :
    public GameState
{
    sf::Text error; /*!< Tekst wy�wietlaj�cy przekazany b��d. */
    std::unique_ptr<Button> b_menu; /*!< Przycisk powrotu do menu gry. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _error b��d zwr�cony przez poprzedni stan gry.
       * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    Error(std::wstring _error, std::shared_ptr<Resources> _resources);
    /**
       * \see GameState::update(sf::Event event, sf::RenderWindow& window)
       */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
    /**
       * \see GameState::update(sf::Event event, sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

