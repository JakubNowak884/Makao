#pragma once
#include "GameState.h"
class Instruction :
    public GameState
{
    sf::Text rules;
    sf::Text controls;
    sf::Text credits;
    sf::Text page1;
    sf::Text page2;

    std::unique_ptr<Button> b_pageDown;
    std::unique_ptr<Button> b_pageUp;
    std::unique_ptr<Button> b_menu;

    int page = 1;

public:
    Instruction(Resources* _resources);
    void pageDown();
    void pageUp();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

