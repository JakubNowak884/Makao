#include "Monitory.h"

void Monitory::dostawa()
{
	do_uregulowania -= 12000;
}

int Monitory::get()
{
	return do_uregulowania;
}
