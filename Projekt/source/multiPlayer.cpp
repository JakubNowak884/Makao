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

	b_addPlayer = std::make_unique<button>(" Dodaj\nmiejsce", font, 400, 200, 550, 300, 56);
	b_menu = std::make_unique<button>("Wroc do menu", font, 600, 150, 400, 700);

	if (prev->getHost())
	{
		text.setString(text.getString() + sf::IpAddress::getLocalAddress().toString() + "\n\n" + "Uczestnicy:\n" "1." + getPlayerName());
		player = std::make_unique<Player>(deck, font, maxID);
	}
	else
	{
		if (socket.connect(prev->getIP(), 2000) != sf::Socket::Done)
			state = 0;
		else 
		{
			socket.receive(buffer, sizeof(buffer), received);
			text.setString(buffer + getPlayerName());
			socket.send(getPlayerName().c_str(), getPlayerName().length() + 1);
		}
	}
}

gameStateNumber multiPlayer::update(sf::Event event, sf::RenderWindow& window)
{
	switch (state)
	{
	case 0:
		if (b_menu->clicked(event))
		{
			return gameStateNumber::menu;
		}
		b_menu->uptade(getMousePos(window));
		break;
	case 1:
		if (waiting)
		{
			listener;
			listener.listen(2000);
			listener.accept(socket);
			waiting = false;
			std::string temp = text.getString();
			socket.send(temp.c_str(), temp.length() + 1);
			socket.receive(buffer, sizeof(buffer), received);
			text.setString(text.getString() + buffer);
		}
		if (b_addPlayer->clicked(event))
		{
			maxID++;
			text.setString(text.getString() + '\n' + std::to_string(maxID) + '.');
			waiting = true;
		}
		if (b_menu->clicked(event))
		{
			return gameStateNumber::menu;
		}
		if (prev->getHost() && maxID < 2)
			b_addPlayer->uptade(getMousePos(window));
		b_menu->uptade(getMousePos(window));
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
		text.setString("Nie udalo sie dolaczyc do gry o podanym IP");
		window.draw(text);
		b_menu->draw(window);
		break;
	case 1:
		if (waiting)
			b_addPlayer->setString("Oczekiwanie\nna gracza...");
		else
			b_addPlayer->setString(" Dodaj\nmiejsce");
		window.draw(text);
		b_addPlayer->draw(window);
		b_menu->draw(window);
		break;
	case 2:
		break;
	default:
		break;
	}
}
