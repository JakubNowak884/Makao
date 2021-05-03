#include "..\headers\GameStates\setFigure.h"
#include "..\headers\Resources.h"

SetFigure::SetFigure(Game* _game, Resources* resources)
    : GameState(resources)
{
    initText(text, 0, 0, 48);
    text.setString(resources->getText(int(gameStateNumber::setFigure), 1));

    b_five = std::make_unique<Button>(resources->getText(int(gameStateNumber::setFigure), 2), resources->getFont(), 200, 100, 200, 150, resources->getTexturePtr("button"), 32);
    b_six = std::make_unique<Button>(resources->getText(int(gameStateNumber::setFigure), 3), resources->getFont(), 200, 100, 600, 150, resources->getTexturePtr("button"), 32);
    b_seven = std::make_unique<Button>(resources->getText(int(gameStateNumber::setFigure), 4), resources->getFont(), 200, 100, 200, 260, resources->getTexturePtr("button"), 32);
    b_eight = std::make_unique<Button>(resources->getText(int(gameStateNumber::setFigure), 5), resources->getFont(), 200, 100, 600, 260, resources->getTexturePtr("button"), 32);
    b_nine = std::make_unique<Button>(resources->getText(int(gameStateNumber::setFigure), 6), resources->getFont(), 200, 100, 200, 370, resources->getTexturePtr("button"), 32);
    b_ten = std::make_unique<Button>(resources->getText(int(gameStateNumber::setFigure), 7), resources->getFont(), 200, 100, 600, 370, resources->getTexturePtr("button"), 32);

    prev = _game;
}

gameStateNumber SetFigure::update(sf::Event event, sf::RenderWindow& window)
{
    if(event.type == sf::Event::MouseWheelScrolled)
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

    if (b_five->clicked(event))
    {
        prev->setCurrentFigure(figureNumber::five);
        return gameStateNumber::resume;
    }
    if (b_six->clicked(event))
    {
        prev->setCurrentFigure(figureNumber::six);
        return gameStateNumber::resume;
    }
    if (b_seven->clicked(event))
    {
        prev->setCurrentFigure(figureNumber::seven);
        return gameStateNumber::resume;
    }
    if (b_eight->clicked(event))
    {
        prev->setCurrentFigure(figureNumber::eight);
        return gameStateNumber::resume;
    }
    if (b_nine->clicked(event))
    {
        prev->setCurrentFigure(figureNumber::nine);
        return gameStateNumber::resume;
    }
    if (b_ten->clicked(event))
    {
        prev->setCurrentFigure(figureNumber::ten);
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

void SetFigure::draw(sf::RenderWindow& window)
{
    for (std::vector<std::shared_ptr<Card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
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
