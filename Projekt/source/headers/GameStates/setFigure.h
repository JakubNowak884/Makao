#pragma once
#include "Game.h"
class SetFigure :
    public GameState
{
    Game* prev;
    
    sf::Text text;

    std::unique_ptr<Button> b_five;
    std::unique_ptr<Button> b_six;
    std::unique_ptr<Button> b_seven;
    std::unique_ptr<Button> b_eight;
    std::unique_ptr<Button> b_nine;
    std::unique_ptr<Button> b_ten;

public:
    SetFigure(Game* _game, Resources* _resources);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

