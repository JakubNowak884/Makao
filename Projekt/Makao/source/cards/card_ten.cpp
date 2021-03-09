#include "..\headers\cards\card_ten.h"
#include "..\headers\cards\card_two.h"
#include "..\headers\cards\card_three.h"

card_ten::~card_ten()
{
}

bool card_ten::ableToPlay(card* current, bool addDraw, bool second)
{
	if ((typeid(*current).name() == typeid(card_two).name() || typeid(*current).name() == typeid(card_three).name()) && addDraw == true)
	{
		frameSetFillColor(sf::Color::Red);
		return false;
	}
	else
		return card::ableToPlay(current, addDraw, second);
}

void card_ten::draw(sf::RenderWindow& window)
{
	card::draw(window);
}
