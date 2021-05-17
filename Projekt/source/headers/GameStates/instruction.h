#pragma once
#include "GameState.h"
class Instruction :
    public GameState
{
    sf::Text rules;                         /*!< Tekst wyœwietlaj¹cy zasady. */
    sf::Text controls;                      /*!< Tekst wyœwietlaj¹cy sterowanie. */
    sf::Text credits;                       /*!< Tekst wyœwietlaj¹cy autora i podziêkowania. */
    sf::Text page1;                         /*!< Tekst wyœwietlaj¹cy aktualn¹ stronê. */
    sf::Text page2;                         /*!< Tekst wyœwietlaj¹cy aktualn¹ stronê. */

    std::unique_ptr<Button> b_pageDown;     /*!< Przycisk cofaj¹cy stronê. */
    std::unique_ptr<Button> b_pageUp;       /*!< Przycisk przewracaj¹cy stronê. */
    std::unique_ptr<Button> b_menu;         /*!< Przycisk powrotu do menu gry. */

    int page = 1; /*!< Numer aktualnej strony. */

public:
    /**
      * \see GameState::GameState(std::shared_ptr<Resources> _resources).
      */
    Instruction(std::shared_ptr<Resources> _resources);
    /**
    * \brief Funkcja cofaj¹ca stronê.
    */
    void pageDown();
    /**
    * \brief Funkcja przewracaj¹ca stronê.
    */
    void pageUp();
    /**
      * \see GameState::update(sf::Event event, sf::RenderWindow& window)
      */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
    /**
       * \see GameState::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

