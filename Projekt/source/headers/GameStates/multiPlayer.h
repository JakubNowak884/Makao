#pragma once

#include "Game.h"
#include "MultiPlayerSettings.h"
#include "../AI.h"

/**
	 * Typ wyliczeniowy informuj�cy w jakim stanie aktualnie znajduje si� gra wielu graczy.
	 */
enum class multiPlayerState 
{ 
	lobby,
	game
};

class MultiPlayer :
	public Game
{
	MultiPlayerSettings* prev;								/*!< Wska�nik na obiekt poprzedniego stanu gry. */

	sf::Text textLobby;										/*!< Tekst wyswietlaj�cy informacje o lobby. */

	sf::TcpSocket guest1;									/*!< Po��czenie z graczem pierwszym. */
	sf::TcpSocket guest2;									/*!< Po��czenie z graczem drugim. */
	sf::TcpSocket guest3;									/*!< Po��czenie z graczem trzecim. */

	std::vector<std::unique_ptr<Object>> cardback;			/*!< Wektor rewers�w kart pozosta�ych graczy. */
	std::vector<sf::Text> infoPlayer;						/*!< Wektor informacji o pozosta�ych graczach. */
	std::string podium;										/*!< Napis zawieraj�cy informacje o graczach i zaj�tych przez nich miejscach. */

	sf::TcpListener listener;								/*!< Nas�uchuje na porcie 50002. */
	sf::Packet packet;										/*!< Pakiet, z kt�rego wczytywane s� odebrane dane. */

	std::unique_ptr<Button> b_addSlot;						/*!< Przycisk dodania miejsca na gracza. */
	std::unique_ptr<Button> b_deleteSlot;					/*!< Przycisk usuni�cia miejsca na gracza. */
	std::unique_ptr<Button> b_start;						/*!< Przycisk rozpocz�cia gry. */
	std::unique_ptr<Button> b_menu;							/*!< Przycisk powrotu do menu gry. */

	multiPlayerState state = multiPlayerState::lobby;		/*!< Zmienna informuj�ca w jakim stanie znajduje si� aktualnie gra. */
	int maxID = 1;											/*!< Zmienna informuj�ca ilu graczy aktualnie znajduje si� w grze. */
	bool waiting = false;									/*!< Zmienna informuj�ca czy gra znajduje si� aktualnie w stanie oczekiwania na do��czenie gracza. */
	bool myTurn = true;										/*!< Zmienna informuj�ca czy aktualna tura dotyczy gracza. */
	bool host = true;										/*!< Zmienna informuj�ca czy gracz jest za�o�ycielem gry. */

	int guest1Won = 0;										/*!< Zmienna informuj�ca czy pierwszy gracz-go�� wygra�. */
	int guest2Won = 0;										/*!< Zmienna informuj�ca czy drugi gracz-go�� wygra�. */
	int guest3Won = 0;										/*!< Zmienna informuj�ca czy trzeci gracz-go�� wygra�. */

public:
	/**
	   * \brief Konstruktor dwuargumentowy.
	   * \param _prev wska�nik na poprzedni stan gry.
	   * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
	   * \see GameState::GameState(std::shared_ptr<Resources> _resources)
	   */
	MultiPlayer(MultiPlayerSettings* _prev, std::shared_ptr<Resources> _resources);
	~MultiPlayer();
	/**
	   * \brief Funckja oczekuj�ca na do��czenie gracza.
	   * 
	   * Funkcja po do��czeniu gracza wysy�a mu informacje o aktualnej grze oraz talii, a nast�pnie odbiera od niego nazw� gracza oraz tali� pomniejszon� o 5 kart. 
	   * \param guest referencja na gniazdo go�cia.
	   */
	void listen(sf::TcpSocket& guest);
	/**
	   * \brief Funckja oczekuj�ca na rozpocz�cie rozgrywki.
	   * 
	   * Funkcja odbiera informacje o do��czeniu kolejnych graczy, opuszczeniu gry przez za�o�yciela oraz rozpocz�ciu rozgrywki.
	   */
	void waitForStart();
	/**
	   * \brief Funckja oczekuj�ca na dane o aktulnym stanie rozgrywki.
	   * \param guest referencja na gniazdo go�cia.
	   */
	void waitForData(sf::TcpSocket& guest);
	/**
	   * \brief Funckja przekazuj�ce dane o grze do pakietu.
	   * \param onlyDeckAndGameData zmienna informuj�ca czy maj� zosta� wys�ane tylko informacje o talii i grze, czy r�wnie� o graczach.
	   */
	sf::Packet putDataToSend(bool onlyDeckAndGameData = false);
	/**
	   * \brief Funckja czytaj�ca dane z odebranego pakietu.
	   * \param onlyDeckAndGameData zmienna informuj�ca czy maj� zosta� przeczytane tylko informacje o talii i grze, czy r�wnie� o graczach.
	   */
	void loadDataFromPacket(bool onlyDeckAndGameData = false);
	/**
	   * \brief Funckja inicjalizuj�ca informacje o graczach.
	   * 
	   * Funkcja w zale�no�ci od liczby graczy dodaje odpowiedni� ilo�� element�w do wektora rewers�w kart oraz do wektora informacji o graczach.
	   */
	void initializeInfo();
	std::string getPodium();
	/**
	  * \see GameState::update(sf::Event event, sf::RenderWindow& window)
	  */
	gameStateNumber update(sf::Event event, sf::RenderWindow& window);
	/**
		* \see GameState::draw(sf::RenderWindow& window)
		*/
	void draw(sf::RenderWindow& window);
};

