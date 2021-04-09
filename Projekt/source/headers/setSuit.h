#pragma once
#include "gameState.h"
class setSuit :
    public gameState
{
    sf::Font font;
    gameState* game;

    sf::Text text;

    std::unique_ptr<button> b_clubs;
    std::unique_ptr<button> b_diamonds;
    std::unique_ptr<button> b_hearts;
    std::unique_ptr<button> b_spades;

public:
    setSuit(gameState* _game);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

