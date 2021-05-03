#include "..\headers\GameStates\endgame.h"
#include "..\headers\Resources.h"

Endgame::Endgame(SinglePlayer* prev, Resources* _resources)
	: GameState(_resources)
{
	initText(text, 0, 0, 48);

	std::string first = sf::String(resources->getText(int(gameStateNumber::endgame), 1));
	for (int i = 2; i < prev->getAmountOfPlayers() + 1; i++)
		results[prev->getAI(i)->getWon()] = sf::String(resources->getText(int(gameStateNumber::endgame), 2)) + std::to_string(prev->getAI(i)->getID() - 1);
	std::cout << prev->getWon() << std::endl;
	results[prev->getWon()] = sf::String(getPlayerName());

	for (int i = 1; i < prev->getAmountOfPlayers() + 1; i++)
		first = first + std::to_string(i) + ". " + results[i] + "\n";

	text.setString(first);

	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::endgame), 3), resources->getFont(), 600, 100, 400, 700, resources->getTexturePtr("button"));
}

Endgame::Endgame(MultiPlayer* prev, Resources* _resources)
	: GameState(_resources)
{
	initText(text, 0, 0, 48);
	text.setString(resources->getText(int(gameStateNumber::endgame), 1) + sf::String(prev->getPodium()));

	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::endgame), 3), resources->getFont(), 600, 100, 400, 700, resources->getTexturePtr("button"));
}

gameStateNumber Endgame::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_menu->clicked(event))
		return gameStateNumber::menu;

	b_menu->uptade(getMousePos(window));
	return gameStateNumber::def;
}

void Endgame::draw(sf::RenderWindow& window)
{
	window.draw(text);
	b_menu->draw(window);
}
