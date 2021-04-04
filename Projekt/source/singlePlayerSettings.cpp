#include "headers\singlePlayerSettings.h"

singlePlayerSettings::singlePlayerSettings()
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	settings.setCharacterSize(86);
	settings.setFillColor(sf::Color::White);
	settings.setFont(font);
	settings.setPosition(0, 0);
	settings.setString("Wybierz ilosc graczy\n komputerowych:");

	b_2 = std::make_unique<button>("2", font, 100, 100, 200, 400);
	b_3 = std::make_unique<button>("3", font, 100, 100, 400, 400);
	b_4 = std::make_unique<button>("4", font, 100, 100, 600, 400);
	b_toMenu = std::make_unique<button>("Wroc do menu", font, 600, 150, 400, 600);
}

singlePlayerSettings::~singlePlayerSettings()
{
}

gameStateNumber singlePlayerSettings::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_2->clicked(event))
	{
		setAmountOfPlayers(2);
		return gameStateNumber::singlePlayer;
	}
	if (b_3->clicked(event));
	if (b_4->clicked(event));
	if (b_toMenu->clicked(event))
	{
		return gameStateNumber::menu;
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		return gameStateNumber::menu;

	b_2->uptade(getMousePos(window));
	b_3->uptade(getMousePos(window));
	b_4->uptade(getMousePos(window));
	b_toMenu->uptade(getMousePos(window));

	return gameStateNumber::def;
}

void singlePlayerSettings::draw(sf::RenderWindow& window)
{
	window.draw(settings);
	b_2->draw(window);
	b_3->draw(window);
	b_4->draw(window);
	b_toMenu->draw(window);
}
