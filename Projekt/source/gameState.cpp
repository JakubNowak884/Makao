#include "headers/gameState.h"

int gameState::amountOfPlayers = 2;

std::string gameState::playerName = "Gracz";

void gameState::setAmountOfPlayers(int amount)
{
    amountOfPlayers = 2;
}

int gameState::getAmountOfPlayers()
{
    return amountOfPlayers;
}

void gameState::setPlayerName(std::string name)
{
    playerName = name;
}

void gameState::setPlayerName(char sign)
{
    if (((64 < sign && sign < 91) || (96 < sign && sign < 123)) && playerName.length() < 11)
    {
        if (playerName.front() == 32)
            playerName.front() = sign;
        else
            playerName += sign;
    }
    else if (sign == 8)
    {
        if (playerName.length() == 1)
            playerName.front() = 32;
        else
            playerName.pop_back();
    }
}

std::string gameState::getPlayerName()
{
    return playerName;
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
