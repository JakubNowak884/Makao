#include "..\headers\GameStates\changeIP.h"

ChangeIP::ChangeIP(MultiPlayerSettings* _prev, std::shared_ptr<Resources> _resources)
    : GameState(_resources), prev(_prev)
{
    initText(currentIP, 0, 200, 36);

    b_back = std::make_unique<Button>(resources->getText(int(gameStateNumber::changeIP), 2), resources->getFont(), 600.0f, 150.0f, 400.0f, 600.0f, resources->getTexturePtr("button"));
}

gameStateNumber ChangeIP::update(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::TextEntered)
    {
        char sign = static_cast<char>(event.text.unicode);
        prev->setIP(sign);
    }

    if (b_back->clicked(event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
    {
        return gameStateNumber::resume;
    }

    b_back->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void ChangeIP::draw(sf::RenderWindow& window)
{
    currentIP.setString(resources->getText(int(gameStateNumber::changeIP), 1) + sf::String(prev->getIP()));
    window.draw(currentIP);

    b_back->draw(window);
}
