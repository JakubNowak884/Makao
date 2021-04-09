#pragma once
#include "gameState.h"
class instruction :
    public gameState
{
    sf::Font font;

    sf::Text rules;
    sf::Text controls;
    sf::Text credits;
    sf::Text page1;
    sf::Text page2;

    std::unique_ptr<button> b_pageDown;
    std::unique_ptr<button> b_pageUp;
    std::unique_ptr<button> b_menu;

    int page = 1;

public:
    instruction();
    void pageDown();
    void pageUp();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

