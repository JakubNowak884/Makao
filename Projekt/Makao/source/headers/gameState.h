#pragma once

#include "button.h"
#include "AI.h"

enum class gameStateNumber { def, quit, menu, singlePlayerSettings, singlePlayer, endgame };

class gameState
{
	static int amountOfPlayers;

	public:
		static void setAmountOfPlayers(int amount);
		static int getAmountOfPlayers();
		sf::Vector2f getMousePos(sf::RenderWindow& window);
		virtual AI* getAI(int number);
		virtual int getWon();
		virtual gameStateNumber update(sf::Event event, sf::RenderWindow& Window) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
};

