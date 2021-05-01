#pragma once

#include "game.h"
#include "multiPlayerSettings.h"
#include "../AI.h"

class multiPlayer :
	public game
{
	multiPlayerSettings* prev;

	sf::Font font;
	sf::Text text;

	sf::TcpSocket guest1;
	sf::TcpSocket guest2;
	sf::TcpSocket guest3;
	std::vector<std::unique_ptr<AI>> bots;

	std::vector<std::unique_ptr<object>> cardback;
	std::vector<sf::Text> infoPlayer;
	std::string podium;

	sf::TcpListener listener;
	char buffer[600];
	std::size_t received;
	char data[600];

	std::unique_ptr<button> b_addSlot;
	std::unique_ptr<button> b_deleteSlot;
	std::unique_ptr<button> b_addBot;
	std::unique_ptr<button> b_deleteBot;
	std::unique_ptr<button> b_start;
	std::unique_ptr<button> b_menu;

	int state = 1;
	int maxID = 1;
	bool waiting = false;
	bool threadRunning = false;
	bool myTurn = true;
	bool host = true;

	std::thread t;

public:
	multiPlayer(multiPlayerSettings* _prev, Resources* _resources);
	~multiPlayer();
	void listen(sf::TcpSocket& guest);
	void waitForStart();
	void waitForData(sf::TcpSocket& guest);
	void putDataToSend();
	bool loadDataFromBuffer(bool onlyDeck = false);
	void initializeInfo();
	std::string getPodium();
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

