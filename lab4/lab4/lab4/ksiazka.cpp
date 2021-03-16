#include "ksiazka.h"

ksiazka::ksiazka(int _cena, std::string _tytul)
{
	cena = _cena;
	tytul = _tytul;
}

int ksiazka::getCena()
{
	return cena;
}

std::ostream& operator<<(std::ostream& ostream, const ksiazka& _ksiazka)
{
	ostream << "Tytul: " << _ksiazka.tytul << std::endl << "Cena: " << _ksiazka.cena << " zl" << std::endl << std::endl;
	return ostream;
}
