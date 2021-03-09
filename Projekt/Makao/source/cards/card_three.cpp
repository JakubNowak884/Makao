#include "..\headers\cards\card_three.h"

card_three::~card_three()
{
}

bool card_three::ableToPlay(card* current, bool addDraw, bool second)
{
	return card::ableToPlay(current, addDraw, second);
}

void card_three::draw(sf::RenderWindow& window)
{
	card::draw(window);
}
