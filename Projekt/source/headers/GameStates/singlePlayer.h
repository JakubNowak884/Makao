#pragma once

#include "Game.h"
#include "SinglePlayerSettings.h"

class SinglePlayer :
    public Game
{
    std::vector<std::unique_ptr<AI>> bots;

    bool end = false;
    long sleepDuration = 1;

    std::thread t;

public:
    SinglePlayer(SinglePlayerSettings* prev, Resources* _resources);
    AI* getAI(int ID);
    void botsTakesTurn();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

