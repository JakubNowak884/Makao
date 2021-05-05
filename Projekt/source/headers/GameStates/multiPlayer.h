#pragma once

#include "Game.h"
#include "MultiPlayerSettings.h"
#include "../AI.h"

class MultiPlayer :
	public Game
{
	MultiPlayerSettings* prev;

	sf::Text text;

	sf::TcpSocket guest1;
	sf::TcpSocket guest2;
	sf::TcpSocket guest3;
	std::vector<std::unique_ptr<AI>> bots;

	std::vector<std::unique_ptr<Object>> cardback;
	std::vector<sf::Text> infoPlayer;
	std::string podium;

	sf::TcpListener listener;
	char buffer[700];
	std::size_t received;
	std::size_t sent;
	char data[700];
	sf::Packet packet;

	std::unique_ptr<Button> b_addSlot;
	std::unique_ptr<Button> b_deleteSlot;
	std::unique_ptr<Button> b_start;
	std::unique_ptr<Button> b_menu;

	int state = 1;
	int maxID = 1;
	bool waiting = false;
	bool myTurn = true;
	bool host = true;
	bool threadRunning = false;

	int guest1Won = 0;
	int guest2Won = 0;
	int guest3Won = 0;

	std::thread t;
	std::exception_ptr texcpt = nullptr;

public:
	MultiPlayer(MultiPlayerSettings* _prev, Resources* _resources);
	~MultiPlayer();
	void listen(sf::TcpSocket& guest);
	void waitForStart();
	void waitForData(sf::TcpSocket& guest);
	sf::Packet putDataToSend(bool onlyDeck = false);
	void loadDataFromBuffer(bool onlyDeck = false);
	void initializeInfo();
	std::string getPodium();
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

