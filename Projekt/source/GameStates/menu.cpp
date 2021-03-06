#include "../headers/GameStates/menu.h"

Menu::Menu(std::shared_ptr<Resources> _resources)
    : GameState(_resources)
{
    initText(currentPlayer, 0, 0, 36);

    b_changeName = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 1), resources->getFont(), 150.0f, 40.0f, currentPlayer.getLocalBounds().width + 30, 25, resources->getTexturePtr("button"), 36);
    b_singlePlayer = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 2), resources->getFont(), 600.0f, 150.0f, 400.0f, 150.0f, resources->getTexturePtr("button"));
    b_multiPlayer = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 3), resources->getFont(), 600.0f, 150.0f, 400.0f, 325.0f, resources->getTexturePtr("button"));
    b_instruction = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 4), resources->getFont(), 600.0f, 150.0f, 400.0f, 500.0f, resources->getTexturePtr("button"));
    b_quit = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 5), resources->getFont(), 600.0f, 150.0f, 400.0f, 675.0f, resources->getTexturePtr("button"));
    b_language = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 6), resources->getFont(), 200.0f, 30.0f, 110.0f, 775.0f, resources->getTexturePtr("button"), 24);
}

gameStateNumber Menu::update(sf::Event event, sf::RenderWindow& window)
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
    if (b_language->clicked(event))
    {
        if (resources->getLanguageVersion() == 'p')
        {
            try
            {
                resources->loadLanguage("english");
            }
            catch (const char* error)
            {
                std::ofstream file;
                file.open("error.txt");
                file << error;
                file.close();
                return gameStateNumber::quit;
            }
        }
        else 
        {
            try
            {
                resources->loadLanguage("polish");
            }
            catch (const char* error)
            {
                std::ofstream file;
                file.open("error.txt");
                file << error;
                file.close();
                return gameStateNumber::quit;
            }
        }
        return gameStateNumber::menu;
    }

    b_changeName->uptade(getMousePos(window));
    b_singlePlayer->uptade(getMousePos(window));
    b_multiPlayer->uptade(getMousePos(window));
    b_instruction->uptade(getMousePos(window));
    b_quit->uptade(getMousePos(window));
    b_language->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void Menu::draw(sf::RenderWindow& window)
{
    currentPlayer.setString(resources->getText(int(gameStateNumber::menu), 7) + getPlayerName());
    window.draw(currentPlayer);

    b_changeName->setPosition(sf::Vector2f(currentPlayer.getLocalBounds().width + 100, 25));
    b_changeName->draw(window);
    b_singlePlayer->draw(window);
    b_multiPlayer->draw(window);
    b_instruction->draw(window);
    b_quit->draw(window);
    b_language->draw(window);
}

