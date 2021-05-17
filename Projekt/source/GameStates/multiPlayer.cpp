#include "..\headers\GameStates\multiPlayer.h"

MultiPlayer::MultiPlayer(MultiPlayerSettings* _prev, std::shared_ptr<Resources> _resources)
	: Game(_resources, _prev->getOnlyQueens())
{
	prev = _prev;

	b_addSlot = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 3), resources->getFont(), 250.0f, 100.0f, 405.0f, 200.0f, resources->getTexturePtr("button"), 38);
	b_deleteSlot = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 4), resources->getFont(), 250.0f, 100.0f, 665.0f, 200.0f, resources->getTexturePtr("button"), 38);
	b_start = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 5), resources->getFont(), 600.0f, 150.0f, 400.0f, 540.0f, resources->getTexturePtr("button"));
	b_menu = std::make_unique<Button>(resources->getText(int(gameStateNumber::multiPlayer), 6), resources->getFont(), 600.0f, 150.0f, 400.0f, 700.0f, resources->getTexturePtr("button"));

	initText(textLobby, 0, 0, 36);
	//ustawienie tekstu w zale�no�ci od ustawie� rozgrywki wielu graczy
	if (prev->getLAN())
		textLobby.setString(resources->getText(int(gameStateNumber::multiPlayer), 1));
	else
		textLobby.setString(resources->getText(int(gameStateNumber::multiPlayer), 2));

	if (prev->getHost())
	{
		std::string temp;

		if (prev->getLAN())
			temp = sf::IpAddress::getLocalAddress().toString();
		else
			temp = sf::IpAddress::getPublicAddress().toString();

		textLobby.setString(textLobby.getString() + temp);

		if (prev->getOnlyQueens())
			textLobby.setString(textLobby.getString() + resources->getText(int(gameStateNumber::multiPlayer), 7) + resources->getText(int(gameStateNumber::multiPlayer), 8) + L"1." + getPlayerName());
		else 
			textLobby.setString(textLobby.getString() + L"\n" + resources->getText(int(gameStateNumber::multiPlayer), 8) + L"1." + getPlayerName());

		player = std::make_unique<Player>(deck, resources, maxID);

		listener.setBlocking(false);
	}
	else
	{
		if (guest1.connect(prev->getIP(), 50052, sf::Time(sf::seconds(2.0f))) != sf::Socket::Done)
		{
			throw (resources->getText(int(gameStateNumber::multiPlayer), 13));
		}
		//otrzymanie pakietu z wersj� j�zykow�, aktualn� liczb� graczy oraz ustawieniami gry
		if (guest1.receive(packet) != sf::Socket::Done)
		{
			throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		}
		else
		{
			int languageVersion;
			packet >> languageVersion;
			if (resources->getLanguageVersion() != languageVersion)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 12));
			}

			packet >> maxID;

			sf::String temp;
			packet >> temp;
			textLobby.setString(temp + getPlayerName());
			//wys�anie pakietu z nazw� gracza
			sf::Packet packetToSend;
			packetToSend << getPlayerName();

			if (guest1.send(packetToSend) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			//otrzymanie pakietu z tali� kart
			if (guest1.receive(packet) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			loadDataFromPacket(true);
			player = std::make_unique<Player>(deck, resources, maxID);
			//odes�anie talii kart, po utworzeniu obiektu gracz
			if (guest1.send(putDataToSend(true)) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			myTurn = false;
			host = false;
			guest1.setBlocking(false);
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
	if (listener.accept(guest) == sf::Socket::Done)
	{
		sf::Packet packetToSend;
		packetToSend << resources->getLanguageVersion();
		packetToSend << maxID;
		packetToSend << textLobby.getString();
		//wys�anie pakietu z wersj� j�zykow�, aktualn� liczb� graczy oraz ustawieniami gry
		if (guest.send(packetToSend) != sf::Socket::Done)
		{
			throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		}
		//otrzymanie pakietu z nazw� gracza, kt�ry do��czy� do gry
		if (guest.receive(packet) != sf::Socket::Done)
		{
			throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		}
		std::wstring temp;
		packet >> temp;
		textLobby.setString(textLobby.getString() + temp);
		//wys�anie pakietu z tali� kart
		if (guest.send(putDataToSend(true)) != sf::Socket::Done)
		{
			throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		}
		//otrzymanie pakietu z zmodyfikowan� tali� kart
		if (guest.receive(packet) != sf::Socket::Done)
		{
			throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		}
		loadDataFromPacket(true);

		sf::Packet packetToSend2;
		packetToSend2 << 9;
		packetToSend2 << textLobby.getString();
		//wys�anie informacji o nowym graczu i talii do pozosta�ych graczy
		switch (maxID)
		{
		case 3:
			if (guest1.send(packetToSend2) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			if (guest1.send(putDataToSend(true)) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			break;
		case 4:
			if (guest1.send(packetToSend2) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			if (guest1.send(putDataToSend(true)) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			if (guest2.send(packetToSend2) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			if (guest2.send(putDataToSend(true)) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
		}
		waiting = false;
		b_addSlot->setChosen(false);
		listener.close();
		guest.setBlocking(false);
	}
}

void MultiPlayer::waitForStart()
{
	switch (guest1.receive(packet))
	{
	case sf::Socket::Done:
	{
		guest1.setBlocking(true);
		int choice = 0;
		packet >> choice;
		//pakiet dostarczy� wiadomo�� o opuszczeniu gry przez za�o�yciela
		switch (choice)
		{
		case 0:
			throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			break;
		//pakiet dostarczy� wiadomo�� o do��czeniu nowego gracza
		case 9:
		{
			sf::String temp;
			packet >> temp;
			textLobby.setString(temp);
			if (guest1.receive(packet) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			loadDataFromPacket(true);
		}
			break;
		//pakiet dostarczy� wiadomo�� o ostatecznej liczbie graczy - oznacza to rozpocz�cie gry
		default:
			amountOfPlayers = choice;
			initializeInfo();
			//wys�anie informacji o stanie gry z perspektywy konkretnego gracza
			if (guest1.send(putDataToSend()) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			//otrzymanie informacji o og�lnym stanie gry
			if (guest1.receive(packet) != sf::Socket::Done)
			{
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
			}
			loadDataFromPacket();
			state = multiPlayerState::game;
			break;
		}
	}
		guest1.setBlocking(false);
		break;
	case sf::Socket::Disconnected:
		throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		break;
	case sf::Socket::Partial:
		throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		break;
	case sf::Socket::Error:
		throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		break;
	default:
		break;
	}
}

void MultiPlayer::waitForData(sf::TcpSocket& guest)
{
	switch (guest.receive(packet))
	{
	case sf::Socket::Done:
		loadDataFromPacket();
		//je�li gracz by� za�o�ycielem gry rozsy�a on otrzymane dane do pozosta�ych graczy
		if (host)
		{
			switch (maxID)
			{
			case 3:
				switch (turn)
				{
				case 1:
					if (guest1.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					break;
				case 3:
					if (guest2.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					break;
				}
				break;
			case 4:
				switch (turn)
				{
				case 1:
					if (guest1.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					if (guest2.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					break;
				case 3:
					if (guest2.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					if (guest3.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					break;
				case 4:
					if (guest1.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					if (guest3.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					break;
				}
				break;
			}
		}
		if (turn == player->getID())
			myTurn = true;
		break;
	case sf::Socket::Disconnected:
		throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		break;
	case sf::Socket::Partial:
		throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		break;
	case sf::Socket::Error:
		throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
		break;
	default:
		break;
	}
}

sf::Packet MultiPlayer::putDataToSend(bool onlyDeckAndGameData)
{
	sf::Packet packet;
	//do pakietu dodawane s� informacje o poszczeg�lnych graczach
	if (!onlyDeckAndGameData)
	{
		if (host) 
		{
			sf::String str = getPlayerName() + resources->getText(int(gameStateNumber::multiPlayer), 9) + std::to_wstring(player->hand.size()) + resources->getText(int(gameStateNumber::multiPlayer), 10) + std::to_wstring(player->getDelay());
			packet << str;
			for (auto i = infoPlayer.begin(); i != infoPlayer.end(); i++)
			{
				sf::String temp = i->getString();
				packet << temp;
			}
		}
		else
		{
			packet << player->getID();
			sf::String str = getPlayerName() + resources->getText(int(gameStateNumber::multiPlayer), 9) + std::to_wstring(player->hand.size()) + resources->getText(int(gameStateNumber::multiPlayer), 10) + std::to_wstring(player->getDelay());
			packet << str;
			packet << player->getWon();
		}
	}
	//do pakietu dodawane s� infromacje o rozgrywce
	packet << turn;
	packet << wonCounter;
	packet << actionCardIsActive;
	packet << addDrawAmount;
	packet << four;
	packet << jackID;
	packet << delay;
	packet << int(currentSuit);
	packet << int(currentFigure);
	//do pakietu dodawana jest informacja o talii kart
	for (auto i = deck.begin(); i != deck.end(); i++)
	{
		packet << int((*i)->getFigure());
		packet << int((*i)->getSuit());
	}
	return packet;
}

void MultiPlayer::loadDataFromPacket(bool onlyDeckAndGameData)
{
	//z pakietu czytane s� informacje o graczach
	if (!onlyDeckAndGameData)
	{
		if (host)
		{
			int ID;
			sf::String text;
			packet >> ID;
			packet >> text;
			infoPlayer[size_t(ID - 2)].setString(text);
			switch (ID)
			{
			case 2:
				packet >> guest1Won;
				break;
			case 3:
				packet >> guest2Won;
				break;
			case 4:
				packet >> guest3Won;
				break;
			}
		}
		else
		{
			int k = 1;
			for (auto i = infoPlayer.begin(); i != infoPlayer.end(); i++)
			{
				sf::String text;
				packet >> text;
				i->setString(text);
				k++;
				if (k == player->getID())
				{
					packet >> text;
				}
			}
		}
	}
	//z pakietu czytane s� informacje o rozgrywce
	packet >> turn;
	packet >> wonCounter;
	packet >> actionCardIsActive;
	packet >> addDrawAmount;
	packet >> four;
	packet >> jackID;
	packet >> delay;
	int  currentSuitInt;
	packet >> currentSuitInt;
	currentSuit = suitNumber(currentSuitInt);
	int  currentFigureInt;
	packet >> currentFigureInt;
	currentFigure = figureNumber(currentFigureInt);

	deck.clear();
	//z pakietu czytane s� informacje o talii
	while (!packet.endOfPacket())
	{
		packet >> currentFigureInt;
		packet >> currentSuitInt;
		deck.push_back(std::make_shared<Card>(figureNumber(currentFigureInt), suitNumber(currentSuitInt), resources->getTexturePtr("deck"), 120.0f, 180.0f, 400.0f, 400.0f));
	}
}

void MultiPlayer::initializeInfo()
{
	sf::Text infoPlayer1;
	infoPlayer1.setFont(resources->getFont());
	infoPlayer1.setCharacterSize(24);
	//w zale�no�ci od liczby graczy informacje o nich oraz grafika ich rewersu kart umieszczana jest w r�nych miejscach na ekranie
	switch (amountOfPlayers)
	{
	case 2:
		infoPlayer1.setPosition(470, 10);
		infoPlayer.push_back(infoPlayer1);

		cardback.push_back(std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White));
		break;
	case 3:
		infoPlayer1.setPosition(10, 210);
		infoPlayer.push_back(infoPlayer1);

		infoPlayer1.setPosition(470, 10);
		infoPlayer.push_back(infoPlayer1);

		cardback.push_back(std::make_unique<Object>(120, 180, 70, 400, resources->getTexturePtr("deck"), sf::Color::White));
		cardback.push_back(std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White));
		break;
	case 4:
		infoPlayer1.setPosition(10, 210);
		infoPlayer.push_back(infoPlayer1);

		infoPlayer1.setPosition(470, 10);
		infoPlayer.push_back(infoPlayer1);

		infoPlayer1.setPosition(580, 210);
		infoPlayer.push_back(infoPlayer1);

		cardback.push_back(std::make_unique<Object>(120, 180, 70, 400, resources->getTexturePtr("deck"), sf::Color::White));
		cardback.push_back(std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White));
		cardback.push_back(std::make_unique<Object>(120, 180, 640, 400, resources->getTexturePtr("deck"), sf::Color::White));
		break;
	}

	for (auto i = cardback.begin(); i != cardback.end(); i++)
	{
		(*i)->getShape().setTexture(resources->getTexturePtr("deck"));
		(*i)->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
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
	case multiPlayerState::lobby:
		//je�li gracz nie jest za�o�ycielem gry oczekuje on na start
		if (player->getID() != 1)
		{
			waitForStart();
		}
		//je�li gra aktualnie oczekuje na do��czenie gracza
		if (waiting)
		{
			switch (maxID)
			{
			case 2:
				listen(guest1);
				break;
			case 3:
				listen(guest2);
				break;
			case 4:
				listen(guest3);
				break;
			}
		}
		if (b_addSlot->clicked(event) && !waiting)
		{
			switch (listener.listen(50052))
			{
			case sf::Socket::Done:
				break;
			case sf::Socket::Error:
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				break;
			default:
				throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				break;
			}
			maxID++;
			textLobby.setString(textLobby.getString() + '\n' + std::to_string(maxID) + '.');
			waiting = true;
		}
		if (b_deleteSlot->clicked(event))
		{
			maxID--;
			std::string temp = textLobby.getString();
			//usuni�cie miejsca na gracza wy�wietlanego w poczekalni
			temp.erase(temp.length() - 3, 3);
			textLobby.setString(temp);
			//zako�czenie oczekiwania na gracza
			listener.close();
			waiting = false;
			b_deleteSlot->setChosen(false);
		}
		if (b_start->clicked(event))
		{
			listener.close();
			//przes�anie informacji o ostatecznej liczbie graczy do wszystkich go�ci, otrzymanie informacji o grze z perspektywy ka�dego z go�ci
			sf::Packet packetToSend;
			packetToSend << maxID;
			amountOfPlayers = maxID;
			initializeInfo();
			switch (maxID)
			{
			case 4:
				guest3.setBlocking(true);
				if (guest3.send(packetToSend) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				if (guest3.receive(packet) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				loadDataFromPacket();
				[[fallthrough]];
			case 3:
				guest2.setBlocking(true);
				if (guest2.send(packetToSend) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				if (guest2.receive(packet) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				loadDataFromPacket();
				[[fallthrough]];
			case 2:
				guest1.setBlocking(true);
				if (guest1.send(packetToSend) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				if (guest1.receive(packet) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				loadDataFromPacket();
				break;
			}
			//przes�anie do ka�dego z go�ci og�lnych(wsp�lnych) informacji o grze
			switch (maxID)
			{
			case 4:
				if (guest3.send(putDataToSend()) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				guest3.setBlocking(false);
				[[fallthrough]];
			case 3:
				if (guest2.send(putDataToSend()) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				guest2.setBlocking(false);
				[[fallthrough]];
			case 2:
				if (guest1.send(putDataToSend()) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				guest1.setBlocking(false);
				break;
			}
			state = multiPlayerState::game;
		}
		if (b_menu->clicked(event))
		{
			//je�li gracz b�d�cy za�o�ycielem opu�ci rozgrywk�, do reszty przesy�ana jest odpowiednia informacja
			if (host)
			{
				sf::Packet packetToSend;
				packetToSend << 0;
				switch (maxID)
				{
				case 4:
					if (guest3.send(packetToSend) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					[[fallthrough]];
				case 3:
					if (guest2.send(packetToSend) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					[[fallthrough]];
				case 2:
					if (guest1.send(packetToSend) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					break;
				}
			}
			else
			{
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
		break;

		case multiPlayerState::game:
		//gracz w�a�nie zako�czy� tur�
		if (turn != player->getID() && myTurn)
		{
			//je�li jest za�o�ycielem przesy�a informacje o aktualnym stanie gry wszystkim pozosta�ym graczom
			if (host)
			{
				switch (maxID)
				{
				case 4:
					if (guest3.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					[[fallthrough]];
				case 3:
					if (guest2.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					[[fallthrough]];
				case 2:
					if (guest1.send(putDataToSend()) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
				}
			}
			//w przeciwnym wypadku przesy�a informacje o grze w�a�cicielowi
			else
			{
				if (guest1.send(putDataToSend()) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
			}
			myTurn = false;
		}
		//gracz aktualnie nie wykonuje tury
		else if (turn != player->getID() && !myTurn)
		{
			//je�li gracz jest za�o�ycielem w zale�no�ci od tury oczekuje na dane o grze od konkretnego gracza
			if (host)
			{
				switch (turn)
				{
				case 2:
					waitForData(guest1);
					break;
				case 3:
					waitForData(guest2);
					break;
				case 4:
					waitForData(guest3);
					break;
				}
			}
			//w przeciwnym wypadku gracz oczekuje na dane o grze od za�o�yciela
			else
			{
				waitForData(guest1);
			}
		}
		//wszyscy gracze opr�cz jednego zako�czyli rozgrywk�
		if (wonCounter == amountOfPlayers - 1)
		{
			//je�li gracz jest za�o�ycielem tworzy informacje o podium, a nast�pnie przesy�a je do reszty graczy
			if (host)
			{
				podium = " ";
				std::map<int, std::string> results;

				for (int i = 0; i < amountOfPlayers - 1; i++)
				{
					std::string temp = infoPlayer[i].getString();
					switch (i)
					{
					case 0:
						//je�li gracz nie ma ustalonego miejsca, to znaczy, �e zaj�� ostatnie
						if (guest1Won == 0)
							guest1Won = amountOfPlayers;
						//z informacji o graczu uzyskiwana jest jego nazwa
						results[guest1Won] = temp.erase(temp.length() - 31, 31) + "\n";
						break;
					case 1:
						if (guest2Won == 0)
							guest2Won = amountOfPlayers;
						results[guest2Won] = temp.erase(temp.length() - 31, 31) + "\n";
						break;
					case 2:
						if (guest3Won == 0)
							guest3Won = amountOfPlayers;
						results[guest3Won] = temp.erase(temp.length() - 31, 31) + "\n";
						break;
					}
				}
				if (player->getWon() == 0)
					player->setWon(amountOfPlayers);

				sf::String str = getPlayerName();
				results[player->getWon()] = str + "\n";
				
				for (int i = 1; i < amountOfPlayers + 1; i++)
					podium = podium + std::to_string(i) + ". " + results[i];
				//wys�anie informacji o zaj�tych przez graczy miejscach do pozosta�ych graczy
				sf::Packet packetToSend;
				packetToSend << podium;

				switch (maxID)
				{
				case 4:
					if (guest3.send(packetToSend) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					[[fallthrough]];
				case 3:
					if (guest2.send(packetToSend) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					[[fallthrough]];
				case 2:
					if (guest1.send(packetToSend) != sf::Socket::Done)
					{
						throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
					}
					break;
				}
			}
			//w przeciwnym wypadku gracz oczekuje na dane od za�o�yciela o zaj�tych przez graczy miejscach 
			else
			{
				guest1.setBlocking(true);
				if (guest1.receive(packet) != sf::Socket::Done)
				{
					throw (resources->getText(int(gameStateNumber::multiPlayer), 11));
				}
				packet >> podium;
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
	case multiPlayerState::lobby:
		//zmiana napisu na przycisku w zale�no�ci od dodania/oczekiwania na gracza
		if (waiting)
			b_addSlot->setString(resources->getText(int(gameStateNumber::multiPlayer), 14));
		else
			b_addSlot->setString(resources->getText(int(gameStateNumber::multiPlayer), 15));
		window.draw(textLobby);
		b_addSlot->draw(window);
		b_deleteSlot->draw(window);
		b_start->draw(window);
		b_menu->draw(window);
		break;
	case multiPlayerState::game:
		//zresetowanie kolor�w napisu informacji o graczach
		for (auto i = infoPlayer.begin(); i != infoPlayer.end(); i++)
			i->setFillColor(sf::Color::White);
		//ustalenie kt�ry gracz aktualnie wykonuje tur�, w zale�no�ci od ID gracza
		//w zale�no�ci od aktualnej tury, zmieniany jest kolor na zielony odpowiednich element�w tabeli informacji o graczach
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
			window.draw(*i);
		}

		for (auto i = cardback.begin(); i != cardback.end(); i++)
			i->get()->draw(window);

		Game::draw(window);
		break;
	default:
		break;
	}
}