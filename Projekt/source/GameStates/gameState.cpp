#include "..\headers\GameStates\gameState.h"

std::string gameState::playerName = "Gracz";

void gameState::setPlayerName(char sign)
{
    if (((64 < sign && sign < 91) || (96 < sign && sign < 123)) && playerName.length() < 10)
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
