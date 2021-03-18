#include "liczbaZespolona.h"

liczbaZespolona::liczbaZespolona(double _Re, double _Im)
{
	Re = _Re;
	Im = _Im;
}

double liczbaZespolona::getRe()
{
	return Re;
}

double liczbaZespolona::getIm()
{
	return Im;
}

bool liczbaZespolona::operator<(const liczbaZespolona& z)
{
	if (sqrt(Re * Re + Im * Im) < sqrt(z.Re * z.Re + z.Im * z.Im))
		return true;
	else return false;
}
