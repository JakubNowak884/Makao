#pragma once
#include "object.h"

enum class suitNumber { clubs = 0, diamonds = 1, hearts = 2, spades = 3 };

class card :
    public virtual object
{
    sf::Text name[2];
    sf::Sprite sprite[2];
    suitNumber suit;
    sf::RectangleShape frame;
    float textSize;

public:
    card(std::string _name, suitNumber _suit, sf::Font& font, sf::Texture& texture, float _width, float _height, float _x, float _y, sf::Color color)
        : suit(_suit)
    {
        frame.setSize(sf::Vector2f(_width + 20, _height + 20));
        frame.setOrigin(sf::Vector2f((_width + 20) / 2, (_height + 20) / 2));
        frame.setPosition(sf::Vector2f(_x, _y));
        frame.setFillColor(sf::Color::Green);

        textSize = 32;

        for (int i = 0; i < 2; i++)
        {
            name[i].setCharacterSize(int(textSize));
            name[i].setFont(font);
            if (_suit == suitNumber::diamonds || _suit == suitNumber::hearts)
                name[i].setFillColor(sf::Color::Color(139, 0, 0));
            else  name[i].setFillColor(sf::Color::Black);
            name[i].setString(_name);

            sprite[i].setTexture(texture);
            sprite[i].scale(0.4f, 0.4f);
            sprite[i].setTextureRect(sf::IntRect(64 * int(_suit), 0, 64, 64));
        }
        name[0].setPosition(_x - _width / 2 + 3, _y - _height / 2);
        name[1].setPosition(_x + _width / 2 - 3, _y + _height / 2);
        name[1].setRotation(180);

        sprite[0].setPosition(_x - _width / 2, _y - _height / 2 + textSize);
        sprite[1].setPosition(_x + _width / 2, _y + _height / 2 - textSize);
        sprite[1].setRotation(180);
    }
    ~card();
    suitNumber getSuit();
    void setPosition(sf::Vector2f position);
    void frameSetFillColor(sf::Color color);
    virtual bool ableToPlay(card* current, bool addDraw, bool second = false);
    void uptade(sf::Vector2f mousePos);
    virtual void draw(sf::RenderWindow& window);
};

