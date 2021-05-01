#pragma once
#include "gameState.h"

class singlePlayerSettings :
    public gameState
{
    sf::Font font;

    sf::Text settings;
    std::unique_ptr<button> b_addAmountOfPlayers;
    std::unique_ptr<button> b_reduceAmountOfPlayers;
    std::unique_ptr<button> b_addBotSpeed;
    std::unique_ptr<button> b_reduceBotSpeed;
    std::unique_ptr<button> b_onlyQueens;
    std::unique_ptr<button> b_start;
    std::unique_ptr<button> b_toMenu;

    int amountOfPlayers = 2;
    int botSpeed = 500;
    bool onlyQueens = false;

public:
    singlePlayerSettings(Resources* _resources);
    int getAmountOfPlayers();
    bool getOnlyQueens();
    int getBotSpeed();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

