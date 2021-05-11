#pragma once

#include "Game.h"
#include "SinglePlayerSettings.h"

class SinglePlayer :
    public Game
{
    std::vector<std::unique_ptr<AI>> bots;  /*!< Wektor wska�nik�w na obiekty reprezentuj�ce graczy kompoterowych. */

    bool end = false;                       /*!< Zmienna informuj�ca o ko�cu rozgrywki. */
    long sleepDuration = 1;                 /*!< Zmienna informuj�ca o odst�pie mi�dzy turami graczy komputerowych. */

    std::thread t;                          /*!< W�tek, na kt�rym wywo�ywana jest funkcja, podczas kt�rej gracze komputerowi wykonuj� tur�. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _prev wska�nik na poprzedni stan gry.
       * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    SinglePlayer(SinglePlayerSettings* prev, std::shared_ptr<Resources> _resources);
    /**
       * \brief Funkcja zwraca gracza komputerowego w zale�no�ci od jego ID.
       * \param ID gracza komputerowego, kt�re ma zwr�ci� funkcja.
       * \return wska�nik na obiekt reprezentuj�cy gracza komputerowego.
       */
    AI* getAI(int ID);
    /**
       * \brief Funkcja symuluj�ca tur� graczy ludzkich.
       * 
       * Funkcja pracuje na osobnym w�tku ni� g�owna p�tla gry, wi�c podczas tury graczy komputerowych gracz mo�e przegl�da� karty w swojej r�ce.
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

