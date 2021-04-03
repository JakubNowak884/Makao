#include "headers\setFigure.h"

setFigure::setFigure(gameState* _game)
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    b_five = std::make_unique<button>("Piatki", font, 200, 200, 150, 150);
    b_six = std::make_unique<button>("Szostki", font, 200, 200, 650, 150);
    b_seven = std::make_unique<button>("Siodemki", font, 200, 200, 150, 400);
    b_eight = std::make_unique<button>("Osemki", font, 200, 200, 650, 400);
    b_nine = std::make_unique<button>("Dziewiatki", font, 200, 200, 150, 650);
    b_ten = std::make_unique<button>("Dziesiatki", font, 200, 200, 650, 650);

    game = _game;
}

setFigure::~setFigure()
{
}

gameStateNumber setFigure::update(sf::Event event, sf::RenderWindow& window)
{
    if (b_five->clicked(event))
    {
        game->setCurrentFigure(figureNumber::five);
        return gameStateNumber::resume;
    }
    if (b_six->clicked(event))
    {
        game->setCurrentFigure(figureNumber::six);
        return gameStateNumber::resume;
    }
    if (b_seven->clicked(event))
    {
        game->setCurrentFigure(figureNumber::seven);
        return gameStateNumber::resume;
    }
    if (b_eight->clicked(event))
    {
        game->setCurrentFigure(figureNumber::eight);
        return gameStateNumber::resume;
    }
    if (b_nine->clicked(event))
    {
        game->setCurrentFigure(figureNumber::nine);
        return gameStateNumber::resume;
    }
    if (b_ten->clicked(event))
    {
        game->setCurrentFigure(figureNumber::ten);
        return gameStateNumber::resume;
    }

    b_five->uptade(getMousePos(window));
    b_six->uptade(getMousePos(window));
    b_seven->uptade(getMousePos(window));
    b_eight->uptade(getMousePos(window));
    b_nine->uptade(getMousePos(window));
    b_ten->uptade(getMousePos(window));
    return gameStateNumber::def;
}

void setFigure::draw(sf::RenderWindow& window)
{
    b_five->draw(window);
    b_six->draw(window);
    b_seven->draw(window);
    b_eight->draw(window);
    b_nine->draw(window);
    b_ten->draw(window);
}
