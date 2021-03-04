#pragma once
#include "Nabywca.h"
class Hurt :
    virtual public Nabywca
{
public:
    void sprzedaz();
    int get();
    virtual ~Hurt() = default;
};

