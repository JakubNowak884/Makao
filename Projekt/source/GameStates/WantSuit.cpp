#include "..\headers\GameStates\WantSuit.h"

WantSuit::WantSuit(Game* _game, std::shared_ptr<Resources> _resources)
    : GameState(_resources)
{
    initText(textChoose, 0, 0, 48);
    textChoose.setString(resources->getText(int(gameStateNumber::wantSuit), 1));

    b_clubs = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantSuit), 2), resources->getFont(), 200.0f, 100.0f, 200.0f, 150.0f, resources->getTexturePtr("button"), 32);
    b_diamonds = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantSuit), 3), resources->getFont(), 200.0f, 100.0f, 200.0f, 260.0f, resources->getTexturePtr("button"), 32);
    b_hearts = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantSuit), 4), resources->getFont(), 200.0f, 100.0f, 600.0f, 150.0f, resources->getTexturePtr("button"), 32);
    b_spades = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantSuit), 5), resources->getFont(), 200.0f, 100.0f, 600.0f, 260.0f, resources->getTexturePtr("button"), 32);

    prev = _game;
}

gameStateNumber WantSuit::update(sf::Event event, sf::RenderWindow& window)
{
    //przesuwanie kart w rêce w prawo lub w lewo
    if (event.type == sf::Event::MouseWheelScrolled || event.type == sf::Event::KeyPressed)
    {
        if ((event.mouseWheelScroll.delta > 0 || event.key.code == sf::Keyboard::Right) && (prev->getHand().front())->getX() < 800)
        {
            for (std::vector<std::shared_ptr<Card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
            {
                (*i)->setPosition(sf::Vector2f((*i)->getX() + 128, 800));
            }
        }
        else if ((event.mouseWheelScroll.delta < 0 || event.key.code == sf::Keyboard::Left) && prev->getHand().back()->getX() > 0)
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

void WantSuit::draw(sf::RenderWindow& window)
{
    for (std::vector<std::shared_ptr<Card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
    {
        if ((*i)->getX() > -200 && (*i)->getX() < 1000)
            (*i)->draw(window);
    }

    window.draw(textChoose);

    b_clubs->draw(window);
    b_diamonds->draw(window);
    b_hearts->draw(window);
    b_spades->draw(window);
}
