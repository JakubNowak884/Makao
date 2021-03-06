#pragma once

#include <vector>
#include <list>
#include <string>

#include "GUI\Card.h"
#include "..\headers\Resources.h"

class AI
{
	/**
	 * Struktura reprezentująca możliwe do zażądania kolory lub figury.
	 * Używana do zliczania ich ilości w wektorze zagranych kart, a następnie znalezienia największej ilości zagranego koloru lub figury.
	 */
	struct howManyCards
	{
		howManyCards(suitNumber _suit)
			: suit(_suit), figure(figureNumber::null), howMany(0) {}
		howManyCards(figureNumber _figure)
			: figure(_figure), suit(suitNumber::null), howMany(0) {}

		suitNumber suit;
		figureNumber figure;
		int howMany;
		bool operator <(const howManyCards& obj)
		{
			if (howMany < obj.howMany)
				return true;
			else
				return false;
		}
	};
	/**
	 * Struktura reprezentująca zagraną kartę, używana do zapamiętywania przez gracza komputerowego zagranych przez poszczególnych graczy kart.
	 */
	struct cardPlayed
	{
		cardPlayed(suitNumber _suit, figureNumber _figure)
			: suit(_suit), figure(_figure) {}
		suitNumber suit;
		figureNumber figure;
	};

	std::shared_ptr<Resources> resources;					/*!< Wskaźnik na obiekt klasy przechowujący zasoby gry. */

	std::unique_ptr<Object> cardBack = nullptr;				/*!< Obiekt reprezentujący rewers kart gracza komputerowego. */
	sf::Text info;											/*!< Informacje o graczu komputerowym. */
	std::vector<std::shared_ptr<Card>> hand;				/*!< Wektor przechowujący karty gracza komputerowego. */
	std::list<std::unique_ptr<cardPlayed>> cardsPlayed;		/*!< Lista przechowująca informacje o kartach zagranych w ciągu rozgrywki. */

	int ID;													/*!< Identyfikator gracza komputerowego. */
	int won;												/*!< Zmienna informująca o zajętym przez gracz komputerowego miejscu. */
	int delay;												/*!< Opóźnienie gracza komputerowego. */
	bool second = false;									/*!< Informacja czy gracz komputerowy zagrał już kartę w swojej turze. */

public:
	/**
		* \brief Konstruktor wieloargumentowy.
		* \param deck talia kart.
		* \param _resources wskaźnik na obiekt klasy przechowujący zasoby gry.
		* \param _ID identyfikator gracza komputerowego.
		* \param onlyOne informacja czy rozgrywka zawiera tylko jednego gracza komputerowego.
		*/
	AI(std::list<std::shared_ptr<Card>>& deck, std::shared_ptr<Resources> _resources, int _ID, bool onlyOne = false);

	int getID();
	int getWon();
	int& getDelay();
	bool handEmpty();

	void setWon(int _won);
	void setDelay(int _delay);
	void setTextColor(sf::Color color);
	/**
		* \brief Funkcja symulująca żądanie koloru.
		* \return żądany kolor.
		*/
	suitNumber wantSuit();
	/**
		* \brief Funkcja symulująca żądanie figury.
		* \return żądana figura.
		*/
	figureNumber wantFigure();
	/**
		* \brief Funkcja zapamiętywania zagranych kart.
		* 
		* Funkcja wpisuje do wektora kartę na środku stołu po turze każdego z graczy.
		* \param suit kolor karty na środku stołu.
		* \param figure figura karty na środku stołu.
		*/
	void rememberCard(suitNumber suit, figureNumber figure);
	/**
		* \brief Funkcja sprawdzająca czy gracz komputerowy ma w ręce kartę możliwą do zagrania.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na grę oddziałuje aktualnie efekt którejś z kart.
		* \param currentSuit aktualnie żądany kolor.
		* \param currentFigure aktualnie żądana figura.
		* \return true jeśli gracz komputerowy posiada kartę do zagrania, false jeśli nie posiada.
		*/
	bool hasACardAbleToPlay(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	/**
		* \brief Funkcja symulująca zagranie karty.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na grę oddziałuje aktualnie efekt którejś z kart.
		* \param currentSuit aktualnie żądany kolor.
		* \param currentFigure aktualnie żądana figura.
		* \return wskaźnik na obiekt reprezentujący zagraną kartę, nullptr jeśli nic nie zagrano
		*/
	Card* playACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	/**
		* \brief Funkcja symulująca dobranie karty.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na grę oddziałuje aktualnie efekt którejś z kart.
		* \param currentSuit aktualnie żądany kolor.
		* \param currentFigure aktualnie żądana figura.
		* \param howMany informacja ile kart zostanie dobranych.
		* \return wskaźnik na dobraną kartę, jeśli została ona odrazu zagrana, inaczej nullptr
		*/
	Card* drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
	/**
		* \brief Funkcja rysująca rewers i informacje o graczu komputerowym na ekranie.
		* \param window okno gry.
		*/
	void draw(sf::RenderWindow& window);
};

