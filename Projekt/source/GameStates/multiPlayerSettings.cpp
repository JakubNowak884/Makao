#include "..\headers\GameStates\multiPlayerSettings.h"
#include "..\headers\Resources.h"

MultiPlayerSettings::MultiPlayerSettings(std::shared_ptr<Resources> _resources)
    : GameState(_resources)
{
    initText(textSettings, 0, 0, 36);

    b_changeName = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 5), resources->getFont(), 150, 35, 715, 25, resources->getTexturePtr("button"), 32);
    b_changeIP_LAN = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 5), resources->getFont(), 150, 35, 715, 65, resources->getTexturePtr("button"), 32);
    b_changeIP_Online = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 5), resources->getFont(), 150, 35, 715, 105, resources->getTexturePtr("button"), 32);
    b_onlyQueens = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 10), resources->getFont(), 150, 35, 715, 155, resources->getTexturePtr("button"), 24);

    b_joinLAN= std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 6), resources->getFont(), 380, 180, 200, 500, resources->getTexturePtr("button"), 56);
    b_createLAN = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 7), resources->getFont(), 380, 180, 200, 700, resources->getTexturePtr("button"), 56);
    b_joinOnline = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 8), resources->getFont(), 380, 180, 600, 500, resources->getTexturePtr("button"), 56);
    b_createOnline = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayerSettings), 9), resources->getFont(), 380, 180, 600, 700, resources->getTexturePtr("button"), 56);
}

void MultiPlayerSettings::setIP(char sign)
{
    std::string* text;
    if (settingIP_LAN)
        text = &IP_LAN;
    else
        text = &IP_Online;
    //w adresie ip mog¹ znajdowaæ siê tylko cyfry i kropki oraz nie mo¿e byæ d³u¿szy niz 20 znaków
    if (((47 < sign && sign < 58) || sign == 46) && (*text).length() < 20)
    {
        //jeœi pierwszy znak by³ spacj¹ zastêpywany jest on nowym znakiem
        if ((*text).front() == 32)
            (*text).front() = sign;
        else
            (*text) += sign;
    }
    //backspace
    else if (sign == 8)
    {
        //jeœli napis mia³by zostaæ bez znaków, pierwszy znak zastêpywany jest spacj¹
        if ((*text).length() == 1)
            (*text).front() = 32;
        else
            (*text).pop_back();
    }
}

bool MultiPlayerSettings::getLAN()
{
    return settingIP_LAN;
}

std::string MultiPlayerSettings::getIP()
{
    if (settingIP_LAN)
        return IP_LAN;
    else
        return IP_Online;
}

bool MultiPlayerSettings::getHost()
{
    return host;
}

bool MultiPlayerSettings::getOnlyQueens()
{
    return onlyQueens;
}

gameStateNumber MultiPlayerSettings::update(sf::Event event, sf::RenderWindow& window)
{
    if (b_changeName->clicked(event))
    {
        return gameStateNumber::changeName;
    }

    if (b_changeIP_LAN->clicked(event))
    {
        settingIP_LAN = true;
        return gameStateNumber::changeIP;
    }

    if (b_changeIP_Online->clicked(event))
    {
        settingIP_LAN = false;
        return gameStateNumber::changeIP;
    }

    if (b_joinLAN->clicked(event))
    {
        host = false;
        settingIP_LAN = true;
        b_joinLAN->setString(resources->getText(int(gameStateNumber::multiPlayerSettings), 11));
        draw(window);
        window.display();
        return gameStateNumber::multiPlayer;
    }

    if (b_createLAN->clicked(event))
    {
        host = true;
        settingIP_LAN = true;
        return gameStateNumber::multiPlayer;
    }

    if (b_joinOnline->clicked(event))
    {
        host = false;
        settingIP_LAN = false;
        b_joinOnline->setString(resources->getText(int(gameStateNumber::multiPlayerSettings), 11));
        draw(window);
        window.display();
        return gameStateNumber::multiPlayer;
    }

    if (b_createOnline->clicked(event))
    {
        host = true;
        settingIP_LAN = false;
        return gameStateNumber::multiPlayer;
    }

    if (b_onlyQueens->clicked(event))
    {
        if (onlyQueens)
            onlyQueens = false;
        else
            onlyQueens = true;
    }

    if (event.type == sf::Event::TextEntered)
    {
        char sign = static_cast<char>(event.text.unicode);
        setIP(sign);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        return gameStateNumber::menu;

    b_changeName->uptade(getMousePos(window));
    b_changeIP_LAN->uptade(getMousePos(window));
    b_changeIP_Online->uptade(getMousePos(window));
    b_joinLAN->uptade(getMousePos(window));
    b_createLAN->uptade(getMousePos(window));
    b_joinOnline->uptade(getMousePos(window));
    b_createOnline->uptade(getMousePos(window));
    b_onlyQueens->uptade(getMousePos(window));

    return gameStateNumber::def;
}

void MultiPlayerSettings::draw(sf::RenderWindow& window)
{
    textSettings.setString(resources->getText(int(gameStateNumber::multiPlayerSettings), 1) + getPlayerName() + L"\n" + resources->getText(int(gameStateNumber::multiPlayerSettings), 2));
    textSettings.setString(textSettings.getString() + sf::String(IP_LAN) + L"\n" + resources->getText(int(gameStateNumber::multiPlayerSettings), 3) + IP_Online + resources->getText(int(gameStateNumber::multiPlayerSettings), 4));
    window.draw(textSettings);

    b_changeName->draw(window);
    b_changeIP_LAN->draw(window);
    b_changeIP_Online->draw(window);
    b_joinLAN->draw(window);
    b_createLAN->draw(window);
    b_joinOnline->draw(window);
    b_createOnline->draw(window);
    if (onlyQueens)
        b_onlyQueens->setString(resources->getText(int(gameStateNumber::multiPlayerSettings), 12));
    else
        b_onlyQueens->setString(resources->getText(int(gameStateNumber::multiPlayerSettings), 10));
    b_onlyQueens->draw(window);
}
