#pragma once

#include "button.h"
#include "AI.h"
#include "card.h"

enum class gameStateNumber { def, quit, menu, instruction, changeName, singlePlayerSettings, singlePlayer, multiPlayer, multiPlayerSettings, changeIP, endgame, setSuit, setFigure, resume };

class gameState
{
	static std::string playerName;

	public:
		virtual ~gameState() {};
		//static
		static void setPlayerName(char sign);
		static std::string getPlayerName();
		//endgame
		virtual int getAmountOfPlayers();
		virtual AI* getAI(int number);
		virtual int getWon();
		//
		sf::Vector2f getMousePos(sf::RenderWindow& window);
		virtual gameStateNumber update(sf::Event event, sf::RenderWindow& Window) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
};

