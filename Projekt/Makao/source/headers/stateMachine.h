#pragma once

#include "menu.h"
#include "singlePlayerSettings.h"
#include "singlePlayer.h"
#include "endgame.h"

class stateMachine
{
    gameState* current;
    gameState* prev;

public:
    stateMachine();
    ~stateMachine();

    bool uptade(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

