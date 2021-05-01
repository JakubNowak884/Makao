#include "..\headers\GUI\button.h"

float button::textEndl(const std::string& text)
{
	float res = 0;

	for (auto i = text.begin(); i < text.end(); i++)
	{
		if ((*i) == '\n')
			res += 0.5;
	}

	return res;
}

float button::textEndl(const std::wstring& text)
{
	float res = 0;

	for (auto i = text.begin(); i < text.end(); i++)
	{
		if ((*i) == '\n')
			res += 0.5;
	}

	return res;
}

button::button(const std::string& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize)
	: object(_width, _height, _x, _y, texture), textSize(_textSize)
{
	text.setFont(font);
	text.setString(textToBeShowed);
	text.setCharacterSize(int(textSize));
	text.setOrigin(text.getLocalBounds().width / 2, (textSize * 3 / 4) + textSize * textEndl(textToBeShowed));
	text.setPosition(_x, _y);
}

button::button(const std::wstring& textToBeShowed, sf::Font& font, float _width, float _height, float _x, float _y, sf::Texture* texture, int _textSize)
	: object(_width, _height, _x, _y, texture), textSize(_textSize)
{
	text.setFont(font);
	text.setString(textToBeShowed);
	text.setCharacterSize(int(textSize));
	text.setOrigin(text.getLocalBounds().width / 2, (textSize * 3 / 4) + textSize * textEndl(textToBeShowed));
	text.setPosition(_x, _y);
}

void button::setString(std::string _text)
{
	text.setString(_text);
	text.setOrigin(text.getLocalBounds().width / 2, (textSize * 3 / 4) + textSize * textEndl(_text));
}

void button::setString(std::wstring _text)
{
	text.setString(_text);
	text.setOrigin(text.getLocalBounds().width / 2, (textSize * 3 / 4) + textSize * textEndl(_text));
}

void button::setPosition(sf::Vector2f position)
{
	object::setPosition(position);
	text.setPosition(position);
}

bool button::clicked(sf::Event& event)
{
	if (isChosen() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		return true;
	else
		return false;
}

void button::draw(sf::RenderWindow& window)
{
	if (isChosen() == true)
		getShape().setTextureRect(sf::IntRect(641, 0, 640, 211));
	else
		getShape().setTextureRect(sf::IntRect(0, 0, 640, 211));

	object::draw(window);
	window.draw(text);
}
