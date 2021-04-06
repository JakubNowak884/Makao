#pragma once
#include "headers\object.h"

class button :
    public object
{
    sf::Text text;
    int textSize;

    float textEndl(const std::string& text);

public:
    button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, int _textSize = 86)
        : object(_width, _height, _x, _y), textSize(_textSize)
    {

        text.setFont(font);
        text.setString(textToBeShowed);
        text.setCharacterSize(int(textSize));
        text.setOrigin(text.getLocalBounds().width / 2, (textSize * 3 / 4) + textSize * textEndl(textToBeShowed));
        text.setPosition(_x, _y);
    }
    void setString(std::string _text);
    bool clicked(sf::Event& event);
    void draw(sf::RenderWindow& window);
};

