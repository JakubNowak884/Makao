#include "..\headers\GameStates\gameState.h"
#include "..\headers\Resources.h"

std::wstring GameState::playerName = L"Gracz";

void GameState::setPlayerName(char sign)
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

std::wstring GameState::getPlayerName()
{
    return playerName;
}

sf::Vector2f GameState::getMousePos(sf::RenderWindow& window)
{
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    return mouseWorldPos;
}

void GameState::initText(sf::Text& text, float posX, float posY, int size, sf::Color color)
{
    text.setFont(resources->getFont());
    text.setPosition(posX, posY);
    text.setCharacterSize(size);
    text.setFillColor(color);
}
