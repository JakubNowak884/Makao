#pragma once
#include "Game.h"
class SetFigure :
    public GameState
{
    Game* prev;                         /*!< WskaŸnik na obiekt poprzedniego stanu gry. */
        
    sf::Text textChoose;                /*!< Tekst wyœwietlaj¹cy napis wyboru. */

    std::unique_ptr<Button> b_five;     /*!< Przycisk wyboru pi¹tki. */
    std::unique_ptr<Button> b_six;      /*!< Przycisk wyboru szóstki. */
    std::unique_ptr<Button> b_seven;    /*!< Przycisk wyboru siódemki. */
    std::unique_ptr<Button> b_eight;    /*!< Przycisk wyboru ósemki. */
    std::unique_ptr<Button> b_nine;     /*!< Przycisk wyboru dziewi¹tki. */
    std::unique_ptr<Button> b_ten;      /*!< Przycisk wyboru dziesi¹tki. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _game wskaŸnik na poprzedni stan gry.
       * \param _resources wskaŸnik na obiekt klasy przechowuj¹cy zasoby gry.
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

