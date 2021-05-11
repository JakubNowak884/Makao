#include "..\headers\GameStates\instruction.h"
#include "..\headers\Resources.h"

Instruction::Instruction(std::shared_ptr<Resources> _resources)
	: GameState (_resources)
{
	initText(rules, 0, 0, 24);
	rules.setString(resources->getText(int(gameStateNumber::instruction), 1));

	initText(controls, 0, 0, 32);
	controls.setString(resources->getText(int(gameStateNumber::instruction), 2));

	initText(credits, 0, 0, 24);
	credits.setString(resources->getText(int(gameStateNumber::instruction), 3));

	initText(page1, 15, 660, 18);
	initText(page2, 700, 660, 18);

	b_pageDown = std::make_unique<Button>("<", resources->getFont(), 100, 100, 60, 740, resources->getTexturePtr("button"));
	b_pageUp = std::make_unique<Button>(">", resources->getFont(), 100, 100, 740, 740, resources->getTexturePtr("button"));
	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::instruction), 5), resources->getFont(), 500, 100, 400, 740, resources->getTexturePtr("button"), 64);
}

void Instruction::pageDown()
{
	page--;
	if (page == 0)
		page = 3;
}

void Instruction::pageUp()
{
	page++;
	if (page == 4)
		page = 1;
}

gameStateNumber Instruction::update(sf::Event event, sf::RenderWindow& window)
{
	if (b_pageDown->clicked(event))
	{
		pageDown();
	}
	if (b_pageUp->clicked(event))
	{
		pageUp();
	}
	if (b_menu->clicked(event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		return gameStateNumber::menu;
	}

	b_pageDown->uptade(getMousePos(window));
	b_pageUp->uptade(getMousePos(window));
	b_menu->uptade(getMousePos(window));

	return gameStateNumber::def;
}

void Instruction::draw(sf::RenderWindow& window)
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

	page1.setString(resources->getText(int(gameStateNumber::instruction), 4) + std::to_wstring(page) + L"/3");
	page2.setString(resources->getText(int(gameStateNumber::instruction), 4) + std::to_wstring(page) + L"/3");
	window.draw(page1);
	window.draw(page2);

	b_pageDown->draw(window);
	b_pageUp->draw(window);
	b_menu->draw(window);
}
