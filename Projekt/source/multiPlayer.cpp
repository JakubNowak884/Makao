#include "headers/multiPlayer.h"

multiPlayer::multiPlayer(gameState* _prev)
{
	prev = _prev;

	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	text.setCharacterSize(36);
	text.setFillColor(sf::Color::White);
	text.setFont(font);
	text.setPosition(0, 0);
	text.setString("Rodzaj gry: LAN\nIP sesji: ");

	b_addPlayer = std::make_unique<button>(" Dodaj\nmiejsce", font, 300, 200, 600, 300, 56);
	b_menu = std::make_unique<button>("Wroc do menu", font, 600, 150, 400, 700);

	if (prev->getHost())
	{
		text.setString(text.getString() + sf::IpAddress::getLocalAddress().toString() + "\n\n" + "Uczestnicy:\n" "1." + getPlayerName());
		player = std::make_unique<Player>(deck, maxID);
	}
	else
	{
		socket.connect(prev->getIP(), 2000);
	}
}

gameStateNumber multiPlayer::update(sf::Event event, sf::RenderWindow& window)
{
	switch (state)
	{
	case 0:
		if (waiting)
		{
			listener;
			listener.listen(2000);
			listener.accept(socket);
			waiting = false;
		}
		if (b_addPlayer->clicked(event) && maxID < 4)
		{
			maxID++;
			text.setString(text.getString() + '\n' + std::to_string(maxID) + '.');
			waiting = true;
		}
		if (b_menu->clicked(event))
		{
			return gameStateNumber::menu;
		}
		if (prev->getHost())
			b_addPlayer->uptade(getMousePos(window));
		b_menu->uptade(getMousePos(window));
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	return gameStateNumber::def;
}

void multiPlayer::draw(sf::RenderWindow& window)
{
	switch (state)
	{
	case 0:
		window.draw(text);
		b_addPlayer->draw(window);
		b_menu->draw(window);
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}
