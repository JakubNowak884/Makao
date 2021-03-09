#pragma once

#include <string>
#include <map>

#include "gameState.h"

class endgame :
    public gameState
{
    sf::Font font;

    sf::Text text;
    button* b_menu;

    std::map<int, std::string> results;

public:
    endgame(gameState* prev);
    ~endgame();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

