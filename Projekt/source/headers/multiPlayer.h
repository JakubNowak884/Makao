#pragma once

#include "game.h"

class multiPlayer :
	public game
{
	gameState* prev;

	sf::Font font;
	sf::Text text;

	sf::TcpSocket guest1;
	sf::TcpSocket guest2;
	sf::TcpSocket guest3;

	sf::TcpListener listener;
	char buffer[2000];
	std::size_t received;

	std::unique_ptr<button> b_addSlot;
	std::unique_ptr<button> b_deleteSlot;
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
	multiPlayer(gameState* _prev);
	void listen(sf::TcpSocket& guest);
	void waitForStart();
	void waitForData(sf::TcpSocket& guest);
	std::string putDeckToString();
	void loadDeckFromBuffer();
	std::string putDataToString();
	void loadDataFromBuffer();
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

