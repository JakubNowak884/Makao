#pragma once

#include "GameStates/Menu.h"
#include "GameStates/ChangeName.h"
#include "GameStates/Instruction.h"
#include "GameStates/SinglePlayerSettings.h"
#include "GameStates/SinglePlayer.h"
#include "GameStates/MultiPlayerSettings.h"
#include "GameStates/ChangeIP.h"
#include "GameStates/MultiPlayer.h"
#include "GameStates/Endgame.h"
#include "GameStates/SetSuit.h"
#include "GameStates/SetFigure.h"

class StateMachine
{
    GameState* current;
    GameState* prev;
    Resources* resources;

public:
    StateMachine(Resources* _resources);
    ~StateMachine();

    bool update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

