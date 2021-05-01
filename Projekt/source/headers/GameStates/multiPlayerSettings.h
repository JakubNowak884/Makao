#pragma once
#include "gameState.h"
class multiPlayerSettings :
	public gameState
{
	sf::Font font;

	sf::Text text;

	std::string IP_LAN = "192.168.100.53";
	std::string IP_Online = "100.100.100.100";

	std::unique_ptr<button> b_changeName;
	std::unique_ptr<button> b_changeIP_LAN;
	std::unique_ptr<button> b_changeIP_Online;

	std::unique_ptr<button> b_joinLAN;
	std::unique_ptr<button> b_createLAN;
	std::unique_ptr<button> b_joinOnline;
	std::unique_ptr<button> b_createOnline;
	std::unique_ptr<button> b_onlyQueens;

	bool settingIP_LAN = true;
	bool host = false;
	bool onlyQueens = false;

public:
	multiPlayerSettings(Resources* _resources);
	void setIP(char sign);
	bool getLAN();
	std::string getIP();
	bool getHost();
	bool getOnlyQueens();
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

