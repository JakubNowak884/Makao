#pragma once
#include "GameState.h"

class Menu :
    public GameState
{
    sf::Text currentPlayer;                     /*!< Tekst wy�wietlaj�cy aktualn� nazw� gracza. */

    std::unique_ptr<Button> b_changeName;       /*!< Przycisk zmiany nazwy gracza. */
    std::unique_ptr<Button> b_singlePlayer;     /*!< Przycisk przej�cia do ustawie� gry w jednego gracza. */
    std::unique_ptr<Button> b_multiPlayer;      /*!< Przycisk przej�cia do ustawie� gry w wielu graczy. */
    std::unique_ptr<Button> b_instruction;      /*!< Przycisk przej�cia do instrukcji. */
    std::unique_ptr<Button> b_quit;             /*!< Przycisk wyj�cia z gry. */
    std::unique_ptr<Button> b_language;         /*!< Przycisk zmiany j�zyka gry. */

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

