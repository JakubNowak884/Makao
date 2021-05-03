#include "..\headers\GameStates\singlePlayerSettings.h"
#include "..\headers\Resources.h"

SinglePlayerSettings::SinglePlayerSettings(Resources* _resources)
	: GameState(_resources)
{
	initText(settings, 0, 0, 42);
	settings.setString(resources->getText(int(gameStateNumber::singlePlayerSettings), 1) + std::to_wstring(amountOfPlayers) + L"\n\n" +
		resources->getText(int(gameStateNumber::singlePlayerSettings), 2) + std::to_wstring(botSpeed) + L" ms\n\n" +
		resources->getText(int(gameStateNumber::singlePlayerSettings), 3));

	b_addAmountOfPlayers = std::make_unique<Button>("+", resources->getFont(), 50, 50, 720, 35, resources->getTexturePtr("button"), 58);
	b_reduceAmountOfPlayers = std::make_unique<Button>("-", resources->getFont(), 50, 50, 655, 35, resources->getTexturePtr("button"), 58);
	b_addBotSpeed = std::make_unique<Button>("+", resources->getFont(), 50, 50, 720, 175, resources->getTexturePtr("button"), 58);
	b_reduceBotSpeed = std::make_unique<Button>("-", resources->getFont(), 50, 50, 655, 175, resources->getTexturePtr("button"), 58);
	b_onlyQueens = std::make_unique<Button>(resources->getText(int(gameStateNumber::singlePlayerSettings), 7), resources->getFont(), 200, 50, 400, 285, resources->getTexturePtr("button"), 38);
	b_start = std::make_unique<Button>(resources->getText(int(gameStateNumber::singlePlayerSettings), 4), resources->getFont(), 600, 150, 400, 500, resources->getTexturePtr("button"));
	b_toMenu = std::make_unique<Button>(resources->getText(int(gameStateNumber::singlePlayerSettings), 5), resources->getFont(), 600, 150, 400, 675, resources->getTexturePtr("button"));
}

int SinglePlayerSettings::getAmountOfPlayers()
{
	return amountOfPlayers;
}

bool SinglePlayerSettings::getOnlyQueens()
{
	return onlyQueens;
}

int SinglePlayerSettings::getBotSpeed()
{
	return botSpeed;
}

gameStateNumber SinglePlayerSettings::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_addAmountOfPlayers->clicked(event))
	{
		if (amountOfPlayers < 4)
			amountOfPlayers++;
	}
	if (b_reduceAmountOfPlayers->clicked(event))
	{

		if (amountOfPlayers > 2)
			amountOfPlayers--;
	}
	if (b_addBotSpeed->clicked(event))
	{
		botSpeed += 100;
	}
	if (b_reduceBotSpeed->clicked(event))
	{
		botSpeed -= 100;
	}
	if (b_onlyQueens->clicked(event))
	{
		if (onlyQueens)
			onlyQueens = false;
		else
			onlyQueens = true;
	}
	if (b_start->clicked(event))
	{
		return gameStateNumber::singlePlayer;
	}
	if (b_toMenu->clicked(event))
	{
		return gameStateNumber::menu;
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		return gameStateNumber::menu;

	b_addAmountOfPlayers->uptade(getMousePos(window));
	b_reduceAmountOfPlayers->uptade(getMousePos(window));
	b_addBotSpeed->uptade(getMousePos(window));
	b_reduceBotSpeed->setChosen(false);
	if (botSpeed > 0)
		b_reduceBotSpeed->uptade(getMousePos(window));
	b_onlyQueens->uptade(getMousePos(window));
	b_start->uptade(getMousePos(window));
	b_toMenu->uptade(getMousePos(window));

	return gameStateNumber::def;
}

void SinglePlayerSettings::draw(sf::RenderWindow& window)
{
	settings.setString(resources->getText(int(gameStateNumber::singlePlayerSettings), 1) + std::to_wstring(amountOfPlayers) + L"\n\n" +
		resources->getText(int(gameStateNumber::singlePlayerSettings), 2) + std::to_wstring(botSpeed) + L" ms\n\n" +
		resources->getText(int(gameStateNumber::singlePlayerSettings), 3));
	window.draw(settings);
	b_addAmountOfPlayers->draw(window);
	b_reduceAmountOfPlayers->draw(window);
	b_addBotSpeed->draw(window);
	b_reduceBotSpeed->draw(window);
	if (onlyQueens)
		b_onlyQueens->setString(resources->getText(int(gameStateNumber::singlePlayerSettings), 6));
	else
		b_onlyQueens->setString(resources->getText(int(gameStateNumber::singlePlayerSettings), 7));
	b_onlyQueens->draw(window);
	b_start->draw(window);
	b_toMenu->draw(window);
}
