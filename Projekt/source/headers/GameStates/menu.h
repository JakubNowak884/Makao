#pragma once
#include "GameState.h"

class Menu :
    public GameState
{
    sf::Text currentPlayer;                     /*!< Tekst wyœwietlaj¹cy aktualn¹ nazwê gracza. */

    std::unique_ptr<Button> b_changeName;       /*!< Przycisk zmiany nazwy gracza. */
    std::unique_ptr<Button> b_singlePlayer;     /*!< Przycisk przejœcia do ustawieñ gry w jednego gracza. */
    std::unique_ptr<Button> b_multiPlayer;      /*!< Przycisk przejœcia do ustawieñ gry w wielu graczy. */
    std::unique_ptr<Button> b_instruction;      /*!< Przycisk przejœcia do instrukcji. */
    std::unique_ptr<Button> b_quit;             /*!< Przycisk wyjœcia z gry. */
    std::unique_ptr<Button> b_language;         /*!< Przycisk zmiany jêzyka gry. */

public:
    /**
     * \see GameState::GameState(std::shared_ptr<Resources> _resources).
     */
    Menu(std::shared_ptr<Resources> _resources);
    /**
      * \see GameState::update(sf::Event event, sf::RenderWindow& window)
      */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
    /**
       * \see GameState::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

