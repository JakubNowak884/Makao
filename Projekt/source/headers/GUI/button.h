#pragma once
#include "Object.h"

class Button :
    public Object
{
    sf::Text text;  /*!< Tekst wyœwietlany na przycisku. */

    int textSize;   /*!< Wielkoœæ tekstu wyœwietlanego na przycisku. */

    /**
       * \brief Funkcja zlicza liczbê znaków koñca wiersza w napisie.
       * \param text napis do sprawdzenia.
       * \return liczba znaków koñca wiersza dzielona na dwa.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    float textEndl(const std::string& text);
    /**
       * \brief Funkcja textEndl() przyjmuj¹ca wide string. 
       * \see textEndl(const std::string& text)
       */
    float textEndl(const std::wstring& text);

public:
    /**
       * \brief Kostruktor wieloargumentowy.
       * \param textToBeShowed tekst do wyœwietlenia na przycisku.
       * \param font font tekstu.
       * \param _width szerokoœæ przycisku.
       * \param _height wysokoœæ przycisku.
       * \param _x pozycja przycisku na osi X ekranu.
       * \param _y pozycja przycisku na osi Y ekranu.
       * \param texture tekstura przycisku.
       * \param _textSize wielkoœæ tekstu na przycisku.
       * \see Object::Object(float _width, float _height, float _x, float _y, sf::Texture* texture, sf::Color color = sf::Color::Black)
       */
    Button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86);
    /**
       * \brief Kostruktor wieloargumentowy przyjmuj¹cy wide string.
       * \see  Button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86)
       */
    Button(const std::wstring& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize = 86);
    void setString(std::string _text);
    void setString(std::wstring _text);
    void setPosition(sf::Vector2f position) override;
    /**
       * \brief Funckja sprawdzaj¹ca czy przycisk zosta³ naciœniêty przez u¿ytkownika.
       * 
       * Funkcja sprawdza czy zmienna chosen jest równa true, a nastêpnie czy u¿ytkownik nacisn¹³ lewy przycisk myszy.
       * \param event rodzaj przycisku naciœniêtego przez u¿ytkownika.
       * \return true jeœli u¿ytkownik nacisn¹³ przycisk, false jeœli nie nacisn¹³.
       */
    bool clicked(sf::Event& event);
    /**
       * \brief Funkcja rysuj¹ca przycisk na ekranie.
       * \param window okno gry.
       * \see Object::draw(sf::RenderWindow& window)
       */
    void draw(sf::RenderWindow& window) override;
};

