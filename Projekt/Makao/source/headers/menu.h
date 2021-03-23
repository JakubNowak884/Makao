#pragma once
#include "gameState.h"

class menu :
    public gameState
{
    sf::Font font;

    std::unique_ptr<button> b_singlePlayer;
    std::unique_ptr<button> b_multiPlayer;
    std::unique_ptr<button> b_quit;

public:
    menu();
    ~menu();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

