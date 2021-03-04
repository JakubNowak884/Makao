#include "Komputery.h"
#include "Monitory.h"
#include "Detal.h"
#include "Hurt.h"
#include <time.h>
#include <iostream>

int main()
{
	Firma** firmy = new Firma*[8];

	firmy[0] = new Komputery();
	firmy[1] = new Komputery();
	firmy[2] = new Monitory();
	firmy[3] = new Monitory();
	firmy[4] = new Hurt();
	firmy[5] = new Hurt();
	firmy[6] = new Detal();
	firmy[7] = new Detal();

	srand(time(NULL));

	int saldo = 0;

	for (int i = 0; i < 8; i++)
	{
		std::string nazwaKlasy = typeid(*firmy[i]).name();
		nazwaKlasy.erase(0, 6); //usuniecie ciagu znakow "class "
		int r = rand() % 4; //losowanie ile razy ma zostac wywolana funckja dostawa() lub sprzedaz()
		Dostawca* dostawca1 = dynamic_cast<Dostawca*>(firmy[i]);
		if (dostawca1 != nullptr)
		{
			for (int i = 0; i < r; i++)
			{
				dostawca1->dostawa();
			}
			std::cout << "Dostawca - " << nazwaKlasy << ": " << dostawca1->get() << std::endl;
			saldo += dostawca1->get();
		}

		else
		{
			Nabywca* nabywca1 = dynamic_cast<Nabywca*>(firmy[i]);
			if (nabywca1 != nullptr)
			{
				for (int i = 0; i < r; i++)
				{
					nabywca1->sprzedaz();
				}
				std::cout << "Nabywca - " << nazwaKlasy << ": " << nabywca1->get() << std::endl;
				saldo += nabywca1->get();
			}
		}
	}

	std::cout << "Saldo centrum logistycznego: " << saldo;

	//czyszczenie pamieci po programie

	for (int i = 0; i < 8; i++)
	{
		delete firmy[i];
	}

	delete[] firmy;

	getchar();

	return 0;
}