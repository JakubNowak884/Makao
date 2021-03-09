#pragma once

#include "game.h"

class singlePlayer :
    public game
{
    AI* bot;

public:
    singlePlayer()
    {
        bot = new AI(deck, font, 2);
    }
    ~singlePlayer();
    AI* getAI(int number);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

