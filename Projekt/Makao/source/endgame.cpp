#include "headers\endgame.h"

endgame::endgame(gameState* prev)
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	text.setFont(font);
	text.setCharacterSize(48);
	text.setPosition(0, 0);
	std::string first = "Koniec gry!\nWyniki:\n";
	results[prev->getAI(0)->getWon()] = typeid(*prev->getAI(0)).name();
	results[prev->getWon()] = typeid(*prev).name();

	std::string second;
	for (int i = 1; i <= getAmountOfPlayers(); i++)
	{
		second = std::to_string(i) + ". ";
		second = second + results[i].erase(0, 6) + "\n";
		first = first + second;
	}
	text.setString(first);

	b_menu = std::make_unique<button>("Wroc do menu", font, 600, 100, 400, 700);
}

endgame::~endgame()
{
}

gameStateNumber endgame::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_menu->clicked(event))
		return gameStateNumber::menu;

	b_menu->uptade(getMousePos(window));
	return gameStateNumber::def;
}

void endgame::draw(sf::RenderWindow& window)
{
	window.draw(text);
	b_menu->draw(window);
}
