#pragma once
#include "Object.h"

class Button :
    public Object
{
    sf::Text text;

    int textSize;

    float textEndl(const std::string& text);
    float textEndl(const std::wstring& text);

public:
    Button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86);
    Button(const std::wstring& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86);
    void setString(std::string _text);
    void setString(std::wstring _text);
    void setPosition(sf::Vector2f position) override;
    bool clicked(sf::Event& event);
    void draw(sf::RenderWindow& window) override;
};

