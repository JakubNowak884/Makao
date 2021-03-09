#pragma once
#include "gameState.h"

class singlePlayerSettings :
    public gameState
{
    sf::Font font;

    sf::Text settings;
    button* b_2;
    button* b_3;
    button* b_4;
    button* b_toMenu;

public:
    singlePlayerSettings();
    ~singlePlayerSettings();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

