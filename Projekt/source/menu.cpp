#include "headers\menu.h"

menu::menu()
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    currentPlayer.setCharacterSize(36);
    currentPlayer.setFillColor(sf::Color::White);
    currentPlayer.setFont(font);
    currentPlayer.setPosition(0, 0);
    currentPlayer.setString("Aktualnie gra: " + getPlayerName());

    b_singlePlayer = std::make_unique<button>("Jeden gracz", font, 600, 150, 400, 150);
    b_multiPlayer = std::make_unique<button>("Wielu graczy", font, 600, 150, 400, 310);
    b_changeName = std::make_unique<button>("Zmien nazwe", font, 600, 150, 400, 510);
    b_quit = std::make_unique<button>("Wyjdz", font, 600, 150, 400, 700);
}

menu::~menu()
{
}

gameStateNumber menu::update(sf::Event event, sf::RenderWindow& window)
{
    if (b_singlePlayer->clicked(event))
    {
        return gameStateNumber::singlePlayerSettings;
    }
    if (b_multiPlayer->clicked(event));
    if (b_changeName->clicked(event));
    if (b_quit->clicked(event))
    {
        return gameStateNumber::quit;
    }

    b_singlePlayer->uptade(getMousePos(window));
    b_multiPlayer->uptade(getMousePos(window));
    b_changeName->uptade(getMousePos(window));
    b_quit->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void menu::draw(sf::RenderWindow& window)
{
    currentPlayer.setString("Aktualnie gra: " + getPlayerName());
    window.draw(currentPlayer);

    b_singlePlayer->draw(window);
    b_multiPlayer->draw(window);
    b_changeName->draw(window);
    b_quit->draw(window);
}

