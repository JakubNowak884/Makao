#pragma once

#include "game.h"

class multiPlayer :
	public game
{
	gameState* prev;

	sf::Font font;
	sf::Text text;

	sf::TcpSocket socket;
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

	std::thread t;

public:
	multiPlayer(gameState* _prev);
	void listen();
	std::string putDeckToString();
	void loadDeckFromBuffer();
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

