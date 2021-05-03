#pragma once
#include "GameState.h"

class Menu :
    public GameState
{
    static int languageVersion;

    sf::Text currentPlayer;

    std::unique_ptr<Button> b_changeName;
    std::unique_ptr<Button> b_singlePlayer;
    std::unique_ptr<Button> b_multiPlayer;
    std::unique_ptr<Button> b_instruction;
    std::unique_ptr<Button> b_quit;
    std::unique_ptr<Button> b_language;

public:
    Menu(Resources* _resources);
    gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

