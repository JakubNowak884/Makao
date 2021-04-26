#include "headers\singlePlayerSettings.h"

singlePlayerSettings::singlePlayerSettings()
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	settings.setCharacterSize(42);
	settings.setFillColor(sf::Color::White);
	settings.setFont(font);
	settings.setPosition(0, 0);
	settings.setString("Ilosc graczy: " + std::to_string(amountOfPlayers) + "\n\n" +
	"Odstep miedzy turami graczy komputerowych: " + std::to_string(botSpeed) + " ms\n\n" +
	"Same krolowe: ");

	b_addAmountOfPlayers = std::make_unique<button>("+", font, 50, 50, 95, 90, 58);
	b_reduceAmountOfPlayers = std::make_unique<button>("-", font, 50, 50, 35, 90, 58);
	b_addBotSpeed = std::make_unique<button>("+", font, 50, 50, 95, 260, 58);
	b_reduceBotSpeed = std::make_unique<button>("-", font, 50, 50, 35, 260, 58);
	b_onlyQueens = std::make_unique<button>("Wylaczone", font, 200, 50, 400, 315, 38);
	b_start = std::make_unique<button>("Start", font, 600, 150, 400, 500);
	b_toMenu = std::make_unique<button>("Wroc do menu", font, 600, 150, 400, 675);
}

int singlePlayerSettings::getAmountOfPlayers()
{
	return amountOfPlayers;
}

bool singlePlayerSettings::getOnlyQueens()
{
	return onlyQueens;
}

gameStateNumber singlePlayerSettings::update(sf::Event event, sf::RenderWindow& window)
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
		botSpeed += 10;
	}
	if (b_reduceBotSpeed->clicked(event))
	{
		botSpeed -= 10;
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
	b_reduceBotSpeed->uptade(getMousePos(window));
	b_onlyQueens->uptade(getMousePos(window));
	b_start->uptade(getMousePos(window));
	b_toMenu->uptade(getMousePos(window));

	return gameStateNumber::def;
}

void singlePlayerSettings::draw(sf::RenderWindow& window)
{
	settings.setString("Ilosc graczy: " + std::to_string(amountOfPlayers) + "\n\n" +
		"Odstep miedzy turami\ngraczy komputerowych: " + std::to_string(botSpeed) + " ms\n\n" +
		"Same krolowe: ");
	window.draw(settings);
	b_addAmountOfPlayers->draw(window);
	b_reduceAmountOfPlayers->draw(window);
	b_addBotSpeed->draw(window);
	b_reduceBotSpeed->draw(window);
	if (onlyQueens)
		b_onlyQueens->setString("Wlaczone");
	else
		b_onlyQueens->setString("Wylaczone");
	b_onlyQueens->draw(window);
	b_start->draw(window);
	b_toMenu->draw(window);
}
