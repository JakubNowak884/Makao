#pragma once
#include "Dostawca.h"
class Komputery :
    virtual public Dostawca
{
public:
    void dostawa();
    int get();
    virtual ~Komputery() = default;
};

