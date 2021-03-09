#pragma once
#include "headers\object.h"

class button :
    public virtual object
{
    sf::Text text;

    float textSize = 86;

public:
    button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y)
        : object(_width, _height, _x, _y)
    {

        text.setFont(font);
        text.setString(textToBeShowed);
        text.setCharacterSize(int(textSize));
        text.setOrigin(text.getLocalBounds().width / 2, textSize * 3 / 4);
        text.setPosition(_x, _y);
    }
    bool clicked(sf::Event& event);
    void draw(sf::RenderWindow& window);
};

