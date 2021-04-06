#pragma once

#include <vector>

#include "object.h"



enum class suitNumber { null = 0, clubs = 1, diamonds = 2, hearts = 3, spades = 4 };
enum class figureNumber { null = 0, ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13 };

class card :
    public object
{
    sf::Text name[2];
    sf::Sprite spriteSuit[2];
    suitNumber suit;
    figureNumber figure;
    sf::RectangleShape frame;
    float textSize;

public:
    card(figureNumber _figure, suitNumber _suit, sf::Font& font, sf::Texture& textureSuit, float _width, float _height, float _x, float _y, sf::Color color)
        : figure(_figure), suit(_suit), object(_width, _height, _x, _y, sf::Color::White)
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
            std::string toText;
            switch (int(_figure)) 
            { 
            case 1: toText = 'A'; break; 
            case 10: toText = "10"; break; 
            case 11: toText = 'J'; break; 
            case 12: toText = 'Q'; break; 
            case 13: toText = 'K'; break; 
            default: toText = std::to_string(int(_figure)); break;
            }
            name[i].setString(toText);

            spriteSuit[i].setTexture(textureSuit);
            spriteSuit[i].scale(0.4f, 0.4f);
            spriteSuit[i].setTextureRect(sf::IntRect(64 * (int(_suit) - 1), 0, 64, 64));
        }
        name[0].setPosition(_x - _width / 2 + 3, _y - _height / 2);
        name[1].setPosition(_x + _width / 2 - 3, _y + _height / 2);
        name[1].setRotation(180);

        spriteSuit[0].setPosition(_x - _width / 2, _y - _height / 2 + textSize);
        spriteSuit[1].setPosition(_x + _width / 2, _y + _height / 2 - textSize);
        spriteSuit[1].setRotation(180);
    }
    ~card();
    suitNumber getSuit();
    figureNumber getFigure();
    void setPosition(sf::Vector2f position) override;
    void frameSetFillColor(sf::Color color);
    bool ableToPlay(card* current, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, bool second = false);
    void uptade(sf::Vector2f mousePos) override;
    void draw(sf::RenderWindow& window) override;
};

