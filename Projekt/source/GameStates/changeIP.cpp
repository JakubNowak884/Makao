#include "..\headers\GameStates\changeIP.h"
#include "..\headers\Resources.h"

ChangeIP::ChangeIP(MultiPlayerSettings* _prev, Resources* _resources)
    : GameState(_resources)
{
    prev = _prev;

    initText(currentIP, 0, 200, 36);
    currentIP.setString(resources->getText(int(gameStateNumber::singlePlayerSettings), 1) + sf::String(prev->getIP()));

    b_back = std::make_unique<Button>(resources->getText(int(gameStateNumber::singlePlayerSettings), 2), resources->getFont(), 600, 150, 400, 600, resources->getTexturePtr("button"));
}

gameStateNumber ChangeIP::update(sf::Event event, sf::RenderWindow& window)
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

void ChangeIP::draw(sf::RenderWindow& window)
{
    currentIP.setString(resources->getText(int(gameStateNumber::singlePlayerSettings), 1) + sf::String(prev->getIP()));
    window.draw(currentIP);

    b_back->draw(window);
}
