#pragma once
#include "GameState.h"
class MultiPlayerSettings :
	public GameState
{
	sf::Text textSettings;							/*!< Tekst wyœwietlaj¹cy infromacje o ustawieniach gry. */

	std::string IP_LAN = "10.10.10.10";				/*!< IP u¿ywane do po³¹czeñ w lokalnej sieci. */
	std::string IP_Online = "100.100.100.100";		/*!< IP u¿ywane do po³¹czeñ w globalnej sieci. */

	std::unique_ptr<Button> b_changeName;			/*!< Przycisk przechodz¹cy do stanu zmiany nazwy gracza. */
	std::unique_ptr<Button> b_changeIP_LAN;			/*!< Przycisk przechodz¹cy do stanu zmiany lokalnego adresu IP. */
	std::unique_ptr<Button> b_changeIP_Online;		/*!< Przycisk przechodz¹cy do stanu zmiany globalnego adresu IP. */

	std::unique_ptr<Button> b_joinLAN;				/*!< Przycisk do³¹czenia do lokalnej rozgrywki. */
	std::unique_ptr<Button> b_createLAN;			/*!< Przycisk utworzenia lokalnej rozgrywki. */
	std::unique_ptr<Button> b_joinOnline;			/*!< Przycisk do³¹czenia do globalnej rogrywki. */
	std::unique_ptr<Button> b_createOnline;			/*!< Przycisk utworzenia globalnej rozgrywki. */
	std::unique_ptr<Button> b_menu;					/*!< Przycisk powrotu do menu gry. */
	std::unique_ptr<Button> b_onlyQueens;			/*!< Przycisk ustawiaj¹cy, czy talia w utworzonej rozgrywce bêdzie zawiera³a tylko królowe. */

	bool settingIP_LAN = true;						/*!< Zmienna informuj¹ca czy aktulnie ustawiane jest lub rozgrywka zosta³a rozpoczêta/utworzona z u¿yciem lokalnego adresu IP. */
	bool host = false;								/*!< Zmienna informuj¹ca czy gracz utworzy³ rozgrywkê. */
	bool onlyQueens = false;						/*!< Zmienna informuj¹ca czy talia w utworzonej rozgrywce ma zawieraæ tylko królowe. */

public:
	/**
	  * \see GameState::GameState(std::shared_ptr<Resources> _resources)
	  */
	MultiPlayerSettings(std::shared_ptr<Resources> _resources);
	/**
	  * \brief Funkcja pojedynczo dodaje (lub odejmuje jeœli znak to backspace) znaki do adresu IP.
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

