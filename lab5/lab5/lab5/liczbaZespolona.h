#pragma once

#include <iostream>
#include <cmath>

class liczbaZespolona
{
	double Re;
	double Im;

public:
	liczbaZespolona(double _Re, double _Im);
	double getRe();
	double getIm();
	bool operator <(const liczbaZespolona& z);
};

