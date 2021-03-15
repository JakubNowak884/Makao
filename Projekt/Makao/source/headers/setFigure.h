#pragma once
#include "gameState.h"
class setFigure :
    public gameState
{
    sf::Font font;
    gameState* game;

    button* b_five;
    button* b_six;
    button* b_seven;
    button* b_eight;
    button* b_nine;
    button* b_ten;

public:
    setFigure(gameState* _game);
    ~setFigure();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

