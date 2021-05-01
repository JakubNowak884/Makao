#include "..\headers\GameStates\changeIP.h"

changeIP::changeIP(multiPlayerSettings* _prev, Resources* _resources)
    : gameState(_resources)
{
    prev = _prev;

    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    currentIP.setCharacterSize(36);
    currentIP.setFillColor(sf::Color::White);
    currentIP.setFont(font);
    currentIP.setPosition(0, 200);
    currentIP.setString("Aktualne IP: " + prev->getIP());

    b_back = std::make_unique<button>(L"Wroc", font, 600, 150, 400, 600, resources->getTexturePtr("button"));
}

gameStateNumber changeIP::update(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::TextEntered)
    {
        char sign = static_cast<char>(event.text.unicode);
        prev->setIP(sign);
    }

    if (b_back->clicked(event))
    {
        return gameStateNumber::resume;
    }

    b_back->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void changeIP::draw(sf::RenderWindow& window)
{
    currentIP.setString("Aktualne IP: " + prev->getIP());
    window.draw(currentIP);

    b_back->draw(window);
}
