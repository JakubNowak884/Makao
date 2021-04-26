#pragma once

#include "game.h"
#include "singlePlayerSettings.h"

class singlePlayer :
    public game
{
    std::vector<std::unique_ptr<AI>> bots;

    bool end = false;
    long sleepDuration = 1;

    std::thread t;

    bool threadRunning = false;

public:
    singlePlayer(singlePlayerSettings* prev);
    AI* getAI(int ID);
    bool everyoneElseWon();
    void botsTakesTurn();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

