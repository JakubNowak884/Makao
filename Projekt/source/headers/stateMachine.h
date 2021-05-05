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
#include "GameStates/Error.h"

class StateMachine
{
    GameState* current;
    GameState* prev;
    std::shared_ptr<Resources> resources;

public:
    StateMachine(std::shared_ptr<Resources> _resources);
    ~StateMachine();
    void exception(std::wstring error);
    bool update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

