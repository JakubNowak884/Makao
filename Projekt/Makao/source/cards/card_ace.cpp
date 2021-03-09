#include "..\headers\cards\card_ace.h"
#include "..\headers\cards\card_two.h"
#include "..\headers\cards\card_three.h"

card_ace::~card_ace()
{
}

bool card_ace::ableToPlay(card* current, bool addDraw, bool second)
{
	if ((typeid(*current).name() == typeid(card_two).name() || typeid(*current).name() == typeid(card_three).name()) && addDraw == true)
	{
		frameSetFillColor(sf::Color::Red);
		return false;
	}
	else
		return card::ableToPlay(current, addDraw, second);
}

void card_ace::draw(sf::RenderWindow& window)
{
	card::draw(window);
}
