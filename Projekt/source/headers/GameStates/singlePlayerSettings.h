#pragma once
#include "GameState.h"

class SinglePlayerSettings :
    public GameState
{
    sf::Text settings;                                  /*!< Tekst wyœwietlaj¹cy ustawienia. */

    std::unique_ptr<Button> b_addAmountOfPlayers;       /*!< Przycisk zwiêkszenia liczby graczy. */
    std::unique_ptr<Button> b_reduceAmountOfPlayers;    /*!< Przycisk zmniejszenia liczby graczy. */
    std::unique_ptr<Button> b_addBotSpeed;              /*!< Przycisk zwiêkszenia odstêpu miêdzy turami graczy komputerowych. */
    std::unique_ptr<Button> b_reduceBotSpeed;           /*!< Przycisk zmniejszenia odstêpu miêdzy turami graczy komputerowych. */
    std::unique_ptr<Button> b_onlyQueens;               /*!< Przycisk zmieniaj¹cy ustawienie samych Królowych w talii. */
    std::unique_ptr<Button> b_start;                    /*!< Przycisk rozpoczynaj¹cy grê. */
    std::unique_ptr<Button> b_toMenu;                   /*!< Przycisk przejœcia do menu gry. */

    int amountOfPlayers = 2;                            /*!< Liczba graczy. */
    int botSpeed = 500;                                 /*!< Odstêp miêdzy turami graczy komputerowych w milisekundach. */
    bool onlyQueens = false;                            /*!< Zmienna informuj¹ca czy opcja samych Królowych w talii jest w³¹czona. */

public:
    /**
      * \see GameState::GameState(std::shared_ptr<Resources> _resources)
      */
    SinglePlayerSettings(std::shared_ptr<Resources> _resources);
    int getAmountOfPlayers();
    bool getOnlyQueens();
    int getBotSpeed();
    /**
      * \see GameState::update(sf::Event event, sf::RenderWindow& window)
      */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    /**
      * \see GameState::draw(sf::RenderWindow& window)
      */
    void draw(sf::RenderWindow& window);
};

