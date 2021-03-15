#pragma once

#include "menu.h"
#include "singlePlayerSettings.h"
#include "singlePlayer.h"
#include "endgame.h"
#include "setSuit.h"
#include "setFigure.h"

class stateMachine
{
    gameState* current;
    gameState* prev;

public:
    stateMachine();
    ~stateMachine();

    bool update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

