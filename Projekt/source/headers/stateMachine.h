#pragma once

#include "GameStates/Menu.h"
#include "GameStates/ChangeName.h"
#include "GameStates/Instruction.h"
#include "GameStates/SinglePlayerSettings.h"
#include "GameStates/SinglePlayer.h"
#include "GameStates/MultiPlayerSettings.h"
#include "GameStates/ChangeIP.h"
#include "GameStates/MultiPlayer.h"
#include "GameStates/Endgame.h"
#include "GameStates/WantSuit.h"
#include "GameStates/WantFigure.h"
#include "GameStates/Error.h"

class StateMachine
{
    GameState* current;                     /*!< Wska�nik na aktualny stan gry. */
    GameState* prev;                        /*!< Wska�nik na poprzedni stan gry. */
    std::shared_ptr<Resources> resources;   /*!< Wska�nik na obiekt klasy przechowuj�cej zasoby gry. */

public:
    /**
      * \brief Konstruktor jednoargumentowy.
      * \param _resources wska�nik na obiekt klasy przechowuj�cej zasoby gry
      */
    StateMachine(std::shared_ptr<Resources> _resources);
    ~StateMachine();
    /**
     * \brief Funkcja wywo�ywana po zg�oszeniu przez kt�ry� z stan�w gry wyj�tku.
     * 
     * W funkcji aktualny stan gry jest usuwany, a nast�pnie zast�pywane stanem gry "Error"
     * \param error tre�� wyj�tku wypisywana na ekranie.
     */
    void exception(std::wstring error);
    /**
     * \brief Funkcja aktualizuj�ca aktualny stan gry.
     * 
     * Funkcja jest wywo�ywana w g��wnej p�tli gry.
     * Rozpatrywany jest typ wyliczeniowy zwr�cony przez metod� update() wywo�ywan� na rzecz akualnego stanu gry,
     * a nast�pnie na jego podstawie tworzony jest nowy stan gry, lub pozostawiany aktualny.
     * \param event wydarzenie zainicjowane przez u�ytkownika.
     * \param window okno gry
     * \return false je�li aktualny stan gry zwr�ci� gameStateNumber::quit, w przeciwnym wypadku true.
     */
    bool update(sf::Event event, sf::RenderWindow& window);
    /**
    * \brief Funkcja rysuj�ca aktualny stan gry na ekranie.
    * \param window okno gry.
    */
    void draw(sf::RenderWindow& window);
};

