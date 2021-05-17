#include "..\headers\GameStates\gameState.h"

std::wstring GameState::playerName = L"Gracz";

GameState::GameState(std::shared_ptr<Resources> _resources)
    : resources(_resources) {}

void GameState::setPlayerName(char sign)
{
    //nazwa gracza mo�e zawiera� tylko ma�e i du�e litery angielskiego alfabetu oraz nie mo�e by� d�u�sza ni� 10 znak�w
    if (((64 < sign && sign < 91) || (96 < sign && sign < 123)) && playerName.length() < 10)
    {
        if (playerName.front() == 32) //je�li pierwszy znak nazwy gracza by� spacj�, zast�pywany jest podanym w argumencie znakiem
            playerName.front() = sign;
        else
            playerName += sign; //w przeciwnym wypadku do nazwy gracza dodawany jest podany w argumencie znak
    }
    else if (sign == 8) //backspace
    {
        if (playerName.length() == 1) //je�li nazwa gracza mia�aby by� pusta, jej pierwszy znak zast�pywany jest spacj�
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
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window); //pozycja myszy wzgl�dem okna
    sf::Vector2f mouseAreaPos = window.mapPixelToCoords(mousePixelPos); //pozycja myszy wzgl�dem ekranu gry

    return mouseAreaPos;
}

void GameState::initText(sf::Text& text, float posX, float posY, int size, sf::Color color)
{
    text.setFont(resources->getFont());
    text.setPosition(posX, posY);
    text.setCharacterSize(size);
    text.setFillColor(color);
}
