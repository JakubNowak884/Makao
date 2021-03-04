#pragma once
#include "Firma.h"
class Nabywca :
    virtual public Firma
{
public:
    virtual void sprzedaz() = 0;
    int get();
    virtual ~Nabywca() = default;
};

