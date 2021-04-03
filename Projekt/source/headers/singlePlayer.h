#pragma once

#include "game.h"

class singlePlayer :
    public game
{
    AI* bot;

public:
    singlePlayer();
    ~singlePlayer();
    AI* getAI(int number);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

