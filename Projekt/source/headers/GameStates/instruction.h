#pragma once
#include "GameState.h"
class Instruction :
    public GameState
{
    sf::Text rules;                         /*!< Tekst wy�wietlaj�cy zasady. */
    sf::Text controls;                      /*!< Tekst wy�wietlaj�cy sterowanie. */
    sf::Text credits;                       /*!< Tekst wy�wietlaj�cy autora i podzi�kowania. */
    sf::Text page1;                         /*!< Tekst wy�wietlaj�cy aktualn� stron�. */
    sf::Text page2;                         /*!< Tekst wy�wietlaj�cy aktualn� stron�. */

    std::unique_ptr<Button> b_pageDown;     /*!< Przycisk cofaj�cy stron�. */
    std::unique_ptr<Button> b_pageUp;       /*!< Przycisk przewracaj�cy stron�. */
    std::unique_ptr<Button> b_menu;         /*!< Przycisk powrotu do menu gry. */

    int page = 1; /*!< Numer aktualnej strony. */

public:
    /**
      * \see GameState::GameState(std::shared_ptr<Resources> _resources).
      */
    Instruction(std::shared_ptr<Resources> _resources);
    /**
    * \brief Funkcja cofaj�ca stron�.
    */
    void pageDown();
    /**
    * \brief Funkcja przewracaj�ca stron�.
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

