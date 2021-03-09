#include "..\headers\cards\card_nine.h"
#include "..\headers\cards\card_two.h"
#include "..\headers\cards\card_three.h"

card_nine::~card_nine()
{
}

bool card_nine::ableToPlay(card* current, bool addDraw, bool second)
{
	if ((typeid(*current).name() == typeid(card_two).name() || typeid(*current).name() == typeid(card_three).name()) && addDraw == true)
	{
		frameSetFillColor(sf::Color::Red);
		return false;
	}
	else
		return card::ableToPlay(current, addDraw, second);
}

void card_nine::draw(sf::RenderWindow& window)
{
	card::draw(window);
}
