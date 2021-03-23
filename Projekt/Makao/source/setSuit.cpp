#include "headers\setSuit.h"

setSuit::setSuit(gameState* _game)
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    b_clubs = std::make_unique<button>("Trefl", font, 200, 200, 150, 400);
    b_diamonds = std::make_unique<button>("Karo", font, 200, 200, 150, 650);
    b_hearts = std::make_unique<button>("Serce", font, 200, 200, 650, 400);
    b_spades = std::make_unique<button>("Pik", font, 200, 200, 650, 650);

    game = _game;
}

setSuit::~setSuit()
{
}

gameStateNumber setSuit::update(sf::Event event, sf::RenderWindow& window)
{
    if (b_clubs->clicked(event))
    {
        game->setCurrentSuit(suitNumber::clubs);
        return gameStateNumber::resume;
    }
    if (b_diamonds->clicked(event))
    {
        game->setCurrentSuit(suitNumber::diamonds);
        return gameStateNumber::resume;
    }
    if (b_hearts->clicked(event))
    {
        game->setCurrentSuit(suitNumber::hearts);
        return gameStateNumber::resume;
    }
    if (b_spades->clicked(event))
    {
        game->setCurrentSuit(suitNumber::spades);
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
    b_clubs->draw(window);
    b_diamonds->draw(window);
    b_hearts->draw(window);
    b_spades->draw(window);
}
