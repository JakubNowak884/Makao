#pragma once

#include "menu.h"
#include "changeName.h"
#include "singlePlayerSettings.h"
#include "singlePlayer.h"
#include "multiPlayerSettings.h"
#include "changeIP.h"
#include "multiPlayer.h"
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

