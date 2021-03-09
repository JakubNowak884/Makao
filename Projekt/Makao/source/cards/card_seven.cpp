#include "..\headers\cards\card_seven.h"
#include "..\headers\cards\card_two.h"
#include "..\headers\cards\card_three.h"

card_seven::~card_seven()
{
}

bool card_seven::ableToPlay(card* current, bool addDraw, bool second)
{
	if ((typeid(*current).name() == typeid(card_two).name() || typeid(*current).name() == typeid(card_three).name()) && addDraw == true)
	{
		frameSetFillColor(sf::Color::Red);
		return false;
	}
	else
		return card::ableToPlay(current, addDraw, second);
}

void card_seven::draw(sf::RenderWindow& window)
{
	card::draw(window);
}
