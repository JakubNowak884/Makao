#pragma once
#include "GameState.h"
class MultiPlayerSettings :
	public GameState
{
	sf::Text text;

	std::string IP_LAN = "192.168.100.53";
	std::string IP_Online = "100.100.100.100";

	std::unique_ptr<Button> b_changeName;
	std::unique_ptr<Button> b_changeIP_LAN;
	std::unique_ptr<Button> b_changeIP_Online;

	std::unique_ptr<Button> b_joinLAN;
	std::unique_ptr<Button> b_createLAN;
	std::unique_ptr<Button> b_joinOnline;
	std::unique_ptr<Button> b_createOnline;
	std::unique_ptr<Button> b_onlyQueens;

	bool settingIP_LAN = true;
	bool host = false;
	bool onlyQueens = false;

public:
	MultiPlayerSettings(Resources* _resources);
	void setIP(char sign);
	bool getLAN();
	std::string getIP();
	bool getHost();
	bool getOnlyQueens();
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

