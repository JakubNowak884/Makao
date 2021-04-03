#pragma once

#include "button.h"
#include "AI.h"
#include "card.h"

enum class gameStateNumber { def, quit, menu, singlePlayerSettings, singlePlayer, endgame, setSuit, setFigure, resume };

class gameState
{
	static int amountOfPlayers;
	static std::string playerName;

	public:
		static void setAmountOfPlayers(int amount);
		static int getAmountOfPlayers();
		static void setPlayerName(std::string name);
		static std::string getPlayerName();
		virtual void setCurrentSuit(suitNumber _suit) {};
		virtual void setCurrentFigure(figureNumber _figure) {};
		sf::Vector2f getMousePos(sf::RenderWindow& window);
		virtual AI* getAI(int number);
		virtual int getWon();
		virtual gameStateNumber update(sf::Event event, sf::RenderWindow& Window) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
};

