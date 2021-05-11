#pragma once

#include "Game.h"
#include "MultiPlayerSettings.h"
#include "../AI.h"

/**
	 * Typ wyliczeniowy informuj¹cy w jakim stanie aktualnie znajduje siê gra wielu graczy.
	 */
enum class multiPlayerState 
{ 
	lobby,
	game
};

class MultiPlayer :
	public Game
{
	MultiPlayerSettings* prev;								/*!< WskaŸnik na obiekt poprzedniego stanu gry. */

	sf::Text textLobby;										/*!< Tekst wyswietlaj¹cy informacje o lobby. */

	sf::TcpSocket guest1;									/*!< Po³¹czenie z graczem pierwszym. */
	sf::TcpSocket guest2;									/*!< Po³¹czenie z graczem drugim. */
	sf::TcpSocket guest3;									/*!< Po³¹czenie z graczem trzecim. */

	std::vector<std::unique_ptr<Object>> cardback;			/*!< Wektor rewersów kart pozosta³ych graczy. */
	std::vector<sf::Text> infoPlayer;						/*!< Wektor informacji o pozosta³ych graczach. */
	std::string podium;										/*!< Napis zawieraj¹cy informacje o graczach i zajêtych przez nich miejscach. */

	sf::TcpListener listener;								/*!< Nas³uchuje na porcie 50002. */
	sf::Packet packet;										/*!< Pakiet, z którego wczytywane s¹ odebrane dane. */

	std::unique_ptr<Button> b_addSlot;						/*!< Przycisk dodania miejsca na gracza. */
	std::unique_ptr<Button> b_deleteSlot;					/*!< Przycisk usuniêcia miejsca na gracza. */
	std::unique_ptr<Button> b_start;						/*!< Przycisk rozpoczêcia gry. */
	std::unique_ptr<Button> b_menu;							/*!< Przycisk powrotu do menu gry. */

	multiPlayerState state = multiPlayerState::lobby;		/*!< Zmienna informuj¹ca w jakim stanie znajduje siê aktualnie gra. */
	int maxID = 1;											/*!< Zmienna informuj¹ca ilu graczy aktualnie znajduje siê w grze. */
	bool waiting = false;									/*!< Zmienna informuj¹ca czy gra znajduje siê aktualnie w stanie oczekiwania na do³¹czenie gracza. */
	bool myTurn = true;										/*!< Zmienna informuj¹ca czy aktualna tura dotyczy gracza. */
	bool host = true;										/*!< Zmienna informuj¹ca czy gracz jest za³o¿ycielem gry. */

	int guest1Won = 0;										/*!< Zmienna informuj¹ca czy pierwszy gracz-goœæ wygra³. */
	int guest2Won = 0;										/*!< Zmienna informuj¹ca czy drugi gracz-goœæ wygra³. */
	int guest3Won = 0;										/*!< Zmienna informuj¹ca czy trzeci gracz-goœæ wygra³. */

public:
	/**
	   * \brief Konstruktor dwuargumentowy.
	   * \param _prev wskaŸnik na poprzedni stan gry.
	   * \param _resources wskaŸnik na obiekt klasy przechowuj¹cy zasoby gry.
	   * \see GameState::GameState(std::shared_ptr<Resources> _resources)
	   */
	MultiPlayer(MultiPlayerSettings* _prev, std::shared_ptr<Resources> _resources);
	~MultiPlayer();
	/**
	   * \brief Funckja oczekuj¹ca na do³¹czenie gracza.
	   * 
	   * Funkcja po do³¹czeniu gracza wysy³a mu informacje o aktualnej grze oraz talii, a nastêpnie odbiera od niego nazwê gracza oraz taliê pomniejszon¹ o 5 kart. 
	   * \param guest referencja na gniazdo goœcia.
	   */
	void listen(sf::TcpSocket& guest);
	/**
	   * \brief Funckja oczekuj¹ca na rozpoczêcie rozgrywki.
	   * 
	   * Funkcja odbiera informacje o do³¹czeniu kolejnych graczy, opuszczeniu gry przez za³o¿yciela oraz rozpoczêciu rozgrywki.
	   */
	void waitForStart();
	/**
	   * \brief Funckja oczekuj¹ca na dane o aktulnym stanie rozgrywki.
	   * \param guest referencja na gniazdo goœcia.
	   */
	void waitForData(sf::TcpSocket& guest);
	/**
	   * \brief Funckja przekazuj¹ce dane o grze do pakietu.
	   * \param onlyDeckAndGameData zmienna informuj¹ca czy maj¹ zostaæ wys³ane tylko informacje o talii i grze, czy równie¿ o graczach.
	   */
	sf::Packet putDataToSend(bool onlyDeckAndGameData = false);
	/**
	   * \brief Funckja czytaj¹ca dane z odebranego pakietu.
	   * \param onlyDeckAndGameData zmienna informuj¹ca czy maj¹ zostaæ przeczytane tylko informacje o talii i grze, czy równie¿ o graczach.
	   */
	void loadDataFromPacket(bool onlyDeckAndGameData = false);
	/**
	   * \brief Funckja inicjalizuj¹ca informacje o graczach.
	   * 
	   * Funkcja w zale¿noœci od liczby graczy dodaje odpowiedni¹ iloœæ elementów do wektora rewersów kart oraz do wektora informacji o graczach.
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

