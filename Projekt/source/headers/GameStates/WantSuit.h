#pragma once
#include "Game.h"
class WantSuit :
    public GameState
{
    Game* prev;                             /*!< Wskaźnik na obiekt poprzedniego stanu gry. */

    sf::Text textChoose;                    /*!< Tekst wyświetlający napis wyboru. */

    std::unique_ptr<Button> b_clubs;        /*!< Przycisk wyboru trefl. */
    std::unique_ptr<Button> b_diamonds;     /*!< Przycisk wyboru karo. */
    std::unique_ptr<Button> b_hearts;       /*!< Przycisk wyboru serc. */
    std::unique_ptr<Button> b_spades;       /*!< Przycisk wyboru pik. */

public:
    /**
      * \brief Konstruktor dwuargumentowy.
      * \param _game wskaźnik na poprzedni stan gry.
      * \param _resources wskaźnik na obiekt klasy przechowujący zasoby gry.
      * \see GameState::GameState(std::shared_ptr<Resources> _resources)
      */
    WantSuit(Game* _game, std::shared_ptr<Resources> _resources);
    /**
      * \see GameState::update(sf::Event event, sf::RenderWindow& window)
      */
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    /**
      * \see GameState::draw(sf::RenderWindow& window)
      */
    void draw(sf::RenderWindow& window);
};

