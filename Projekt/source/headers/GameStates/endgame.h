#pragma once

#include <string>
#include <map>

#include "SinglePlayer.h"
#include "MultiPlayer.h"

class Endgame :
    public GameState
{
    sf::Text textResults;                   /*!< Tekst wyświetlający wyniki gry. */

    std::unique_ptr<Button> b_menu;         /*!< Przycisk powrotu do menu gry. */

    std::map<int, std::string> results;     /*!< Mapa przechowująca nazwy graczy oraz odpowiednio zajęte przez nich miejsca. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _prev wskaźnik na poprzedni stan gry.
       * \param _resources wskaźnik na obiekt klasy przechowujący zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    Endgame(SinglePlayer* prev, std::shared_ptr<Resources> _resources);
    /**
      * \brief Konstruktor dwuargumentowy.
      * \param _prev wskaźnik na poprzedni stan gry.
      * \param _resources wskaźnik na obiekt klasy przechowujący zasoby gry.
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

