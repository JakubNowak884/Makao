#pragma once
#include "Firma.h"
class Dostawca :
    virtual public Firma
{
public:
    virtual void dostawa() = 0;
    int get();
    virtual ~Dostawca() = default;
};

