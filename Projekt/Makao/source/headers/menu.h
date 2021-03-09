#pragma once
#include "gameState.h"

class menu :
    public gameState
{
    sf::Font font;

    button* b_singlePlayer;
    button* b_multiPlayer;
    button* b_quit;

public:
    menu();
    ~menu();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

