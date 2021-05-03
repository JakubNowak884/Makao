#include "..\headers\GameStates\multiPlayer.h"
#include "..\headers\Resources.h"
#include "windows.h"

MultiPlayer::MultiPlayer(MultiPlayerSettings* _prev, Resources* _resources)
	: Game(_resources, _prev->getOnlyQueens())
{
	prev = _prev;

	initText(text, 0, 0, 36);
	if (prev->getLAN())
		text.setString(resources->getText(int(gameStateNumber::multiPlayer), 1));
	else
		text.setString(resources->getText(int(gameStateNumber::multiPlayer), 2));
	

	b_addSlot = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 3), resources->getFont(), 250, 100, 405, 200, resources->getTexturePtr("button"), 38);
	b_deleteSlot = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 4), resources->getFont(), 250, 100, 665, 200, resources->getTexturePtr("button"), 38);
	b_start = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 5), resources->getFont(), 600, 150, 400, 540, resources->getTexturePtr("button"));
	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 6), resources->getFont(), 600, 150, 400, 700, resources->getTexturePtr("button"));

	if (prev->getHost())
	{
		std::string temp;

		if (prev->getLAN())
			temp = sf::IpAddress::getLocalAddress().toString();
		else
			temp = sf::IpAddress::getPublicAddress().toString();

		text.setString(text.getString() + temp);

		if (prev->getOnlyQueens())
			text.setString(text.getString() + resources->getText(int(gameStateNumber::multiPlayer), 7) + resources->getText(int(gameStateNumber::multiPlayer), 8) + L"1." + getPlayerName());
		else 
			text.setString(text.getString() + L"\n" + resources->getText(int(gameStateNumber::multiPlayer), 8) + L"1." + getPlayerName());

		player = std::make_unique<Player>(deck, resources, maxID);
	}
	else
	{
		if (guest1.connect(prev->getIP(), 50002) != sf::Socket::Done)
			state = 0;
		else
		{
			guest1.receive(buffer, sizeof(buffer), received);
			sf::String str = getPlayerName();
			text.setString(buffer + str);
			std::string str2 = str;
			guest1.send(str2.c_str(), str2.length() + 1);
			guest1.receive(buffer, sizeof(buffer), received);
			maxID = buffer[0];
			guest1.receive(buffer, sizeof(buffer), received);
			loadDataFromBuffer(true);
			player = std::make_unique<Player>(deck, resources, maxID);
			putDataToSend();
			guest1.send(data, 600);
			myTurn = false;
			host = false;
		}
	}
}

MultiPlayer::~MultiPlayer()
{
	guest3.disconnect();
	guest2.disconnect();
	guest1.disconnect();
	listener.close();
}

void MultiPlayer::listen(sf::TcpSocket& guest)
{
	listener.listen(50002);
	if (listener.accept(guest) == sf::Socket::Done)
	{
		std::string temp = text.getString();
		guest.send(temp.c_str(), temp.length() + 1);
		guest.receive(buffer, sizeof(buffer), received);
		text.setString(text.getString() + buffer);
		temp[0] = maxID;
		guest.send(temp.c_str(), temp.length() + 1);
		putDataToSend();
		guest.send(data, 600);
		guest.receive(buffer, sizeof(buffer), received);
		loadDataFromBuffer(true);
		temp = text.getString();
		switch (maxID)
		{
		case 3:
			guest1.send(temp.c_str(), temp.length() + 1);
			putDataToSend();
			guest1.send(data, 600);
			break;
		case 4:
			guest1.send(temp.c_str(), temp.length() + 1);
			putDataToSend();
			guest1.send(data, 600);
			guest2.send(temp.c_str(), temp.length() + 1);
			putDataToSend();
			guest2.send(data, 600);
			break;
		}
	}
	waiting = false;
	b_addSlot->setChosen(false);
	threadRunning = false;
}

void MultiPlayer::waitForStart()
{
	if (guest1.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
	{
		if (buffer[0] != 2 && buffer[0] != 3 && buffer[0] != 4 && buffer[0] != '0')
		{
			text.setString(buffer);
			guest1.receive(buffer, sizeof(buffer), received);
			loadDataFromBuffer();
		}
		else if (buffer[0] == '0')
		{
			state = 0;
		}
		else
		{
			amountOfPlayers = buffer[0];
			initializeInfo();
			putDataToSend();
			guest1.send(data, 600);
			if (guest1.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
			{
				state = 0;
				return;
			}
			loadDataFromBuffer();
			state = 2;
		}
	}
	threadRunning = false;
}

void MultiPlayer::waitForData(sf::TcpSocket& guest)
{
	if (guest.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
	{
		loadDataFromBuffer();

		if (host)
		{
			switch (maxID)
			{
			case 3:
				switch (turn)
				{
				case 1:
					putDataToSend();
					guest1.send(data, 600);
					break;
				case 3:
					putDataToSend();
					guest2.send(data, 600);
					break;
				}
				break;
			case 4:
				switch (turn)
				{
				case 1:
					putDataToSend();
					guest1.send(data, 600);
					guest2.send(data, 600);
					break;
				case 3:
					putDataToSend();
					guest2.send(data, 600);
					guest3.send(data, 600);
					break;
				case 4:
					putDataToSend();
					guest1.send(data, 600);
					guest3.send(data, 600);
					break;
				}
				break;
			}
		}

		if (turn == player->getID())
			myTurn = true;
	}

	threadRunning = false;
}

void MultiPlayer::putDataToSend()
{
	int ID = player->getID();

	if (host)
	{
		sf::String str = getPlayerName() + resources->getText(int(gameStateNumber::multiPlayer), 9) + std::to_wstring(player->hand.size()) + resources->getText(int(gameStateNumber::multiPlayer), 10) + std::to_wstring(player->getDelay());
		std::string temp = str;
		data[200] = int(temp.length());
		temp.copy(&data[200 + 1], 100);

		int k = 2;
		for (auto i = infoPlayer.begin(); i != infoPlayer.end(); i++)
		{
			std::string temp = i->getString();
			data[100 * k + 100] = int(temp.length());
			temp.copy(&data[100 * k + 101], 100);
			k++;
		}
	}
	else
	{
		data[200] = ID;
		sf::String str = getPlayerName() + resources->getText(int(gameStateNumber::multiPlayer), 9) + std::to_wstring(player->hand.size()) + resources->getText(int(gameStateNumber::multiPlayer), 10) + std::to_wstring(player->getDelay());
		std::string temp = str;
		data[201] = int(temp.length());
		temp.copy(&data[202], 100);
	}

	data[0] = turn;
	data[1] = wonCounter;
	data[2] = actionCardIsActive;
	data[3] = addDrawAmount;
	data[4] = four;
	data[5] = jackID;
	data[6] = delay;
	data[7] = int(currentSuit);
	data[8] = int(currentFigure);
	data[9] = player->getWon();

	int j = 10;
	for (auto i = deck.begin(); i != deck.end(); i++)
	{
		data[j] = int((*i)->getFigure());
		data[j + 1] = int((*i)->getSuit());
		j += 2;
	}

	data[j] = 'e';
}

bool MultiPlayer::loadDataFromBuffer(bool onlyDeck)
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

	int i = 10;
	deck.clear();

	while (buffer[i] != 'e')
	{
		deck.push_back(std::make_shared<Card>(figureNumber(buffer[i]), suitNumber(buffer[i + 1]), resources->getFont(), resources->getTexturePtr("deck"), 120, 180, 400, 400, sf::Color::White));
		i += 2;
	}

	if (!onlyDeck)
	{
		if (host)
		{
			int ID = int(buffer[200]);
			if (ID < 0 && ID > 3)
				infoPlayer[0].setString(resources->getText(int(gameStateNumber::multiPlayer), 11));
			else
				infoPlayer[size_t(ID - 2)].setString(std::string(&buffer[202], buffer[201]) + buffer[9]);
		}
		else
		{
			int k = 1;
			for (auto i = infoPlayer.begin(); i != infoPlayer.end(); i++)
			{
				i->setString(std::string(&buffer[100 * k + 101], buffer[100 * k + 100]));
				k++;
				if (k == player->getID())
					k++;
			}
		}
	}
	return true;
}

void MultiPlayer::initializeInfo()
{
	sf::Text infoPlayer1;
	infoPlayer1.setFont(resources->getFont());
	infoPlayer1.setCharacterSize(24);

	switch (amountOfPlayers)
	{
	case 2:
		infoPlayer1.setPosition(470, 10);
		infoPlayer.push_back(infoPlayer1);

		cardback.push_back(std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White));
		cardback[0]->getShape().setTexture(resources->getTexturePtr("deck"));
		cardback[0]->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
		break;
	case 3:
		infoPlayer1.setPosition(10, 210);
		infoPlayer.push_back(infoPlayer1);

		infoPlayer1.setPosition(470, 10);
		infoPlayer.push_back(infoPlayer1);

		cardback.push_back(std::make_unique<Object>(120, 180, 70, 400, resources->getTexturePtr("deck"), sf::Color::White));
		cardback[0]->getShape().setTexture(resources->getTexturePtr("deck"));
		cardback[0]->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
		cardback.push_back(std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White));
		cardback[1]->getShape().setTexture(resources->getTexturePtr("deck"));
		cardback[1]->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
		break;
	case 4:
		infoPlayer1.setPosition(10, 210);
		infoPlayer.push_back(infoPlayer1);

		infoPlayer1.setPosition(470, 10);
		infoPlayer.push_back(infoPlayer1);

		infoPlayer1.setPosition(580, 210);
		infoPlayer.push_back(infoPlayer1);

		cardback.push_back(std::make_unique<Object>(120, 180, 70, 400, resources->getTexturePtr("deck"), sf::Color::White));
		cardback[0]->getShape().setTexture(resources->getTexturePtr("deck"));
		cardback[0]->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
		cardback.push_back(std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White));
		cardback[1]->getShape().setTexture(resources->getTexturePtr("deck"));
		cardback[1]->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
		cardback.push_back(std::make_unique<Object>(120, 180, 640, 400, resources->getTexturePtr("deck"), sf::Color::White));
		cardback[2]->getShape().setTexture(resources->getTexturePtr("deck"));
		cardback[2]->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
		break;
	}
}

std::string MultiPlayer::getPodium()
{
	return podium;
}

gameStateNumber MultiPlayer::update(sf::Event event, sf::RenderWindow& window)
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
				t = std::thread(&MultiPlayer::waitForStart, this);
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
					t = std::thread(&MultiPlayer::listen, this, std::ref(guest1));
					break;
				case 3:
					t = std::thread(&MultiPlayer::listen, this, std::ref(guest2));
					break;
				case 4:
					t = std::thread(&MultiPlayer::listen, this, std::ref(guest3));
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
			b_deleteSlot->setChosen(false);
		}
		if (b_start->clicked(event))
		{
			std::string temp;
			temp[0] = maxID;
			amountOfPlayers = maxID;
			initializeInfo();
			putDataToSend();
			switch (maxID)
			{
			case 4:
				if (guest3.send(temp.c_str(), 5) != sf::Socket::Done)
				{
					return gameStateNumber::menu;
				}
				guest3.receive(buffer, sizeof(buffer), received);
				loadDataFromBuffer();
				[[fallthrough]];
			case 3:
				if (guest2.send(temp.c_str(), 5) != sf::Socket::Done)
				{
					return gameStateNumber::menu;
				}
				guest2.receive(buffer, sizeof(buffer), received);
				loadDataFromBuffer();
				[[fallthrough]];
			case 2:
				if (guest1.send(temp.c_str(), 5) != sf::Socket::Done)
				{
					return gameStateNumber::menu;
				}
				guest1.receive(buffer, sizeof(buffer), received);
				loadDataFromBuffer();
				break;
			}
			putDataToSend();
			switch (maxID)
			{
			case 4:
				guest3.send(data, 600);
				[[fallthrough]];
			case 3:
				guest2.send(data, 600);
				[[fallthrough]];
			case 2:
				guest1.send(data, 600);
				break;
			}
			state = 2;
		}
		if (b_menu->clicked(event))
		{
			if (host)
			{
				std::string temp = "0";
				switch (maxID)
				{
				case 4:
					guest3.send(temp.c_str(), temp.length() + 1);
					[[fallthrough]];
				case 3:
					guest2.send(temp.c_str(), temp.length() + 1);
					[[fallthrough]];
				case 2:
					guest1.send(temp.c_str(), temp.length() + 1);
					break;
				}
			}
			else
			{
				std::string temp = text.getString();
				temp.erase(temp.length() - getPlayerName().length() - 3, getPlayerName().length() + 3);
				text.setString(temp);
				guest1.send(temp.c_str(), 100);
				guest1.disconnect();
			}
			return gameStateNumber::menu;
		}
		if (prev->getHost() && maxID < 4 && player->getID() == 1)
			b_addSlot->uptade(getMousePos(window));

		if (player->getID() == 1 && waiting && maxID > 1)
			b_deleteSlot->uptade(getMousePos(window));

		b_start->setChosen(false);
		if (maxID > 1 && !waiting && player->getID() == 1)
			b_start->uptade(getMousePos(window));

		b_menu->uptade(getMousePos(window));

		if (!host && guest1.getLocalPort() == 0)
			state = 0;

		break;
	case 2:
		if (turn != player->getID() && myTurn)
		{
			if (host)
			{
				putDataToSend();
				switch (maxID)
				{
				case 4:
					guest3.send(data, 600);
					[[fallthrough]];
				case 3:
					guest2.send(data, 600);
					[[fallthrough]];
				case 2:
					guest1.send(data, 600);
				}
			}
			else
			{
				putDataToSend();
				guest1.send(data, 600);
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
						t = std::thread(&MultiPlayer::waitForData, this, std::ref(guest1));
						t.detach();
						break;
					case 3:
						threadRunning = true;
						t = std::thread(&MultiPlayer::waitForData, this, std::ref(guest2));
						t.detach();
						break;
					case 4:
						threadRunning = true;
						t = std::thread(&MultiPlayer::waitForData, this, std::ref(guest3));
						t.detach();
						break;
					}
				}
				else
				{
					threadRunning = true;
					t = std::thread(&MultiPlayer::waitForData, this, std::ref(guest1));
					t.detach();
				}
			}
		}
		if (wonCounter == amountOfPlayers - 1)
		{
			if (host)
			{
				podium = " ";
				std::map<int, std::string> results;

				for (int i = 0; i < amountOfPlayers - 1; i++)
				{
					std::string temp = infoPlayer[i].getString();
					std::string temp2 = infoPlayer[i].getString();
					temp2.erase(temp2.length() - 31, 31);
					if (int(temp[temp.length() - 1]) == 0)
						temp[temp.length() - 1] = amountOfPlayers;
					results[int(temp[temp.length() - 1])] = temp2;
				}
				if (player->getWon() == 0)
					player->setWon(amountOfPlayers);
				sf::String str = getPlayerName();
				std::string tmp = str;
				results[player->getWon()] = tmp;
				for (int i = 1; i < amountOfPlayers + 1; i++)
					podium = podium + std::to_string(i) + ". " + results[i] + "\n";

				std::string temp3 = podium;
				temp3[0] = int(podium.length() - 1);
				podium.erase(0, 1);

				switch (maxID)
				{
				case 4:
					guest3.send(temp3.c_str(), 100);
					[[fallthrough]];
				case 3:
					guest2.send(temp3.c_str(), 100);
					[[fallthrough]];
				case 2:
					guest1.send(temp3.c_str(), 100);
					break;
				}
			}
			else
			{
				guest1.receive(buffer, sizeof(buffer), received);
				podium = std::string(&buffer[1], buffer[0]);
			}

			return gameStateNumber::endgame;
		}
		return Game::update(event, window);
		break;
	default:
		break;
	}

	return gameStateNumber::def;
}

void MultiPlayer::draw(sf::RenderWindow& window)
{
	switch (state)
	{
	case 0:
		text.setString(resources->getText(int(gameStateNumber::multiPlayer), 12));
		window.draw(text);
		b_menu->draw(window);
		break;
	case 1:
		if (waiting)
			b_addSlot->setString(resources->getText(int(gameStateNumber::multiPlayer), 13));
		else
			b_addSlot->setString(resources->getText(int(gameStateNumber::multiPlayer), 14));
		window.draw(text);
		b_addSlot->draw(window);
		b_deleteSlot->draw(window);
		b_start->draw(window);
		b_menu->draw(window);
		break;
	case 2:
		for (auto i = infoPlayer.begin(); i != infoPlayer.end(); i++)
			i->setFillColor(sf::Color::White);
		switch (player->getID())
		{
		case 1:
			for (int i = 0; i < 3; i++)
				if (turn - 2 == i)
					infoPlayer[i].setFillColor(sf::Color::Green);
			break;
		case 2:
			for (int i = 0; i < 3; i++)
				if ((turn == 1 && i == 0) || (turn - 2 == i && (i == 1 || i == 2)))
					infoPlayer[i].setFillColor(sf::Color::Green);
			break;
		case 3:
			for (int i = 0; i < 3; i++)
				if ((turn - 1 == i && (i == 0 || i == 1)) || (turn == 4 && i == 2))
					infoPlayer[i].setFillColor(sf::Color::Green);
			break;
		case 4:
			for (int i = 0; i < 3; i++)
				if (turn - 1 == i)
					infoPlayer[i].setFillColor(sf::Color::Green);
			break;
		}

		for (auto i = infoPlayer.begin(); i != infoPlayer.end(); i++)
		{
			if (player->getID() != 1 && i == infoPlayer.begin())
			{
				window.draw(*i);
			}
			else
			{
				std::string temp = i->getString();
				std::string temp2 = i->getString();
				i->setString(temp2.erase(temp2.length() - 1));
				window.draw(*i);
				i->setString(temp);
			}
		}

		for (auto i = cardback.begin(); i != cardback.end(); i++)
			i->get()->draw(window);

		Game::draw(window);
		break;
	default:
		break;
	}
}