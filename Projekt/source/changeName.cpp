#include "headers/changeName.h"

changeName::changeName()
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    currentName.setCharacterSize(36);
    currentName.setFillColor(sf::Color::White);
    currentName.setFont(font);
    currentName.setPosition(0, 200);
    currentName.setString("Aktualna nazwa gracza: " + getPlayerName());

    b_back = std::make_unique<button>("Wroc", font, 600, 150, 400, 600);
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

    b_back->uptade(getMousePos(window));
}

void changeName::draw(sf::RenderWindow& window)
{
    currentName.setString("Aktualna nazwa gracza: " + getPlayerName());
    window.draw(currentName);

    b_back->draw(window);
}
