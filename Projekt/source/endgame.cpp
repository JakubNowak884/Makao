#include "headers\endgame.h"

endgame::endgame(gameState* prev)
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	text.setFont(font);
	text.setCharacterSize(48);
	text.setPosition(0, 0);
	std::string first = "Koniec gry!\nWyniki:\n";
	for (int i = 2; i < prev->getAmountOfPlayers() + 1; i++)
		results[prev->getAI(i)->getWon()] = "Komputer " + std::to_string(prev->getAI(i)->getID() - 1);
	results[prev->getWon()] = getPlayerName();

	for (int i = 1; i < prev->getAmountOfPlayers() + 1; i++)
		first = first + std::to_string(i) + ". " + results[i] + "\n";

	text.setString(first);

	b_menu = std::make_unique<button>("Wroc do menu", font, 600, 100, 400, 700);
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
