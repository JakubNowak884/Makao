#pragma once
#include "..\card.h"
class card_ace :
    public card
{
public:
    card_ace(std::string _name, suitNumber _suit, sf::Font& font, sf::Texture& texture, float _width, float _height, float _x, float _y, sf::Color color)
        : card(_name, _suit, font, texture, _width, _height, _x, _y, color), object(_width, _height, _x, _y, color)
    {

    }
    ~card_ace();
    bool ableToPlay(card* current, bool addDraw, bool second = false) override;
    void draw(sf::RenderWindow& window);
};

