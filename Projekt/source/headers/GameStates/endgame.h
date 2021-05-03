#pragma once

#include <string>
#include <map>

#include "SinglePlayer.h"
#include "MultiPlayer.h"

class Endgame :
    public GameState
{
    sf::Text text;
    std::unique_ptr<Button> b_menu;

    std::map<int, std::string> results;

public:
    Endgame(SinglePlayer* prev, Resources* _resources);
    Endgame(MultiPlayer* prev, Resources* _resources);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

