#pragma once

#include "GameStates/menu.h"
#include "GameStates/changeName.h"
#include "GameStates/instruction.h"
#include "GameStates/singlePlayerSettings.h"
#include "GameStates/singlePlayer.h"
#include "GameStates/multiPlayerSettings.h"
#include "GameStates/changeIP.h"
#include "GameStates/multiPlayer.h"
#include "GameStates/endgame.h"
#include "GameStates/setSuit.h"
#include "GameStates/setFigure.h"

class stateMachine
{
    gameState* current;
    gameState* prev;
    Resources* resources;

public:
    stateMachine(Resources* _resources);
    ~stateMachine();

    bool update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

