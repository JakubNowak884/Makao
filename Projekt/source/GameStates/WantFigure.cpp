#include "..\headers\GameStates\WantFigure.h"

WantFigure::WantFigure(Game* _game, std::shared_ptr<Resources> _resources)
    : GameState(_resources)
{
    initText(textChoose, 0, 0, 48);
    textChoose.setString(resources->getText(int(gameStateNumber::wantFigure), 1));

    b_five = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantFigure), 2), resources->getFont(), 200.0f, 100.0f, 200.0f, 150.0f, resources->getTexturePtr("button"), 32);
    b_six = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantFigure), 3), resources->getFont(), 200.0f, 100.0f, 600.0f, 150.0f, resources->getTexturePtr("button"), 32);
    b_seven = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantFigure), 4), resources->getFont(), 200.0f, 100.0f, 200.0f, 260.0f, resources->getTexturePtr("button"), 32);
    b_eight = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantFigure), 5), resources->getFont(), 200.0f, 100.0f, 600.0f, 260.0f, resources->getTexturePtr("button"), 32);
    b_nine = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantFigure), 6), resources->getFont(), 200.0f, 100.0f, 200.0f, 370.0f, resources->getTexturePtr("button"), 32);
    b_ten = std::make_unique<Button>(resources->getText(int(gameStateNumber::wantFigure), 7), resources->getFont(), 200.0f, 100.0f, 600.0f, 370.0f, resources->getTexturePtr("button"), 32);

    prev = _game;
}

gameStateNumber WantFigure::update(sf::Event event, sf::RenderWindow& window)
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

void WantFigure::draw(sf::RenderWindow& window)
{
    for (std::vector<std::shared_ptr<Card>>::iterator i = prev->getHand().begin(); i != prev->getHand().end(); i++)
    {
        if ((*i)->getX() > -200 && (*i)->getX() < 1000)
            (*i)->draw(window);
    }

    window.draw(textChoose);

    b_five->draw(window);
    b_six->draw(window);
    b_seven->draw(window);
    b_eight->draw(window);
    b_nine->draw(window);
    b_ten->draw(window);
}
