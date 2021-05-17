#pragma once

#include <vector>
#include <list>
#include <string>

#include "GUI\Card.h"
#include "..\headers\Resources.h"

class AI
{
	/**
	 * Struktura reprezentuj�ca mo�liwe do za��dania kolory lub figury.
	 * U�ywana do zliczania ich ilo�ci w wektorze zagranych kart, a nast�pnie znalezienia najwi�kszej ilo�ci zagranego koloru lub figury.
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
	 * Struktura reprezentuj�ca zagran� kart�, u�ywana do zapami�tywania przez gracza komputerowego zagranych przez poszczeg�lnych graczy kart.
	 */
	struct cardPlayed
	{
		cardPlayed(suitNumber _suit, figureNumber _figure)
			: suit(_suit), figure(_figure) {}
		suitNumber suit;
		figureNumber figure;
	};

	std::shared_ptr<Resources> resources;					/*!< Wska�nik na obiekt klasy przechowuj�cy zasoby gry. */

	std::unique_ptr<Object> cardBack = nullptr;				/*!< Obiekt reprezentuj�cy rewers kart gracza komputerowego. */
	sf::Text info;											/*!< Informacje o graczu komputerowym. */
	std::vector<std::shared_ptr<Card>> hand;				/*!< Wektor przechowuj�cy karty gracza komputerowego. */
	std::list<std::unique_ptr<cardPlayed>> cardsPlayed;		/*!< Lista przechowuj�ca informacje o kartach zagranych w ci�gu rozgrywki. */

	int ID;													/*!< Identyfikator gracza komputerowego. */
	int won;												/*!< Zmienna informuj�ca o zaj�tym przez gracz komputerowego miejscu. */
	int delay;												/*!< Op�nienie gracza komputerowego. */
	bool second = false;									/*!< Informacja czy gracz komputerowy zagra� ju� kart� w swojej turze. */

public:
	/**
		* \brief Konstruktor wieloargumentowy.
		* \param deck talia kart.
		* \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
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
		* \brief Funkcja symuluj�ca ��danie koloru.
		* \return ��dany kolor.
		*/
	suitNumber wantSuit();
	/**
		* \brief Funkcja symuluj�ca ��danie figury.
		* \return ��dana figura.
		*/
	figureNumber wantFigure();
	/**
		* \brief Funkcja zapami�tywania zagranych kart.
		* 
		* Funkcja wpisuje do wektora kart� na �rodku sto�u po turze ka�dego z graczy.
		* \param suit kolor karty na �rodku sto�u.
		* \param figure figura karty na �rodku sto�u.
		*/
	void rememberCard(suitNumber suit, figureNumber figure);
	/**
		* \brief Funkcja sprawdzaj�ca czy gracz komputerowy ma w r�ce kart� mo�liw� do zagrania.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na gr� oddzia�uje aktualnie efekt kt�rej� z kart.
		* \param currentSuit aktualnie ��dany kolor.
		* \param currentFigure aktualnie ��dana figura.
		* \return true je�li gracz komputerowy posiada kart� do zagrania, false je�li nie posiada.
		*/
	bool hasACardAbleToPlay(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	/**
		* \brief Funkcja symuluj�ca zagranie karty.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na gr� oddzia�uje aktualnie efekt kt�rej� z kart.
		* \param currentSuit aktualnie ��dany kolor.
		* \param currentFigure aktualnie ��dana figura.
		* \return wska�nik na obiekt reprezentuj�cy zagran� kart�, nullptr je�li nic nie zagrano
		*/
	Card* playACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure);
	/**
		* \brief Funkcja symuluj�ca dobranie karty.
		* \param deck talia kart.
		* \param actionCardIsActive informacja czy na gr� oddzia�uje aktualnie efekt kt�rej� z kart.
		* \param currentSuit aktualnie ��dany kolor.
		* \param currentFigure aktualnie ��dana figura.
		* \param howMany informacja ile kart zostanie dobranych.
		* \return wska�nik na dobran� kart�, je�li zosta�a ona odrazu zagrana, inaczej nullptr
		*/
	Card* drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
	/**
		* \brief Funkcja rysuj�ca rewers i informacje o graczu komputerowym na ekranie.
		* \param window okno gry.
		*/
	void draw(sf::RenderWindow& window);
};

