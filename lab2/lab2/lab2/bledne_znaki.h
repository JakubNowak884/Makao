#pragma once
#include "numer_error.h"
class bledne_znaki :
    public numer_error
{
public:
    bledne_znaki(std::string _nazwa) { nazwa = _nazwa; }
};

