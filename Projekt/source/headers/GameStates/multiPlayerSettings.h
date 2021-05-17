#pragma once
#include "GameState.h"
class MultiPlayerSettings :
	public GameState
{
	sf::Text textSettings;							/*!< Tekst wy�wietlaj�cy infromacje o ustawieniach gry. */

	std::string IP_LAN = "10.10.10.10";				/*!< IP u�ywane do po��cze� w lokalnej sieci. */
	std::string IP_Online = "100.100.100.100";		/*!< IP u�ywane do po��cze� w globalnej sieci. */

	std::unique_ptr<Button> b_changeName;			/*!< Przycisk przechodz�cy do stanu zmiany nazwy gracza. */
	std::unique_ptr<Button> b_changeIP_LAN;			/*!< Przycisk przechodz�cy do stanu zmiany lokalnego adresu IP. */
	std::unique_ptr<Button> b_changeIP_Online;		/*!< Przycisk przechodz�cy do stanu zmiany globalnego adresu IP. */

	std::unique_ptr<Button> b_joinLAN;				/*!< Przycisk do��czenia do lokalnej rozgrywki. */
	std::unique_ptr<Button> b_createLAN;			/*!< Przycisk utworzenia lokalnej rozgrywki. */
	std::unique_ptr<Button> b_joinOnline;			/*!< Przycisk do��czenia do globalnej rogrywki. */
	std::unique_ptr<Button> b_createOnline;			/*!< Przycisk utworzenia globalnej rozgrywki. */
	std::unique_ptr<Button> b_menu;					/*!< Przycisk powrotu do menu gry. */
	std::unique_ptr<Button> b_onlyQueens;			/*!< Przycisk ustawiaj�cy, czy talia w utworzonej rozgrywce b�dzie zawiera�a tylko kr�lowe. */

	bool settingIP_LAN = true;						/*!< Zmienna informuj�ca czy aktulnie ustawiane jest lub rozgrywka zosta�a rozpocz�ta/utworzona z u�yciem lokalnego adresu IP. */
	bool host = false;								/*!< Zmienna informuj�ca czy gracz utworzy� rozgrywk�. */
	bool onlyQueens = false;						/*!< Zmienna informuj�ca czy talia w utworzonej rozgrywce ma zawiera� tylko kr�lowe. */

public:
	/**
	  * \see GameState::GameState(std::shared_ptr<Resources> _resources)
	  */
	MultiPlayerSettings(std::shared_ptr<Resources> _resources);
	/**
	  * \brief Funkcja pojedynczo dodaje (lub odejmuje je�li znak to backspace) znaki do adresu IP.
	  * \param sign wpisany na klawiaturze znak.
	  */
	void setIP(char sign);
	bool getLAN();
	std::string getIP();
	bool getHost();
	bool getOnlyQueens();
	/**
	  * \see GameState::update(sf::Event event, sf::RenderWindow& window)
	  */
	gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
	/**
	  * \see GameState::draw(sf::RenderWindow& window)
	  */
	void draw(sf::RenderWindow& window) override;
};

