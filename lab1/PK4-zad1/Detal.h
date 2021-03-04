#pragma once
#include "Nabywca.h"
class Detal :
    virtual public Nabywca
{
public:
    void sprzedaz();
    int get();
    virtual ~Detal() = default;
};

