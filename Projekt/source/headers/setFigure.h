#pragma once
#include "gameState.h"
class setFigure :
    public gameState
{
    sf::Font font;
    gameState* game;
    
    std::unique_ptr<button> b_five;
    std::unique_ptr<button> b_six;
    std::unique_ptr<button> b_seven;
    std::unique_ptr<button> b_eight;
    std::unique_ptr<button> b_nine;
    std::unique_ptr<button> b_ten;

public:
    setFigure(gameState* _game);
    ~setFigure();
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

