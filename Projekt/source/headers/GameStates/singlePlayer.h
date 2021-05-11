#pragma once

#include "Game.h"
#include "SinglePlayerSettings.h"

class SinglePlayer :
    public Game
{
    std::vector<std::unique_ptr<AI>> bots;  /*!< Wektor wskaŸników na obiekty reprezentuj¹ce graczy kompoterowych. */

    bool end = false;                       /*!< Zmienna informuj¹ca o koñcu rozgrywki. */
    long sleepDuration = 1;                 /*!< Zmienna informuj¹ca o odstêpie miêdzy turami graczy komputerowych. */

    std::thread t;                          /*!< W¹tek, na którym wywo³ywana jest funkcja, podczas której gracze komputerowi wykonuj¹ turê. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _prev wskaŸnik na poprzedni stan gry.
       * \param _resources wskaŸnik na obiekt klasy przechowuj¹cy zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    SinglePlayer(SinglePlayerSettings* prev, std::shared_ptr<Resources> _resources);
    /**
       * \brief Funkcja zwraca gracza komputerowego w zale¿noœci od jego ID.
       * \param ID gracza komputerowego, które ma zwróciæ funkcja.
       * \return wskaŸnik na obiekt reprezentuj¹cy gracza komputerowego.
       */
    AI* getAI(int ID);
    /**
       * \brief Funkcja symuluj¹ca turê graczy ludzkich.
       * 
       * Funkcja pracuje na osobnym w¹tku ni¿ g³owna pêtla gry, wiêc podczas tury graczy komputerowych gracz mo¿e przegl¹daæ karty w swojej rêce.
       */
    void botsTakesTurn();
    /**
       * \see GameState::update(sf::Event event, sf::RenderWindow& window)
       */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    /**
        * \see GameState::draw(sf::RenderWindow& window)
        */
    void draw(sf::RenderWindow& window);
};

