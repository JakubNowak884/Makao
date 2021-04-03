#pragma once
#include "gameState.h"

class singlePlayerSettings :
    public gameState
{
    sf::Font font;

    sf::Text settings;
    std::unique_ptr<button> b_2;
    std::unique_ptr<button> b_3;
    std::unique_ptr<button> b_4;
    std::unique_ptr<button> b_toMenu;

public:
    singlePlayerSettings();
    ~singlePlayerSettings();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

