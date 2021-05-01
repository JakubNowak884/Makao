#include "..\headers\GameStates\setSuit.h"

setSuit::setSuit(game* _game, Resources* _resources)
    : gameState(_resources)
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    text.setFont(resources->getFont());
    text.setCharacterSize(48);
    text.setPosition(0, 0);
    text.setString("Wybierz zadany kolor: ");

    b_clubs = std::make_unique<button>("Trefl", resources->getFont(), 200, 100, 200, 150, resources->getTexturePtr("button"), 32);
    b_diamonds = std::make_unique<button>("Karo", resources->getFont(), 200, 100, 200, 260, resources->getTexturePtr("button"), 32);
    b_hearts = std::make_unique<button>("Serce", resources->getFont(), 200, 100, 600, 150, resources->getTexturePtr("button"), 32);
    b_spades = std::make_unique<button>("Pik", resources->getFont(), 200, 100, 600, 260, resources->getTexturePtr("button"), 32);

    prev = _game;
}

gameStateNumber setSuit::update(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0 && (prev->getHand().front())->getX() < 800)
        {
            for (std::vector<std::shared_ptr<card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
            {
                (*i)->setPosition(sf::Vector2f((*i)->getX() + 128, 800));
            }
        }
        else if (event.mouseWheelScroll.delta < 0 && prev->getHand().back()->getX() > 0)
        {
            for (std::vector<std::shared_ptr<card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
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

void setSuit::draw(sf::RenderWindow& window)
{
    for (std::vector<std::shared_ptr<card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
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
