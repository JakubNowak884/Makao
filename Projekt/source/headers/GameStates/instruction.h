#pragma once
#include "GameState.h"
class Instruction :
    public GameState
{
    sf::Text rules;                         /*!< Tekst wyświetlający zasady. */
    sf::Text controls;                      /*!< Tekst wyświetlający sterowanie. */
    sf::Text credits;                       /*!< Tekst wyświetlający autora i podziękowania. */
    sf::Text page1;                         /*!< Tekst wyświetlający aktualną stronę. */
    sf::Text page2;                         /*!< Tekst wyświetlający aktualną stronę. */

    std::unique_ptr<Button> b_pageDown;     /*!< Przycisk cofający stronę. */
    std::unique_ptr<Button> b_pageUp;       /*!< Przycisk przewracający stronę. */
    std::unique_ptr<Button> b_menu;         /*!< Przycisk powrotu do menu gry. */

    int page = 1; /*!< Numer aktualnej strony. */

public:
    /**
      * \see GameState::GameState(std::shared_ptr<Resources> _resources).
      */
    Instruction(std::shared_ptr<Resources> _resources);
    /**
    * \brief Funkcja cofająca stronę.
    */
    void pageDown();
    /**
    * \brief Funkcja przewracająca stronę.
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

