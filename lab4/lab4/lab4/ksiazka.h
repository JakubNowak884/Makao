#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <time.h>

class ksiazka
{
protected:
	int cena;
	std::string tytul;

public:
	ksiazka(int _cena, std::string _tytul);
	int getCena();
	friend std::ostream& operator<<(std::ostream& ostream, const ksiazka& _ksiazka);
};

