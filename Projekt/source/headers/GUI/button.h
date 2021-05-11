#pragma once
#include "Object.h"

class Button :
    public Object
{
    sf::Text text;  /*!< Tekst wy�wietlany na przycisku. */

    int textSize;   /*!< Wielko�� tekstu wy�wietlanego na przycisku. */

    /**
       * \brief Funkcja zlicza liczb� znak�w ko�ca wiersza w napisie.
       * \param text napis do sprawdzenia.
       * \return liczba znak�w ko�ca wiersza dzielona na dwa.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    float textEndl(const std::string& text);
    /**
       * \brief Funkcja textEndl() przyjmuj�ca wide string. 
       * \see textEndl(const std::string& text)
       */
    float textEndl(const std::wstring& text);

public:
    /**
       * \brief Kostruktor wieloargumentowy.
       * \param textToBeShowed tekst do wy�wietlenia na przycisku.
       * \param font font tekstu.
       * \param _width szeroko�� przycisku.
       * \param _height wysoko�� przycisku.
       * \param _x pozycja przycisku na osi X ekranu.
       * \param _y pozycja przycisku na osi Y ekranu.
       * \param texture tekstura przycisku.
       * \param _textSize wielko�� tekstu na przycisku.
       * \see Object::Object(float _width, float _height, float _x, float _y, sf::Texture* texture, sf::Color color = sf::Color::Black)
       */
    Button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86);
    /**
       * \brief Kostruktor wieloargumentowy przyjmuj�cy wide string.
       * \see  Button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86)
       */
    Button(const std::wstring& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86);
    void setString(std::string _text);
    void setString(std::wstring _text);
    void setPosition(sf::Vector2f position) override;
    /**
       * \brief Funckja sprawdzaj�ca czy przycisk zosta� naci�ni�ty przez u�ytkownika.
       * 
       * Funkcja sprawdza czy zmienna chosen jest r�wna true, a nast�pnie czy u�ytkownik nacisn�� lewy przycisk myszy.
       * \param event rodzaj przycisku naci�ni�tego przez u�ytkownika.
       * \return true je�li u�ytkownik nacisn�� przycisk, false je�li nie nacisn��.
       */
    bool clicked(sf::Event& event);
    /**
       * \brief Funkcja rysuj�ca przycisk na ekranie.
       * \param window okno gry.
       * \see Object::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

