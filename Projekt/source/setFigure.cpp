#include "headers\setFigure.h"

setFigure::setFigure(gameState* _game)
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    text.setFont(font);
    text.setCharacterSize(48);
    text.setPosition(0, 0);
    text.setString("Wybierz zadana figure: ");

    b_five = std::make_unique<button>("Piatki", font, 200, 100, 200, 150, 32);
    b_six = std::make_unique<button>("Szostki", font, 200, 100, 600, 150, 32);
    b_seven = std::make_unique<button>("Siodemki", font, 200, 100, 200, 260, 32);
    b_eight = std::make_unique<button>("Osemki", font, 200, 100, 600, 260, 32);
    b_nine = std::make_unique<button>("Dziewiatki", font, 200, 100, 200, 370, 32);
    b_ten = std::make_unique<button>("Dziesiatki", font, 200, 100, 600, 370, 32);

    game = _game;
}

gameStateNumber setFigure::update(sf::Event event, sf::RenderWindow& window)
{
    if(event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0 && (game->getHand().front())->getX() < 800)
        {
            for (std::vector<card*>::iterator i = game->getHand().begin(); i != game->getHand().end(); i++)
            {
                (*i)->setPosition(sf::Vector2f((*i)->getX() + 128, 800));
            }
        }
        else if (event.mouseWheelScroll.delta < 0 && game->getHand().back()->getX() > 0)
        {
            for (std::vector<card*>::iterator i = game->getHand().begin(); i != game->getHand().end(); i++)
            {
                (*i)->setPosition(sf::Vector2f((*i)->getX() - 128, 800));
            }
        }
    }

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
    for (std::vector<card*>::iterator i = game->getHand().begin(); i != game->getHand().end(); i++)
    {
        if ((*i)->getX() > -200 && (*i)->getX() < 1000)
            (*i)->draw(window);
    }

    window.draw(text);

    b_five->draw(window);
    b_six->draw(window);
    b_seven->draw(window);
    b_eight->draw(window);
    b_nine->draw(window);
    b_ten->draw(window);
}
