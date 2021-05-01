#include "..\headers\GameStates\endgame.h"

endgame::endgame(singlePlayer* prev, Resources* _resources)
	: gameState(_resources)
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	text.setFont(resources->getFont());
	text.setCharacterSize(48);
	text.setPosition(0, 0);
	std::string first = "Koniec gry!\nWyniki:\n";
	for (int i = 2; i < prev->getAmountOfPlayers() + 1; i++)
		results[prev->getAI(i)->getWon()] = "Komputer " + std::to_string(prev->getAI(i)->getID() - 1);
	std::cout << prev->getWon() << std::endl;
	results[prev->getWon()] = getPlayerName();

	for (int i = 1; i < prev->getAmountOfPlayers() + 1; i++)
		first = first + std::to_string(i) + ". " + results[i] + "\n";

	text.setString(first);

	b_menu = std::make_unique<button>(L"Wroc do menu", resources->getFont(), 600, 100, 400, 700, resources->getTexturePtr("button"));
}

endgame::endgame(multiPlayer* prev, Resources* _resources)
	: gameState(_resources)
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	text.setFont(resources->getFont());
	text.setCharacterSize(48);
	text.setPosition(0, 0);

	text.setString("Koniec gry!\nWyniki:\n" + prev->getPodium());

	b_menu = std::make_unique<button>(L"Wroc do menu", resources->getFont(), 600, 100, 400, 700, resources->getTexturePtr("button"));
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
