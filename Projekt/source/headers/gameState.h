#pragma once

#include "button.h"
#include "AI.h"
#include "card.h"

enum class gameStateNumber { def, quit, menu, changeName, singlePlayerSettings, singlePlayer, mutliPlayer, multiPlayerSettings, changeIP, endgame, setSuit, setFigure, resume };

class gameState
{
	static int amountOfPlayers;
	static std::string playerName;

	public:
		static void setAmountOfPlayers(int amount);
		static int getAmountOfPlayers();
		static void setPlayerName(std::string name);
		static void setPlayerName(char sign);
		static std::string getPlayerName();
		virtual void setCurrentSuit(suitNumber _suit) {};
		virtual void setCurrentFigure(figureNumber _figure) {};
		virtual void setIP(char sign) {};
		virtual std::string getIP() { return "Placeholder"; };
		virtual bool getHost() { return false; };
		sf::Vector2f getMousePos(sf::RenderWindow& window);
		virtual AI* getAI(int number);
		virtual int getWon();
		virtual gameStateNumber update(sf::Event event, sf::RenderWindow& Window) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
};
