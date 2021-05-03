#include "..\headers\GUI\button.h"

float Button::textEndl(const std::string& text)
{
	float res = 0;

	for (auto i = text.begin(); i < text.end(); i++)
	{
		if ((*i) == '\n')
			res += 0.5;
	}

	return res;
}

float Button::textEndl(const std::wstring& text)
{
	float res = 0;

	for (auto i = text.begin(); i < text.end(); i++)
	{
		if ((*i) == '\n')
			res += 0.5;
	}

	return res;
}

Button::Button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize)
	: Object(_width, _height, _x, _y, texture), textSize(_textSize)
{
	text.setFont(font);
	text.setString(textToBeShowed);
	text.setCharacterSize(int(textSize));
	text.setOrigin(text.getLocalBounds().width / 2, (float(textSize) * 3 / 4) + textSize * textEndl(textToBeShowed));
	text.setPosition(_x, _y);
}

Button::Button(const std::wstring& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize)
	: Object(_width, _height, _x, _y, texture), textSize(_textSize)
{
	text.setFont(font);
	text.setString(textToBeShowed);
	text.setCharacterSize(textSize);
	text.setOrigin(text.getLocalBounds().width / 2, (float(textSize) * 3 / 4) + textSize * textEndl(textToBeShowed));
	text.setPosition(_x, _y);
}

void Button::setString(std::string _text)
{
	text.setString(_text);
	text.setOrigin(text.getLocalBounds().width / 2, (float(textSize) * 3 / 4) + textSize * textEndl(_text));
}

void Button::setString(std::wstring _text)
{
	text.setString(_text);
	text.setOrigin(text.getLocalBounds().width / 2, (float(textSize) * 3 / 4) + textSize * textEndl(_text));
}

void Button::setPosition(sf::Vector2f position)
{
	Object::setPosition(position);
	text.setPosition(position);
}

bool Button::clicked(sf::Event& event)
{
	if (isChosen() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		return true;
	else
		return false;
}

void Button::draw(sf::RenderWindow& window)
{
	if (isChosen() == true)
		getShape().setTextureRect(sf::IntRect(641, 0, 640, 211));
	else
		getShape().setTextureRect(sf::IntRect(0, 0, 640, 211));

	Object::draw(window);
	window.draw(text);
}
