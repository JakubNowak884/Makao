#include "..\headers\GameStates\instruction.h"

instruction::instruction(Resources* _resources)
	: gameState (_resources)
{
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	rules.setCharacterSize(24);
	rules.setFillColor(sf::Color::White);
	rules.setFont(resources->getFont());
	rules.setPosition(0, 0);
	rules.setString(L"Zasady:\n\nNa poczatku gry kazdy z graczy dostaje do reki 5 kart z talli 52 kart.\nPierwsza karta z talli polozona jest na srodku stolu.\nCelem gry jest pozbycie sie wszystkich kart z reki poprzez zagrywanie\nich na karte na stole, jesli obie maja pasujacy kolor lub figure.\n\nPoszczegolne karty maja nastepujace efekty:\nAs: Gracz zada koloru dla nastepnego gracza\nDwojki/trojki: Nastepny gracz dobiera dwie/trzy karty\nCzworki: Nastepny gracz czeka 1 kolejke\nWalety: Gracz zada figury dla calej kolejki\nKrolowe: Krolowa mozna zagrac na dowolna karte niefunkcyjna,\n                na krolowa mozna zagrac dowolna karte\nKrol Serce/Pik: Nastepny/poprzedni gracz dobiera 5 kart\n\nPrzed kartami funkcyjnymi mozna obronic sie tylko zagrywajac karte o\ntej samej funkcji.");

	controls.setCharacterSize(32);
	controls.setFillColor(sf::Color::White);
	controls.setFont(resources->getFont());
	controls.setPosition(0, 0);
	controls.setString(L"Sterowanie:\n\nLewy przycisk myszy:\nZagranie karty/nacisniecie przycisku\n\nStrzalki w lewo/prawo lub kolko myszy w dol/gore:\nPrzesuwanie kart w rece w lewo/prawo\n\nEscape:\nWyjscie do menu");

	credits.setCharacterSize(24);
	credits.setFillColor(sf::Color::White);
	credits.setFont(resources->getFont());
	credits.setPosition(0, 0);
	credits.setString(L"Autor:\n	Jakub Nowak\n\nPodziekowania:\n	Tekstura tla: Image by Danny Santamaria Osorio from Pixabay\n	Tekstura przycisku: Image by 1117826 from Pixabay\n	Tekstura kart: Image by OpenClipart - Vectors from Pixabay\n	Wszystkie tesktury zostaly oparte na licencji Pixabay License.");

	page1.setCharacterSize(18);
	page1.setFillColor(sf::Color::White);
	page1.setFont(resources->getFont());
	page1.setPosition(15, 660);
	page1.setString("Strona " + std::to_string(page) + "/3");

	page2.setCharacterSize(18);
	page2.setFillColor(sf::Color::White);
	page2.setFont(resources->getFont());
	page2.setPosition(700, 660);
	page2.setString("Strona " + std::to_string(page) + "/3");

	b_pageDown = std::make_unique<button>("<", resources->getFont(), 100, 100, 60, 740, resources->getTexturePtr("button"));
	b_pageUp = std::make_unique<button>(">", resources->getFont(), 100, 100, 740, 740, resources->getTexturePtr("button"));
	b_menu = std::make_unique<button>("Wroc do menu", resources->getFont(), 500, 100, 400, 740, resources->getTexturePtr("button"), 64);
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
	if (b_menu->clicked(event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
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
