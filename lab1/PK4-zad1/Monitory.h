#pragma once
#include "Dostawca.h"
class Monitory :
    virtual public Dostawca
{
public:
    void dostawa();
    int get();
    virtual ~Monitory() = default;
};

