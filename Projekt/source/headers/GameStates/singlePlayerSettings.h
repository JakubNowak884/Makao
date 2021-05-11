#pragma once
#include "GameState.h"

class SinglePlayerSettings :
    public GameState
{
    sf::Text settings;                                  /*!< Tekst wy�wietlaj�cy ustawienia. */

    std::unique_ptr<Button> b_addAmountOfPlayers;       /*!< Przycisk zwi�kszenia liczby graczy. */
    std::unique_ptr<Button> b_reduceAmountOfPlayers;    /*!< Przycisk zmniejszenia liczby graczy. */
    std::unique_ptr<Button> b_addBotSpeed;              /*!< Przycisk zwi�kszenia odst�pu mi�dzy turami graczy komputerowych. */
    std::unique_ptr<Button> b_reduceBotSpeed;           /*!< Przycisk zmniejszenia odst�pu mi�dzy turami graczy komputerowych. */
    std::unique_ptr<Button> b_onlyQueens;               /*!< Przycisk zmieniaj�cy ustawienie samych Kr�lowych w talii. */
    std::unique_ptr<Button> b_start;                    /*!< Przycisk rozpoczynaj�cy gr�. */
    std::unique_ptr<Button> b_toMenu;                   /*!< Przycisk przej�cia do menu gry. */

    int amountOfPlayers = 2;                            /*!< Liczba graczy. */
    int botSpeed = 500;                                 /*!< Odst�p mi�dzy turami graczy komputerowych w milisekundach. */
    bool onlyQueens = false;                            /*!< Zmienna informuj�ca czy opcja samych Kr�lowych w talii jest w��czona. */

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

