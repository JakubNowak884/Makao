#pragma once

#include "../GUI/button.h"
#include "../AI.h"
#include "../GUI/card.h"
#include "../Resources.h"

enum class gameStateNumber { def, quit, menu, instruction, changeName, singlePlayerSettings, singlePlayer, multiPlayer, multiPlayerSettings, changeIP, endgame, setSuit, setFigure, resume };

class gameState
{
	static std::string playerName;

	protected:
		Resources* resources;

	public:
		gameState(Resources* _resources)
			: resources(_resources) {}
		virtual ~gameState() {};
		//static
		static void setPlayerName(char sign);
		static std::string getPlayerName();
		//
		sf::Vector2f getMousePos(sf::RenderWindow& window);
		virtual gameStateNumber update(sf::Event event, sf::RenderWindow& Window) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
};

