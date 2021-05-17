#pragma once

#include <string>
#include <map>

#include "SinglePlayer.h"
#include "MultiPlayer.h"

class Endgame :
    public GameState
{
    sf::Text textResults;                   /*!< Tekst wy�wietlaj�cy wyniki gry. */

    std::unique_ptr<Button> b_menu;         /*!< Przycisk powrotu do menu gry. */

    std::map<int, std::string> results;     /*!< Mapa przechowuj�ca nazwy graczy oraz odpowiednio zaj�te przez nich miejsca. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _prev wska�nik na poprzedni stan gry.
       * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    Endgame(SinglePlayer* prev, std::shared_ptr<Resources> _resources);
    /**
      * \brief Konstruktor dwuargumentowy.
      * \param _prev wska�nik na poprzedni stan gry.
      * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
      * \see GameState::GameState(std::shared_ptr<Resources> _resources)
      */
    Endgame(MultiPlayer* prev, std::shared_ptr<Resources> _resources);
    /**
     * \see GameState::update(sf::Event event, sf::RenderWindow& window)
     */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
    /**
       * \see GameState::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

