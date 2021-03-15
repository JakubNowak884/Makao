#pragma once
#include "gameState.h"
class setSuit :
    public gameState
{
    sf::Font font;
    gameState* game;

    button* b_clubs;
    button* b_diamonds;
    button* b_hearts;
    button* b_spades;

public:
    setSuit(gameState* _game);
    ~setSuit();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

