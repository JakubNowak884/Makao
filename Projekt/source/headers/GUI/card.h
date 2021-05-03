#pragma once

#include <vector>

#include "Object.h"



enum class suitNumber { null = 0, clubs = 1, diamonds = 2, hearts = 3, spades = 4 };
enum class figureNumber { null = 0, ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13 };

class Card :
    public Object
{
    suitNumber suit;
    figureNumber figure;
    sf::RectangleShape frame;
    float textSize;

public:
    Card(figureNumber _figure, suitNumber _suit, sf::Font& font, sf::Texture* textureSuit, float _width, float _height, float _x, float _y, sf::Color color)
        : figure(_figure), suit(_suit), Object(_width, _height, _x, _y, textureSuit, sf::Color::White)
    {
        getShape().setTextureRect(sf::IntRect((int(_figure) - 1) * 148, (int(_suit) - 1) * 230, 145, 230));

        frame.setSize(sf::Vector2f(_width + 20, _height + 20));
        frame.setOrigin(sf::Vector2f((_width + 20) / 2, (_height + 20) / 2));
        frame.setPosition(sf::Vector2f(_x, _y));
        frame.setFillColor(sf::Color::Green);
        textSize = 32;
    }
    ~Card();
    suitNumber getSuit();
    figureNumber getFigure();
    void setPosition(sf::Vector2f position) override;
    void frameSetFillColor(sf::Color color);
    bool ableToPlay(Card* current, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, bool second = false);
    void uptade(sf::Vector2f mousePos) override;
    void draw(sf::RenderWindow& window) override;
};

