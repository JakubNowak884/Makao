#include "..\headers\cards\card_two.h"

card_two::~card_two()
{
}

bool card_two::ableToPlay(card* current, bool addDraw, bool second)
{
	return card::ableToPlay(current, addDraw, second);
}

void card_two::draw(sf::RenderWindow& window)
{
	card::draw(window);
}
