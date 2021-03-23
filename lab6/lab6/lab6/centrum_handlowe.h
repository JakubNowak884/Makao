#pragma once

#include <iostream>

class centrum_handlowe
{
	int liczba_sklepow;

public:
	centrum_handlowe()
		: liczba_sklepow(0)
	{
		std::cout << "konstruktor bezargumentowy" << std::endl;
	}
	centrum_handlowe(int _liczba_sklepow)
		: liczba_sklepow(_liczba_sklepow)
	{
		std::cout << "konstruktor jednoargumentowy" << std::endl;
	}
	~centrum_handlowe()
	{
		std::cout << "destruktor" << std::endl;
	}

	int getLiczba_sklepow()
	{
		return liczba_sklepow;
	}

	void increment()
	{
		liczba_sklepow++;
		std::cout << "metoda incremect" << std::endl;
	}
};

