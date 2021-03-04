#include "Hurt.h"

void Hurt::sprzedaz()
{
	do_uregulowania += 25000;
}

int Hurt::get()
{
	return do_uregulowania;
}
