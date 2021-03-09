#pragma once
#include "numer_error.h"
class bledna_dlugosc :
    public numer_error
{
public:
    bledna_dlugosc(std::string _nazwa) { nazwa = _nazwa; }
};

