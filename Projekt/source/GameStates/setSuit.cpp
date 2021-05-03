#include "..\headers\GameStates\setSuit.h"
#include "..\headers\Resources.h"

SetSuit::SetSuit(Game* _game, Resources* _resources)
    : GameState(_resources)
{
    initText(text, 0, 0, 48);
    text.setString(resources->getText(int(gameStateNumber::setSuit), 1));

    b_clubs = std::make_unique<Button>(resources->getText(int(gameStateNumber::setSuit), 2), resources->getFont(), 200, 100, 200, 150, resources->getTexturePtr("button"), 32);
    b_diamonds = std::make_unique<Button>(resources->getText(int(gameStateNumber::setSuit), 3), resources->getFont(), 200, 100, 200, 260, resources->getTexturePtr("button"), 32);
    b_hearts = std::make_unique<Button>(resources->getText(int(gameStateNumber::setSuit), 4), resources->getFont(), 200, 100, 600, 150, resources->getTexturePtr("button"), 32);
    b_spades = std::make_unique<Button>(resources->getText(int(gameStateNumber::setSuit), 5), resources->getFont(), 200, 100, 600, 260, resources->getTexturePtr("button"), 32);

    prev = _game;
}

gameStateNumber SetSuit::update(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0 && (prev->getHand().front())->getX() < 800)
        {
            for (std::vector<std::shared_ptr<Card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
            {
                (*i)->setPosition(sf::Vector2f((*i)->getX() + 128, 800));
            }
        }
        else if (event.mouseWheelScroll.delta < 0 && prev->getHand().back()->getX() > 0)
        {
            for (std::vector<std::shared_ptr<Card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
            {
                (*i)->setPosition(sf::Vector2f((*i)->getX() - 128, 800));
            }
        }
    }

    if (b_clubs->clicked(event))
    {
        prev->setCurrentSuit(suitNumber::clubs);
        return gameStateNumber::resume;
    }
    if (b_diamonds->clicked(event))
    {
        prev->setCurrentSuit(suitNumber::diamonds);
        return gameStateNumber::resume;
    }
    if (b_hearts->clicked(event))
    {
        prev->setCurrentSuit(suitNumber::hearts);
        return gameStateNumber::resume;
    }
    if (b_spades->clicked(event))
    {
        prev->setCurrentSuit(suitNumber::spades);
        return gameStateNumber::resume;
    }

    b_clubs->uptade(getMousePos(window));
    b_diamonds->uptade(getMousePos(window));
    b_hearts->uptade(getMousePos(window));
    b_spades->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void SetSuit::draw(sf::RenderWindow& window)
{
    for (std::vector<std::shared_ptr<Card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
    {
        if ((*i)->getX() > -200 && (*i)->getX() < 1000)
            (*i)->draw(window);
    }

    window.draw(text);

    b_clubs->draw(window);
    b_diamonds->draw(window);
    b_hearts->draw(window);
    b_spades->draw(window);
}
