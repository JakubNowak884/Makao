#pragma once

#include <string>
#include <map>

#include "SinglePlayer.h"
#include "MultiPlayer.h"

class Endgame :
    public GameState
{
    sf::Text textResults;                   /*!< Tekst wyúwietlajπcy wyniki gry. */

    std::unique_ptr<Button> b_menu;         /*!< Przycisk powrotu do menu gry. */

    std::map<int, std::string> results;     /*!< Mapa przechowujπca nazwy graczy oraz odpowiednio zajÍte przez nich miejsca. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _prev wskaünik na poprzedni stan gry.
       * \param _resources wskaünik na obiekt klasy przechowujπcy zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    Endgame(SinglePlayer* prev, std::shared_ptr<Resources> _resources);
    /**
      * \brief Konstruktor dwuargumentowy.
      * \param _prev wskaünik na poprzedni stan gry.
      * \param _resources wskaünik na obiekt klasy przechowujπcy zasoby gry.
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

