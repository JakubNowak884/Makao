#pragma once

#include <iostream>
#include "bledna_dlugosc.h"
#include"bledne_znaki.h"

class Abonent
{
	float cenaAbonamentu, cenaTelefonu, doZaplaty;
	std::string numer;

public:
	Abonent()
		: cenaAbonamentu(0), cenaTelefonu(0), doZaplaty(0) {}
	~Abonent() {};

	friend void dodajAbonenta(Abonent* klienci[], int klient)
	{
		bledna_dlugosc dlugosc("Nieprawidlowa dlugosc numeru\n");
		bledne_znaki znaki("Nieprawidlowe znaki\n");

		std::cout << "Podaj cene abonamentu " << klient << " klienta: ";
		std::cin >> klienci[klient]->cenaAbonamentu;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			throw 1;
		}
		if (klienci[klient]->cenaAbonamentu <= 0) throw("Wartosc do zaplaty musi byc wieksza od 0\n");

		std::cout << "Podaj cene telefonu " << klient << " klienta: ";
		std::cin >> klienci[klient]->cenaTelefonu;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			throw 1;
		}
		if (klienci[klient]->cenaTelefonu <= 0) throw("Wartosc do zaplaty musi byc wieksza od 0\n");

		std::cout << "Podaj cene do zaplaty " << klient << " klienta: ";
		std::cin >> klienci[klient]->cenaTelefonu;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			throw 1;
		}
		if (klienci[klient]->cenaTelefonu <= 1000) throw std::out_of_range("Wartosc do zaplaty musi byc wieksza od 1000\n");

		std::cout << "Podaj numer " << klient << " klienta: ";
		std::cin >> klienci[klient]->numer;
		if (klienci[klient]->numer.length() < 9 || klienci[klient]->numer.length() > 9) throw dlugosc;
		for (size_t i = 0; i < klienci[klient]->numer.length(); i++) if (klienci[klient]->numer[i] < 48 || klienci[klient]->numer[i] > 57) throw znaki;
	}
};


