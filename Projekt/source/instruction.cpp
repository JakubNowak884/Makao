#include "headers/instruction.h"

instruction::instruction()
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	rules.setCharacterSize(36);
	rules.setFillColor(sf::Color::White);
	rules.setFont(font);
	rules.setPosition(0, 0);
	rules.setString("Zasady:");

	controls.setCharacterSize(36);
	controls.setFillColor(sf::Color::White);
	controls.setFont(font);
	controls.setPosition(0, 0);
	controls.setString("Sterowanie:");

	credits.setCharacterSize(24);
	credits.setFillColor(sf::Color::White);
	credits.setFont(font);
	credits.setPosition(0, 0);
	credits.setString("Autor:\n	Jakub Nowak\n\nPodziekowania:\n	Tekstura tla: Image by Danny Santamaria Osorio from Pixabay\n	Tekstura przycisku: Image by 1117826 from Pixabay\n	Tekstura kart: Image by OpenClipart - Vectors from Pixabay\n	Wszystkie tesktury zostaly oparte na licencji Pixabay License.");

	page1.setCharacterSize(18);
	page1.setFillColor(sf::Color::White);
	page1.setFont(font);
	page1.setPosition(15, 660);
	page1.setString("Strona " + std::to_string(page) + "/3");

	page2.setCharacterSize(18);
	page2.setFillColor(sf::Color::White);
	page2.setFont(font);
	page2.setPosition(700, 660);
	page2.setString("Strona " + std::to_string(page) + "/3");

	b_pageDown = std::make_unique<button>("<", font, 100, 100, 60, 740);
	b_pageUp = std::make_unique<button>(">", font, 100, 100, 740, 740);
	b_menu = std::make_unique<button>("Wroc do menu", font, 500, 100, 400, 740, 64);
}

void instruction::pageDown()
{
	page--;
	if (page == 0)
		page = 3;
}

void instruction::pageUp()
{
	page++;
	if (page == 4)
		page = 1;
}

gameStateNumber instruction::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_pageDown->clicked(event))
	{
		pageDown();
	}
	if (b_pageUp->clicked(event))
	{
		pageUp();
	}
	if (b_menu->clicked(event))
	{
		return gameStateNumber::menu;
	}

	b_pageDown->uptade(getMousePos(window));
	b_pageUp->uptade(getMousePos(window));
	b_menu->uptade(getMousePos(window));

	return gameStateNumber::def;
}

void instruction::draw(sf::RenderWindow& window)
{
	switch (page)
	{
	case 1:
		window.draw(rules);
		break;
	case 2:
		window.draw(controls);
		break;
	case 3:
		window.draw(credits);
		break;
	default:
		break;
	}
	page1.setString("Strona " + std::to_string(page) + "/3");
	page2.setString("Strona " + std::to_string(page) + "/3");
	window.draw(page1);
	window.draw(page2);

	b_pageDown->draw(window);
	b_pageUp->draw(window);
	b_menu->draw(window);
}
