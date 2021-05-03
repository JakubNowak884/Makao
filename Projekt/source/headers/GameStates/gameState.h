#pragma once

#include "../GUI/Button.h"
#include "../AI.h"
#include "../GUI/Card.h"

enum class gameStateNumber { def, quit, menu, instruction, changeName, singlePlayerSettings, singlePlayer, multiPlayer, multiPlayerSettings, changeIP, endgame, setSuit, setFigure, game, AI, resume };

class Resources;
class GameState
{
	static std::wstring playerName;

	protected:
		Resources* resources;

	public:
		GameState(Resources* _resources)
			: resources(_resources) {}
		virtual ~GameState() {};
		//static
		static void setPlayerName(char sign);
		static std::wstring getPlayerName();
		//
		sf::Vector2f getMousePos(sf::RenderWindow& window);
		void initText(sf::Text& text, float posX, float posY, int size, sf::Color color = sf::Color::White);
		virtual gameStateNumber update(sf::Event event, sf::RenderWindow& Window) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
};

