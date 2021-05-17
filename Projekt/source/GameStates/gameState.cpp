#include "..\headers\GameStates\gameState.h"

std::wstring GameState::playerName = L"Gracz";

GameState::GameState(std::shared_ptr<Resources> _resources)
    : resources(_resources) {}

void GameState::setPlayerName(char sign)
{
    //nazwa gracza mo¿e zawieraæ tylko ma³e i du¿e litery angielskiego alfabetu oraz nie mo¿e byæ d³u¿sza ni¿ 10 znaków
    if (((64 < sign && sign < 91) || (96 < sign && sign < 123)) && playerName.length() < 10)
    {
        if (playerName.front() == 32) //jeœli pierwszy znak nazwy gracza by³ spacj¹, zastêpywany jest podanym w argumencie znakiem
            playerName.front() = sign;
        else
            playerName += sign; //w przeciwnym wypadku do nazwy gracza dodawany jest podany w argumencie znak
    }
    else if (sign == 8) //backspace
    {
        if (playerName.length() == 1) //jeœli nazwa gracza mia³aby byæ pusta, jej pierwszy znak zastêpywany jest spacj¹
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
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window); //pozycja myszy wzglêdem okna
    sf::Vector2f mouseAreaPos = window.mapPixelToCoords(mousePixelPos); //pozycja myszy wzglêdem ekranu gry

    return mouseAreaPos;
}

void GameState::initText(sf::Text& text, float posX, float posY, int size, sf::Color color)
{
    text.setFont(resources->getFont());
    text.setPosition(posX, posY);
    text.setCharacterSize(size);
    text.setFillColor(color);
}
