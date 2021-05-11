#pragma once

#include "Object.h"
/**
     * Typ wyliczeniowy oznaczaj¹cy kolor danej karty(wartoœæ null = 0 jest u¿ywana do zaznaczenia braku ¿¹dania podczas gry).
     */
enum class suitNumber { null = 0, clubs = 1, diamonds = 2, hearts = 3, spades = 4 };
/**
     * Typ wyliczeniowy oznaczaj¹cy figurê danej karty(wartoœæ null = 0 jest u¿ywana do zaznaczenia braku ¿¹dania podczas gry).
     */
enum class figureNumber { null = 0, ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13 };

class Card :
    public Object
{
    suitNumber suit;            /*!< Kolor karty. */
    figureNumber figure;        /*!< Figura karty. */
    sf::RectangleShape frame;   /*!< Ramka do oko³a karty, wyœwietlana po najechaniu na kartê przez u¿ytkownika. */

public:
    /**
     * \brief Kostruktor wieloargumentowy.
     * \param _figure figura karty.
     * \param _suit kolor karty.
     * \param texture tekstura karty.
     * \param _width szerokoœæ karty.
     * \param _height wysokoœæ karty.
     * \param _x pozycja karty na osi X ekranu.
     * \param _y pozycja karty na osi Y ekranu.
     * \see Object::Object(float _width, float _height, float _x, float _y, sf::Texture* texture, sf::Color color = sf::Color::Black)
     */
    Card(figureNumber _figure, suitNumber _suit, sf::Texture* texture, float _width, float _height, float _x, float _y);
    suitNumber getSuit();
    figureNumber getFigure();
    void setPosition(sf::Vector2f position) override;
    void frameSetFillColor(sf::Color color);
    /**
       * \brief Funkcja sprawdzaj¹ca czy dana karta mo¿e zostaæ zagrana.
       * \param current aktualna karta na œrodku sto³u.
       * \param actionCardIsActive informacja czy na grê oddzia³uje aktualnie efekt którejœ z kart.
       * \param currentSuit aktualne ¿¹danie koloru.
       * \param currentFigure aktualne ¿¹danie figury.
       * \param second informacje czy zagrywana jest kolejna w tej kolejce karta przez gracza.
       * \return true jeœli karta mo¿e zostaæ zagrana, false jeœli nie mo¿e.
       */
    bool ableToPlay(Card* current, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, bool second = false);
    /**
       * \brief Funkcja aktualizuj¹ca stan karty na ekranie.
       * \param mousePos pozycja myszy na ekranie.
       * \see Object::uptade(sf::Vector2f mousePos)
       */
    void uptade(sf::Vector2f mousePos) override;
    /**
       * \brief Funkcja rysuj¹ca kartê na ekranie.
       * \param window okno gry.
       * \see Object::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

