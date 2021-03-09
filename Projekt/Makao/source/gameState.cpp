#include "headers/gameState.h"

int gameState::amountOfPlayers = 2;

void gameState::setAmountOfPlayers(int amount)
{
    amountOfPlayers = 2;
}

int gameState::getAmountOfPlayers()
{
    return amountOfPlayers;
}

sf::Vector2f gameState::getMousePos(sf::RenderWindow& window)
{
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    return mouseWorldPos;
}

AI* gameState::getAI(int number)
{
    return nullptr;
}

int gameState::getWon()
{
    return 0;
}
