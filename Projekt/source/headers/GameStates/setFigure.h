#pragma once
#include "Game.h"
class SetFigure :
    public GameState
{
    Game* prev;                         /*!< Wska�nik na obiekt poprzedniego stanu gry. */
        
    sf::Text textChoose;                /*!< Tekst wy�wietlaj�cy napis wyboru. */

    std::unique_ptr<Button> b_five;     /*!< Przycisk wyboru pi�tki. */
    std::unique_ptr<Button> b_six;      /*!< Przycisk wyboru sz�stki. */
    std::unique_ptr<Button> b_seven;    /*!< Przycisk wyboru si�demki. */
    std::unique_ptr<Button> b_eight;    /*!< Przycisk wyboru �semki. */
    std::unique_ptr<Button> b_nine;     /*!< Przycisk wyboru dziewi�tki. */
    std::unique_ptr<Button> b_ten;      /*!< Przycisk wyboru dziesi�tki. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _game wska�nik na poprzedni stan gry.
       * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    SetFigure(Game* _game, std::shared_ptr<Resources> _resources);
    /**
       * \see GameState::update(sf::Event event, sf::RenderWindow& window)
       */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    /**
       * \see GameState::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window);
};

