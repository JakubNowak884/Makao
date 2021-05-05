#pragma once

#include "GameState.h"

class Error :
    public GameState
{
    sf::Text text;
    std::unique_ptr<Button> b_menu;

public:
    Error(std::wstring error, Resources* _resources);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

