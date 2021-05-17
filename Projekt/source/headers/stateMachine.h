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
    GameState* current;                     /*!< WskaŸnik na aktualny stan gry. */
    GameState* prev;                        /*!< WskaŸnik na poprzedni stan gry. */
    std::shared_ptr<Resources> resources;   /*!< WskaŸnik na obiekt klasy przechowuj¹cej zasoby gry. */

public:
    /**
      * \brief Konstruktor jednoargumentowy.
      * \param _resources wskaŸnik na obiekt klasy przechowuj¹cej zasoby gry
      */
    StateMachine(std::shared_ptr<Resources> _resources);
    ~StateMachine();
    /**
     * \brief Funkcja wywo³ywana po zg³oszeniu przez któryœ z stanów gry wyj¹tku.
     * 
     * W funkcji aktualny stan gry jest usuwany, a nastêpnie zastêpywane stanem gry "Error"
     * \param error treœæ wyj¹tku wypisywana na ekranie.
     */
    void exception(std::wstring error);
    /**
     * \brief Funkcja aktualizuj¹ca aktualny stan gry.
     * 
     * Funkcja jest wywo³ywana w g³ównej pêtli gry.
     * Rozpatrywany jest typ wyliczeniowy zwrócony przez metodê update() wywo³ywan¹ na rzecz akualnego stanu gry,
     * a nastêpnie na jego podstawie tworzony jest nowy stan gry, lub pozostawiany aktualny.
     * \param event wydarzenie zainicjowane przez u¿ytkownika.
     * \param window okno gry
     * \return false jeœli aktualny stan gry zwróci³ gameStateNumber::quit, w przeciwnym wypadku true.
     */
    bool update(sf::Event event, sf::RenderWindow& window);
    /**
    * \brief Funkcja rysuj¹ca aktualny stan gry na ekranie.
    * \param window okno gry.
    */
    void draw(sf::RenderWindow& window);
};

