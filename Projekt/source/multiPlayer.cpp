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

	b_addSlot = std::make_unique<button>(" Dodaj\nmiejsce", font, 250, 200, 405, 250, 38);
	b_deleteSlot = std::make_unique<button>(" Usun\nmiejsce", font, 250, 200, 665, 250, 38);
	b_start = std::make_unique<button>("Rozpocznij", font, 600, 150, 400, 540);
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
			socket.send(putDeckToString().c_str(), putDeckToString().length() + 1);
		}
	}
}

void multiPlayer::listen()
{
	listener;
	listener.listen(2000);
	if (listener.accept(socket) == sf::Socket::Done)
	{
		std::string temp = text.getString();
		socket.send(temp.c_str(), temp.length() + 1);
		socket.receive(buffer, sizeof(buffer), received);
		text.setString(text.getString() + buffer);
		socket.receive(buffer, sizeof(buffer), received);
		loadDeckFromBuffer();
		player = std::make_unique<Player>(deck, font, maxID);
	}
	waiting = false;
	threadRunning = false;
}

std::string multiPlayer::putDeckToString()
{
	std::string rtrn = "";

	for (auto i = deck.begin(); i != deck.end(); i++)
	{
		rtrn += int((*i)->getFigure());
		rtrn += int((*i)->getSuit());
	}

	rtrn += 'e';
	return rtrn;
}

void multiPlayer::loadDeckFromBuffer()
{
	int i = 0;
	deck.clear();

	while (buffer[i] != 'e')
	{
		card* newCard = new card(figureNumber(buffer[i]), suitNumber(buffer[i+1]), font, textureSuit.get(), 120, 180, 400, 400, sf::Color::White);
		deck.push_back(newCard);
		i += 2;
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
		if (player->getID() == 2)
		{
			if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
			{
				state = 2;
				socket.send(putDeckToString().c_str(), putDeckToString().length() + 1);
			}
		}
		if (waiting)
		{
			if (!threadRunning)
			{
				threadRunning = true;
				t = std::thread(&multiPlayer::listen, this);
				t.detach();
			}
		}
		if (b_addSlot->clicked(event) && !waiting)
		{
			maxID++;
			text.setString(text.getString() + '\n' + std::to_string(maxID) + '.');
			waiting = true;
		}
		if(b_deleteSlot->clicked(event) && maxID > 1)
		{
			maxID--;
			std::string temp = text.getString();
			temp.erase(temp.length() - 3, 3);
			text.setString(temp);
			listener.close();
		}
		if (b_start->clicked(event))
		{
			socket.send("2", 2);
			socket.receive(buffer, sizeof(buffer), received);
			loadDeckFromBuffer();
			state = 2;
		}
		if (b_menu->clicked(event))
		{
			return gameStateNumber::menu;
		}
		if (prev->getHost() && maxID < 2)
			b_addSlot->uptade(getMousePos(window));
		b_deleteSlot->uptade(getMousePos(window));
		if (maxID > 1 && !waiting)
			b_start->uptade(getMousePos(window));
		b_menu->uptade(getMousePos(window));
		break;
	case 2:
		game::update(event, window);
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
			b_addSlot->setString("Oczekiwanie\nna gracza...");
		else
			b_addSlot->setString(" Dodaj\nmiejsce");
		window.draw(text);
		b_addSlot->draw(window);
		b_deleteSlot->draw(window);
		b_start->draw(window);
		b_menu->draw(window);
		break;
	case 2:
		game::draw(window);
		break;
	default:
		break;
	}
}
