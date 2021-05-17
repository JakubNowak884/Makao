#include "..\headers\GameStates\endgame.h"

Endgame::Endgame(SinglePlayer* prev, std::shared_ptr<Resources> _resources)
	: GameState(_resources)
{
	initText(textResults, 0, 0, 48);
	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::endgame), 3), resources->getFont(), 600.0f, 150.0f, 400.0f, 700.0f, resources->getTexturePtr("button"));

	std::string textToShow = sf::String(resources->getText(int(gameStateNumber::endgame), 1));
	//zapisanie wyników graczy komputerowych
	for (int i = 2; i < prev->getAmountOfPlayers() + 1; i++)
		results[prev->getAI(i)->getWon()] = sf::String(resources->getText(int(gameStateNumber::endgame), 2)) + std::to_string(prev->getAI(i)->getID() - 1);
	//zapisanie wyniku gracza
	results[prev->getWon()] = sf::String(getPlayerName());
	//przepisanie wyników do std::string
	for (int i = 1; i < prev->getAmountOfPlayers() + 1; i++)
		textToShow = textToShow + std::to_string(i) + ". " + results[i] + "\n";

	textResults.setString(textToShow);
}

Endgame::Endgame(MultiPlayer* prev, std::shared_ptr<Resources> _resources)
	: GameState(_resources)
{
	initText(textResults, 0, 0, 48);
	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::endgame), 3), resources->getFont(), 600, 100, 400, 700, resources->getTexturePtr("button"));
	//wyniki gry w wielu graczy otrzymane s¹ z poprzedniego stanu gry
	textResults.setString(resources->getText(int(gameStateNumber::endgame), 1) + sf::String(prev->getPodium()));
}

gameStateNumber Endgame::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_menu->clicked(event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		return gameStateNumber::menu;
	}

	b_menu->uptade(getMousePos(window));

	return gameStateNumber::def;
}

void Endgame::draw(sf::RenderWindow& window)
{
	window.draw(textResults);
	b_menu->draw(window);
}
