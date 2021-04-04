#pragma once
#include "headers\object.h"

class button :
    public virtual object
{
    sf::Text text;
    float textEndl(const std::string& text);

public:
    button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, int textSize = 86)
        : object(_width, _height, _x, _y)
    {

        text.setFont(font);
        text.setString(textToBeShowed);
        text.setCharacterSize(int(textSize));
        text.setOrigin(text.getLocalBounds().width / 2, (textSize * 3 / 4) + textSize * textEndl(textToBeShowed));
        text.setPosition(_x, _y);
    }
    bool clicked(sf::Event& event);
    void draw(sf::RenderWindow& window);
};

