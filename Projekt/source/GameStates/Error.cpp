#include "..\headers\GameStates\Error.h"
#include "..\headers\Resources.h"

Error::Error(std::wstring error, Resources* _resources)
	: GameState(_resources)
{
	initText(text, 0, 0, 36);
	text.setString(error);

	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 6), resources->getFont(), 600, 150, 400, 700, resources->getTexturePtr("button"));
}

gameStateNumber Error::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_menu->clicked(event))
	{
		return gameStateNumber::menu;
	}

	b_menu->uptade(getMousePos(window));

	return gameStateNumber::def;
}

void Error::draw(sf::RenderWindow& window)
{
	window.draw(text);
	b_menu->draw(window);
}
