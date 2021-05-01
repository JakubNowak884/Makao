#pragma once
#include "gameState.h"

class menu :
    public gameState
{
    sf::Font font;

    sf::Text currentPlayer;

    std::unique_ptr<button> b_changeName;
    std::unique_ptr<button> b_singlePlayer;
    std::unique_ptr<button> b_multiPlayer;
    std::unique_ptr<button> b_instruction;
    std::unique_ptr<button> b_quit;

public:
    menu(Resources* _resources);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

