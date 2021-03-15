#include "headers\menu.h"

menu::menu()
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    b_singlePlayer = new button("Jeden gracz", font, 600, 200, 400, 150);
    b_multiPlayer = new button("Wielu graczy", font, 600, 200, 400, 400);
    b_quit = new button("Wyjdz", font, 600, 200, 400, 650);
}

menu::~menu()
{
    delete b_singlePlayer;
    delete b_multiPlayer;
    delete b_quit;
}

gameStateNumber menu::update(sf::Event event, sf::RenderWindow& window)
{
    if (b_singlePlayer->clicked(event))
    {
        return gameStateNumber::singlePlayerSettings;
    }
    if (b_multiPlayer->clicked(event));
    if (b_quit->clicked(event))
    {
        return gameStateNumber::quit;
    }

    b_singlePlayer->uptade(getMousePos(window));
    b_multiPlayer->uptade(getMousePos(window));
    b_quit->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void menu::draw(sf::RenderWindow& window)
{
    b_singlePlayer->draw(window);
    b_multiPlayer->draw(window);
    b_quit->draw(window);
}

