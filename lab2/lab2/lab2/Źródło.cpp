#include "Abonent.h"

int main()
{
	Abonent klient1, klient2, klient3, klient4, klient5;
	Abonent* klienci[5] = { &klient1, &klient2, &klient3, &klient4, &klient5 };

	bool blad;

	for (int i = 0; i < 5; i++)
	{
		blad = false;
		try
		{
			dodajAbonenta(klienci, i);
		}
		catch (const char* blad1)
		{
			std::cout << "Blad: " << blad1;
			blad = true;
		}
		catch (std::out_of_range& blad2)
		{
			std::cout << "Blad: " << blad2.what();
			blad = true;
		}
		catch (numer_error error)
		{
			std::cout << error.nazwa;
			blad = true;
		}
		catch (...)
		{
			std::cout << "Blad\n";
			blad = true;
		}
		if (blad) i--;
	}

	return (0);
}