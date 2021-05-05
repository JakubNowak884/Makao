#include "../headers/GameStates/menu.h"
#include "../headers/Resources.h"

int Menu::languageVersion = 0;

Menu::Menu(Resources* _resources)
    : GameState(_resources)
{
    initText(currentPlayer, 0, 0, 36);
    currentPlayer.setString(resources->getText(int(gameStateNumber::menu), 6) + getPlayerName());

    b_changeName = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 1), resources->getFont(), 150, 40, currentPlayer.getLocalBounds().width + 30, 25, resources->getTexturePtr("button"), 36);
    b_singlePlayer = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 2), resources->getFont(), 600, 150, 400, 150, resources->getTexturePtr("button"));
    b_multiPlayer = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 3), resources->getFont(), 600, 150, 400, 325, resources->getTexturePtr("button"));
    b_instruction = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 4), resources->getFont(), 600, 150, 400, 500, resources->getTexturePtr("button"));
    b_quit = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 5), resources->getFont(), 600, 150, 400, 675, resources->getTexturePtr("button"));
    b_language = std::make_unique<Button>(resources->getText(int(gameStateNumber::menu), 6), resources->getFont(), 200, 30, 110, 775, resources->getTexturePtr("button"), 24);
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
        if (languageVersion == 0)
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
            languageVersion = 1;
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
            languageVersion = 0;
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

