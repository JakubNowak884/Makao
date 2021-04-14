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
		if (guest1.connect(prev->getIP(), 2000) != sf::Socket::Done)
			state = 0;
		else
		{
			guest1.receive(buffer, sizeof(buffer), received);
			text.setString(buffer + getPlayerName());
			guest1.send(getPlayerName().c_str(), getPlayerName().length() + 1);
			guest1.receive(buffer, sizeof(buffer), received);
			loadDeckFromBuffer();
			guest1.receive(buffer, sizeof(buffer), received);
			maxID = buffer[0];
			player = std::make_unique<Player>(deck, font, maxID);
			guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
			myTurn = false;
			host = false;
		}
	}
}

void multiPlayer::listen(sf::TcpSocket& guest)
{
	listener;
	listener.listen(2000);
	if (listener.accept(guest) == sf::Socket::Done)
	{
		std::string temp = text.getString();
		guest.send(temp.c_str(), temp.length() + 1);
		guest.receive(buffer, sizeof(buffer), received);
		text.setString(text.getString() + buffer);
		guest.send(putDeckToString().c_str(), putDeckToString().length() + 1);
		temp[0] = maxID;
		guest.send(temp.c_str(), temp.length() + 1);
		guest.receive(buffer, sizeof(buffer), received);
		loadDeckFromBuffer();
		temp = text.getString();
		switch (maxID)
		{
		case 3:
			guest1.send(temp.c_str(), temp.length() + 1);
			guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
			break;
		case 4:
			guest1.send(temp.c_str(), temp.length() + 1);
			guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
			guest2.send(temp.c_str(), temp.length() + 1);
			guest2.send(putDeckToString().c_str(), putDeckToString().length() + 1);
			break;
		}
	}
	waiting = false;
	b_addSlot->setChosen(false);
	threadRunning = false;
}

void multiPlayer::waitForStart()
{
	if (guest1.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
	{
		if (buffer[0] != 2 && buffer[0] != 3 && buffer[0] != 4)
		{
			text.setString(buffer);
			guest1.receive(buffer, sizeof(buffer), received);
			loadDeckFromBuffer();
		}
		else
		{
			amountOfPlayers = buffer[0];
			state = 2;
		}
	}
	threadRunning = false;
}

void multiPlayer::waitForData(sf::TcpSocket& guest)
{
	if (guest.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
	{
		loadDeckFromBuffer();
		guest.receive(buffer, sizeof(buffer), received);
		loadDataFromBuffer();

		if (host)
		{
			switch (maxID)
			{
			case 2:
				guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
				guest1.send(putDataToString().c_str(), putDataToString().length() + 1);
				break;
			case 3:
				guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
				guest1.send(putDataToString().c_str(), putDataToString().length() + 1);
				guest2.send(putDeckToString().c_str(), putDeckToString().length() + 1);
				guest2.send(putDataToString().c_str(), putDataToString().length() + 1);
				break;
			case 4:
				guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
				guest1.send(putDataToString().c_str(), putDataToString().length() + 1);
				guest2.send(putDeckToString().c_str(), putDeckToString().length() + 1);
				guest2.send(putDataToString().c_str(), putDataToString().length() + 1);
				guest3.send(putDeckToString().c_str(), putDeckToString().length() + 1);
				guest3.send(putDataToString().c_str(), putDataToString().length() + 1);
				break;
			}
		}

		if (turn == player->getID())
			myTurn = true;
	}
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

std::string multiPlayer::putDataToString()
{
	std::string rtrn = "0123456789";

	rtrn[0] = turn;
	rtrn[1] = wonCounter;
	rtrn[2] = actionCardIsActive;
	rtrn[3] = addDrawAmount;
	rtrn[4] = four;
	rtrn[5] = jackID;
	rtrn[6] = delay;
	rtrn[7] = int(currentSuit);
	rtrn[8] = int(currentFigure);

	return rtrn;
}

void multiPlayer::loadDataFromBuffer()
{
	turn = buffer[0];
	wonCounter = buffer[1];
	actionCardIsActive = buffer[2];
	addDrawAmount = buffer[3];
	four = buffer[4];
	jackID = buffer[5];
	delay = buffer[6];
	currentSuit = suitNumber(buffer[7]);
	currentFigure = figureNumber(buffer[8]);
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
		if (player->getID() != 1)
		{
			if (!threadRunning)
			{
				threadRunning = true;
				t = std::thread(&multiPlayer::waitForStart, this);
				t.detach();
			}
		}
		if (waiting)
		{
			if (!threadRunning)
			{
				threadRunning = true;
				switch (maxID)
				{
				case 2:
					t = std::thread(&multiPlayer::listen, this, std::ref(guest1));
					break;
				case 3:
					t = std::thread(&multiPlayer::listen, this, std::ref(guest2));
					break;
				case 4:
					t = std::thread(&multiPlayer::listen, this, std::ref(guest3));
					break;
				}
				t.detach();
			}
		}
		if (b_addSlot->clicked(event) && !waiting)
		{
			maxID++;
			text.setString(text.getString() + '\n' + std::to_string(maxID) + '.');
			waiting = true;
		}
		if(b_deleteSlot->clicked(event))
		{
			maxID--;
			std::string temp = text.getString();
			temp.erase(temp.length() - 3, 3);
			text.setString(temp);
			listener.close();
		}
		if (b_start->clicked(event))
		{
			std::string temp;
			temp[0] = maxID;
			switch (maxID)
			{
			case 2:
				guest1.send(temp.c_str(), 2);
				break;
			case 3:
				guest2.send(temp.c_str(), 2);
				guest1.send(temp.c_str(), 2);
				break;
			case 4:
				guest3.send(temp.c_str(), 2);
				guest2.send(temp.c_str(), 2);
				guest1.send(temp.c_str(), 2);
				break;
			}
			amountOfPlayers = maxID;
			state = 2;
		}
		if (b_menu->clicked(event))
		{
			return gameStateNumber::menu;
		}
		if (prev->getHost() && maxID < 3 && player->getID() == 1)
			b_addSlot->uptade(getMousePos(window));

		if (player->getID() == 1 && waiting && maxID > 1)
			b_deleteSlot->uptade(getMousePos(window));

		if (maxID > 1 && !waiting && player->getID() == 1)
			b_start->uptade(getMousePos(window));

		b_menu->uptade(getMousePos(window));
		break;
	case 2:
		if (turn != player->getID() && myTurn)
		{
			if (host)
			{
				switch (maxID)
				{
				case 2:
					guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
					guest1.send(putDataToString().c_str(), putDataToString().length() + 1);
					break;
				case 3:
					guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
					guest1.send(putDataToString().c_str(), putDataToString().length() + 1);
					guest2.send(putDeckToString().c_str(), putDeckToString().length() + 1);
					guest2.send(putDataToString().c_str(), putDataToString().length() + 1);
					break;
				case 4:
					guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
					guest1.send(putDataToString().c_str(), putDataToString().length() + 1);
					guest2.send(putDeckToString().c_str(), putDeckToString().length() + 1);
					guest2.send(putDataToString().c_str(), putDataToString().length() + 1);
					guest3.send(putDeckToString().c_str(), putDeckToString().length() + 1);
					guest3.send(putDataToString().c_str(), putDataToString().length() + 1);
					break;
				}
			}
			else
			{
				guest1.send(putDeckToString().c_str(), putDeckToString().length() + 1);
				guest1.send(putDataToString().c_str(), putDataToString().length() + 1);
			}
			myTurn = false;
		}
		else if (turn != player->getID() && !myTurn)
		{
			if (!threadRunning)
			{
				if (host)
				{
					switch (turn)
					{
					case 2:
						threadRunning = true;
						t = std::thread(&multiPlayer::waitForData, this, std::ref(guest1));
						t.detach();
						break;
					case 3:
						threadRunning = true;
						t = std::thread(&multiPlayer::waitForData, this, std::ref(guest2));
						t.detach();
						break;
					case 4:
						threadRunning = true;
						t = std::thread(&multiPlayer::waitForData, this, std::ref(guest3));
						t.detach();
						break;
					}
				}
				else
				{
					threadRunning = true;
					t = std::thread(&multiPlayer::waitForData, this, std::ref(guest1));
					t.detach();
				}
			}
		}
		return game::update(event, window);
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
