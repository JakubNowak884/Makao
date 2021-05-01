#include "..\headers\GameStates\changeName.h"

changeName::changeName(Resources* _resources)
    : gameState(_resources)
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    currentName.setCharacterSize(36);
    currentName.setFillColor(sf::Color::White);
    currentName.setFont(resources->getFont());
    currentName.setPosition(0, 200);
    currentName.setString("Aktualna nazwa gracza: " + getPlayerName());

    b_back = std::make_unique<button>(L"Wroc", resources->getFont(), 600, 150, 400, 600, resources->getTexturePtr("button"));
}

gameStateNumber changeName::update(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::TextEntered)
    {
        char sign = static_cast<char>(event.text.unicode);
        setPlayerName(sign);
    }

    if (b_back->clicked(event))
    {
        return gameStateNumber::resume;
    }

    if (getPlayerName().length() - 1 != 0)
        b_back->uptade(getMousePos(window));

    if (getPlayerName().length() - 1 <= 0)
        b_back->setChosen(false);

    return gameStateNumber::def;
}

void changeName::draw(sf::RenderWindow& window)
{
    currentName.setString("Aktualna nazwa gracza: " + getPlayerName());
    window.draw(currentName);

    b_back->draw(window);
}
