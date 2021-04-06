#pragma once

#include "game.h"

class singlePlayer :
    public game
{
    std::vector<std::unique_ptr<AI>> bots;

    bool end = false;
    long sleepDuration = 1;

    std::thread t;

    bool test = true;

public:
    singlePlayer(gameState* prev);
    AI* getAI(int ID);
    bool everyoneElseWon();
    void botsTakesTurn();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

