#include "..\headers\GameStates\changeName.h"
#include "..\headers\Resources.h"

ChangeName::ChangeName(Resources* _resources)
    : GameState(_resources)
{
    initText(currentName, 0, 200, 36);
    currentName.setString(resources->getText(int(gameStateNumber::changeName), 1) + getPlayerName());

    b_back = std::make_unique<Button>(resources->getText(int(gameStateNumber::changeName), 2), resources->getFont(), 600, 150, 400, 600, resources->getTexturePtr("button"));
}

gameStateNumber ChangeName::update(sf::Event event, sf::RenderWindow& window)
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

void ChangeName::draw(sf::RenderWindow& window)
{
    currentName.setString(resources->getText(int(gameStateNumber::changeName), 1) + getPlayerName());
    window.draw(currentName);

    b_back->draw(window);
}
