#pragma once

#include "../GUI/Button.h"
#include "../AI.h"
#include "../GUI/Card.h"

/**
	 * Typ wyliczeniowy u�ywany do zwracania obecnego stanu gry dla maszyny stan�w oraz u�atwienia pobierania zasob�w z klasy Resources.
	 */
enum class gameStateNumber 
{ 
	def, 
	quit, 
	menu, 
	instruction, 
	changeName,
	singlePlayerSettings, 
	singlePlayer, 
	multiPlayer,
	multiPlayerSettings, 
	changeIP, 
	endgame, 
	wantSuit, 
	wantFigure, 
	game, 
	AI, 
	resume 
};

class GameState
{
	static std::wstring playerName;				/*!< Nazwa gracza wy�wietlana w g��wnym menu oraz podczas gry. */

	protected:
		std::shared_ptr<Resources> resources;	/*!< Wska�nik na obiekt klasy przechowuj�cy zasoby gry. */

	public:
		/**
		   * \brief Konstruktor jednoargumentowy.
		   * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
		   */
		GameState(std::shared_ptr<Resources> _resources);
		virtual ~GameState() {};
		/**
		   * \brief Funkcja pojedynczo dodaje (lub odejmuje je�li znak to backspace) znaki do nazwy gracza.
		   * \param sign wpisany na klawiaturze znak.
		   */
		static void setPlayerName(char sign);
		static std::wstring getPlayerName();
		/**
		   * \brief Funkcja zwracaj�ca pozycje myszy na ekranie.
		   * \param window okno gry.
		   * \return pozycja myszy na ekranie.
		   */
		sf::Vector2f getMousePos(sf::RenderWindow& window);
		/**
		   * \brief Funkcja inicjalizuj�ca tekst.
		   * \param text tekst do inicjalizacji.
		   * \param poxX pozycja tekstu na osi X okna.
		   * \param posY pozycja tekstu na osi Y okna.
		   * \param size rozmiar tesktu.
		   * \param color kolor tekstu.
		   */
		void initText(sf::Text& text, float posX, float posY, int size, sf::Color color = sf::Color::White);
		/**
		   * \brief Czysto wirtualna funkcja, wywo�ywana w g��wnej p�tli gry przez klasy potomne, aktualizuj�ca obecny stan gry.
		   * \param event wydarzenie zainicjowane przez u�ytkownika.
		   * \param window okno gry.
		   * \return nowy stan gry.
		   */
		virtual gameStateNumber update(sf::Event event, sf::RenderWindow& Window) = 0;
		/**
		   * \brief Czysto wirtualna funkcja, wywo�ywana w g��wnej p�tli gry przez klasy potomne, rysuj�ca na ekranie obecny stan gry.
		   * \param event wydarzenie zainicjowane przez u�ytkownika.
		   * \param window okno gry.
		   */
		virtual void draw(sf::RenderWindow& window) = 0;
};

