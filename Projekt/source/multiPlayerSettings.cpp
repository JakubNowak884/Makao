#include "headers/multiPlayerSettings.h"

multiPlayerSettings::multiPlayerSettings()
{
    font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(0, 0);
    text.setString("Nazwa gracza: " + getPlayerName() + '\n' + "IP gry LAN: " + IP_LAN + '\n' + "IP gry ONLINE: " + IP_Online);

    b_changeName = std::make_unique<button>("Zmien", font, 150, 40, 715, 25, 36);
    b_changeIP_LAN = std::make_unique<button>("Zmien", font, 150, 40, 715, 75, 36);
    b_changeIP_Online = std::make_unique<button>("Zmien", font, 150, 40, 715, 125, 36);

    b_joinLAN= std::make_unique<button>("Dolacz do\nsesji LAN", font, 380, 180, 200, 500, 56);
    b_createLAN = std::make_unique<button>("Stworz\nsesje LAN", font, 380, 180, 200, 700, 56);
    b_joinOnline = std::make_unique<button>("Dolacz do\nsesji ONLINE", font, 380, 180, 600, 500, 56);
    b_createOnline = std::make_unique<button>("Stworz\nsesje ONLINE", font, 380, 180, 600, 700, 56);
}

void multiPlayerSettings::setIP(char sign)
{
    std::string* text;
    if (settingIP_LAN)
        text = &IP_LAN;
    else
        text = &IP_Online;

    if (((47 < sign && sign < 58) || sign == 46) && (*text).length() < 15)
    {
        if ((*text).front() == 32)
            (*text).front() = sign;
        else
            (*text) += sign;
    }
    else if (sign == 8)
    {
        if ((*text).length() == 1)
            (*text).front() = 32;
        else
            (*text).pop_back();
    }
}

std::string multiPlayerSettings::getIP()
{
    if (settingIP_LAN)
        return IP_LAN;
    else
        return IP_Online;
}

bool multiPlayerSettings::getHost()
{
    return host;
}

gameStateNumber multiPlayerSettings::update(sf::Event event, sf::RenderWindow& window)
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
        return gameStateNumber::mutliPlayer;
    }

    if (b_createLAN->clicked(event))
    {
        host = true;
        return gameStateNumber::mutliPlayer;
    }

    if (b_joinOnline->clicked(event));

    if (b_createOnline->clicked(event));

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

    return gameStateNumber::def;
}

void multiPlayerSettings::draw(sf::RenderWindow& window)
{
    text.setString("Nazwa gracza: " + getPlayerName() + '\n' + "IP gry LAN: " + IP_LAN + '\n' + "IP gry ONLINE: " + IP_Online);
    window.draw(text);

    b_changeName->draw(window);
    b_changeIP_LAN->draw(window);
    b_changeIP_Online->draw(window);
    b_joinLAN->draw(window);
    b_createLAN->draw(window);
    b_joinOnline->draw(window);
    b_createOnline->draw(window);
}
