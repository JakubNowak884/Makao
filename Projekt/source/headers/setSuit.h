#pragma once
#include "game.h"
class setSuit :
    public gameState
{
    sf::Font font;
    game* prev;

    sf::Text text;

    std::unique_ptr<button> b_clubs;
    std::unique_ptr<button> b_diamonds;
    std::unique_ptr<button> b_hearts;
    std::unique_ptr<button> b_spades;

public:
    setSuit(game* _game);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

