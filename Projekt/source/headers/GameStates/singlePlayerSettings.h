#pragma once
#include "GameState.h"

class SinglePlayerSettings :
    public GameState
{
    sf::Text settings;

    std::unique_ptr<Button> b_addAmountOfPlayers;
    std::unique_ptr<Button> b_reduceAmountOfPlayers;
    std::unique_ptr<Button> b_addBotSpeed;
    std::unique_ptr<Button> b_reduceBotSpeed;
    std::unique_ptr<Button> b_onlyQueens;
    std::unique_ptr<Button> b_start;
    std::unique_ptr<Button> b_toMenu;

    int amountOfPlayers = 2;
    int botSpeed = 500;
    bool onlyQueens = false;

public:
    SinglePlayerSettings(Resources* _resources);
    int getAmountOfPlayers();
    bool getOnlyQueens();
    int getBotSpeed();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

