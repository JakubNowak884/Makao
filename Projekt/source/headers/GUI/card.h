#pragma once

#include "Object.h"
/**
     * Typ wyliczeniowy oznaczaj�cy kolor danej karty(warto�� null = 0 jest u�ywana do zaznaczenia braku ��dania podczas gry).
     */
enum class suitNumber { null = 0, clubs = 1, diamonds = 2, hearts = 3, spades = 4 };
/**
     * Typ wyliczeniowy oznaczaj�cy figur� danej karty(warto�� null = 0 jest u�ywana do zaznaczenia braku ��dania podczas gry).
     */
enum class figureNumber { null = 0, ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13 };

class Card :
    public Object
{
    suitNumber suit;            /*!< Kolor karty. */
    figureNumber figure;        /*!< Figura karty. */
    sf::RectangleShape frame;   /*!< Ramka do oko�a karty, wy�wietlana po najechaniu na kart� przez u�ytkownika. */

public:
    /**
     * \brief Kostruktor wieloargumentowy.
     * \param _figure figura karty.
     * \param _suit kolor karty.
     * \param texture tekstura karty.
     * \param _width szeroko�� karty.
     * \param _height wysoko�� karty.
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
       * \brief Funkcja sprawdzaj�ca czy dana karta mo�e zosta� zagrana.
       * \param current aktualna karta na �rodku sto�u.
       * \param actionCardIsActive informacja czy na gr� oddzia�uje aktualnie efekt kt�rej� z kart.
       * \param currentSuit aktualne ��danie koloru.
       * \param currentFigure aktualne ��danie figury.
       * \param second informacje czy zagrywana jest kolejna w tej kolejce karta przez gracza.
       * \return true je�li karta mo�e zosta� zagrana, false je�li nie mo�e.
       */
    bool ableToPlay(Card* current, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, bool second = false);
    /**
       * \brief Funkcja aktualizuj�ca stan karty na ekranie.
       * \param mousePos pozycja myszy na ekranie.
       * \see Object::uptade(sf::Vector2f mousePos)
       */
    void uptade(sf::Vector2f mousePos) override;
    /**
       * \brief Funkcja rysuj�ca kart� na ekranie.
       * \param window okno gry.
       * \see Object::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

