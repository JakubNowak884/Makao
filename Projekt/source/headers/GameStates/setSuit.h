#pragma once
#include "Game.h"
class SetSuit :
    public GameState
{
    Game* prev;

    sf::Text text;

    std::unique_ptr<Button> b_clubs;
    std::unique_ptr<Button> b_diamonds;
    std::unique_ptr<Button> b_hearts;
    std::unique_ptr<Button> b_spades;

public:
    SetSuit(Game* _game, Resources* _resources);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

