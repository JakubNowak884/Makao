#include "headers\button.h"

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
		setShapeColor(sf::Color::Color(0, 128, 0));
	else
		setShapeColor(sf::Color::Color(0, 0, 0));

	object::draw(window);
	window.draw(text);
}
