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

	std::unique_ptr<button> b_addPlayer;
	std::unique_ptr<button> b_menu;

	int state = 1;
	int maxID = 1;
	bool waiting = false;

public:
	multiPlayer(gameState* _prev);
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

