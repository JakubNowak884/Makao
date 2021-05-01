#include "../headers/GameStates/menu.h"

menu::menu(Resources* _resources)
    : gameState(_resources)
{
    font.loadFromFile("../resources/fonts/Aleo-Regular.otf");

    currentPlayer.setCharacterSize(36);
    currentPlayer.setFillColor(sf::Color::White);
    currentPlayer.setFont(resources->getFont());
    currentPlayer.setPosition(0, 0);
    currentPlayer.setString("Aktualnie gra: " + getPlayerName());

    b_changeName = std::make_unique<button>("Zmien", resources->getFont(), 150, 40, currentPlayer.getLocalBounds().width + 30, 25, resources->getTexturePtr("button"), 36);
    b_singlePlayer = std::make_unique<button>("Jeden gracz", resources->getFont(), 600, 150, 400, 150, resources->getTexturePtr("button"));
    b_multiPlayer = std::make_unique<button>("Wielu graczy", resources->getFont(), 600, 150, 400, 325, resources->getTexturePtr("button"));
    b_instruction = std::make_unique<button>("Instrukcja", resources->getFont(), 600, 150, 400, 500, resources->getTexturePtr("button"));
    b_quit = std::make_unique<button>(L"WyjdŸ", resources->getFont(), 600, 150, 400, 675, resources->getTexturePtr("button"));
}

gameStateNumber menu::update(sf::Event event, sf::RenderWindow& window)
{
    if (b_changeName->clicked(event))
    {
        return gameStateNumber::changeName;
    }
    if (b_singlePlayer->clicked(event))
    {
        return gameStateNumber::singlePlayerSettings;
    }
    if (b_multiPlayer->clicked(event))
    {
        return gameStateNumber::multiPlayerSettings;
    }
    if (b_instruction->clicked(event))
    {
        return gameStateNumber::instruction;
    }
    if (b_quit->clicked(event))
    {
        return gameStateNumber::quit;
    }

    b_changeName->uptade(getMousePos(window));
    b_singlePlayer->uptade(getMousePos(window));
    b_multiPlayer->uptade(getMousePos(window));
    b_instruction->uptade(getMousePos(window));
    b_quit->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void menu::draw(sf::RenderWindow& window)
{
    currentPlayer.setString("Aktualnie gra: " + getPlayerName());
    window.draw(currentPlayer);

    b_changeName->setPosition(sf::Vector2f(currentPlayer.getLocalBounds().width + 100, 25));
    b_changeName->draw(window);
    b_singlePlayer->draw(window);
    b_multiPlayer->draw(window);
    b_instruction->draw(window);
    b_quit->draw(window);
}

