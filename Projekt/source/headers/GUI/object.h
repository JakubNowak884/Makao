#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <thread>

class Object
{
	sf::RectangleShape shape;	/*!< Kszta³t obiektu na ekranie, mo¿e zostaæ na³o¿ona na niego tekstura. */
	float x;					/*!< Pozycja obiektu na osi X ekranu. */
	float y;					/*!< Pozycja obiektu na osi Y ekranu. */
	float width;				/*!< Szerokoœæ obiektu. */
	float height;				/*!< Wysokoœæ obiektu. */
	bool chosen;				/*!< Informacje czy u¿ytkownik aktulnie ma kursor myszki na obiekcie. */

public:
	Object();
	/**
	  * \brief Konstruktor wieloargumentowy.
	  * \param _width szerokoœæ obiektu.
	  * \param _height wysokoœæ obiektu
	  * \param _x obiektu na osi X ekranu
	  * \param _y obiektu na osi Y ekranu
	  * \param texture tekstura obiektu.
	  * \param color kolor obiektu.
	  */
	Object(float _width, float _height, float _x, float _y, sf::Texture* texture, sf::Color color = sf::Color::Black);

	float getX();
	float getY();
	float getWidth();
	float getHeight();
	/**
	  * \brief Funkcja sprawdzaj¹ca czy u¿ytkownik aktulnie celuje kursorem na obiekt.
	  * \return true jeœli u¿ytkownik aktualnie wskazuje kursorem na obiekt, inaczej false.
	  */
	bool isChosen();
	sf::RectangleShape& getShape();

	void setChosen(bool newChosen);
	virtual void setPosition(sf::Vector2f position);
	void setShapeColor(sf::Color color);
	/**
	   * \brief Funkcja aktualizuj¹ca stan obiektu na ekranie.
	   * \param mousePos pozycja myszy na ekranie.
	   */
	virtual void uptade(sf::Vector2f mousePos);
	/**
	   * \brief Funkcja rysuj¹ca obiekt na ekranie.
	   * \param window okno gry.
	   */
	virtual void draw(sf::RenderWindow& window);
};

