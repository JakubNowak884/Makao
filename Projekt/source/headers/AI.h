#pragma once

#include <vector>
#include <list>
#include <string>

#include "GUI\Card.h"
#include "..\headers\Resources.h"

class AI
{
	/**
	 * Struktura reprezentuj¹ca mo¿liwe do za¿¹dania kolory lub figury.
	 * U¿ywana do zliczania ich iloœci w wektorze zagranych kart, a nastêpnie znalezienia najwiêkszej iloœci zagranego koloru lub figury.
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
	 * Struktura reprezentuj¹ca zagran¹ kartê, u¿ywana do zapamiêtywania przez gracza komputerowego zagranych przez poszczególnych graczy kart.
	 */
	struct cardPlayed
	{
		cardPlayed(suitNumber _suit, figureNumber _figure)
			: suit(_suit), figure(_figure) {}
		suitNumber suit;
		figureNumber figure;
	};

	std::shared_ptr<Resources> resources;					/*!< WskaŸnik na obiekt klasy przechowuj¹cy zasoby gry. */

	std::unique_ptr<Object> cardBack = nullptr;				/*!< Obiekt reprezentuj¹cy rewers kart gracza komputerowego. */
	sf::Text info;											/*!< Informacje o graczu komputerowym. */
	std::vector<std::shared_ptr<Card>> hand;				/*!< Wektor przechowuj¹cy karty gracza komputerowego. */
	std::list<std::unique_ptr<cardPlayed>> cardsPlayed;		/*!< Lista przechowuj¹ca informacje o kartach zagranych w ci¹gu rozgrywki. */

	int ID;													/*!< Identyfikator gracza komputerowego. */
	int won;												/*!< Zmienna informuj¹ca o zajêtym przez gracz komputerowego miejscu. */
	int delay;												/*!< OpóŸnienie gracza komputerowego. */
	bool second = false;									/*!< Informacja czy gracz komputerowy zagra³ ju¿ kartê w swojej turze. */

public:
	/**
		* \brief Konstruktor wieloargumentowy.
		* \param deck talia kart.
		* \param _resources wskaŸnik na obiekt klasy przechowuj¹cy zasoby gry.
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
		* \brief Funkcja symuluj¹ca ¿¹danie koloru.
		* \return ¿¹dany kolor.
		*/
	suitNumber wantSuit();
	/**
		* \brief Funkcja symuluj¹ca ¿¹danie figury.
		* \return ¿¹dana figura.
		*/
	figureNumber wantFigure();
	/**
		* \brief Funkcja zapamiêtywania zagranych kart.
		* 
		* Funkcja wpisuje do wektora kartê na œrodku sto³u po turze ka¿dego z graczy.
		* \param suit kolor karty na œrodku sto³u.
		* \param figure figura karty na œrodku sto³u.
		*/
	void rememberCard(suitNumber suit, figureNumber figure);
	/**
		* \brief Funkcja sprawdzaj¹ca czy gracz komputerowy ma w rêce kartê mo¿liw¹ do zagrania.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na grê oddzia³uje aktualnie efekt którejœ z kart.
		* \param currentSuit aktualnie ¿¹dany kolor.
		* \param currentFigure aktualnie ¿¹dana figura.
		* \return true jeœli gracz komputerowy posiada kartê do zagrania, false jeœli nie posiada.
		*/
	bool hasACardAbleToPlay(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	/**
		* \brief Funkcja symuluj¹ca zagranie karty.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na grê oddzia³uje aktualnie efekt którejœ z kart.
		* \param currentSuit aktualnie ¿¹dany kolor.
		* \param currentFigure aktualnie ¿¹dana figura.
		* \return wskaŸnik na obiekt reprezentuj¹cy zagran¹ kartê, nullptr jeœli nic nie zagrano
		*/
	Card* playACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	/**
		* \brief Funkcja symuluj¹ca dobranie karty.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na grê oddzia³uje aktualnie efekt którejœ z kart.
		* \param currentSuit aktualnie ¿¹dany kolor.
		* \param currentFigure aktualnie ¿¹dana figura.
		* \param howMany informacja ile kart zostanie dobranych.
		* \return wskaŸnik na dobran¹ kartê, jeœli zosta³a ona odrazu zagrana, inaczej nullptr
		*/
	Card* drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
	/**
		* \brief Funkcja rysuj¹ca rewers i informacje o graczu komputerowym na ekranie.
		* \param window okno gry.
		*/
	void draw(sf::RenderWindow& window);
};

