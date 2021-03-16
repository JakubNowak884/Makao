#include "ksiazka.h"

int main()
{
	//zad 1

	srand(time(NULL));

	std::vector<ksiazka*> vec;
	
	for (int i = 0; i < 10; i++)
	{
		int cena = rand() % 100;
		std::string nazwa = "Ksiazka nr " + std::to_string(rand() % 100);
		ksiazka* _ksiazka = new ksiazka(cena, nazwa);
		vec.push_back(_ksiazka);
	}

	for (int i = 0; i < 10; i++)
	{
		std::cout << (*vec[i]);
	}

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (vec[j]->getCena() > vec[j + 1]->getCena())
			{
				ksiazka* temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << (*vec[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		delete vec[i];
	}

	//zad 2

	std::set<int> set1;
	std::multiset<int> set2;

	for (int i = 0; i < 10; i++)
	{
		int r = rand() % 10;
		set1.insert(r);
		set2.insert(r);
	}

	std::cout << "Ilosc elementow w set: " << set1.size() << std::endl;
	std::cout << "Ilosc elementow w multiset: " << set2.size() << std::endl;

	//zad 3

	std::vector<std::vector<int>> vec2;
	int rozmiar;

	std::cout << "Podaj rozmiar macierzy jednostkowej: ";
	std::cin >> rozmiar;

	for (int i = 0; i < rozmiar; i++)
	{
		std::vector<int> temp;
		for (int j = 0; j < rozmiar; j++)
		{
			if (i == j) temp.push_back(1);
			else temp.push_back(0);
		}
		vec2.push_back(temp);
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			std::cout << vec2[i][j] << "	";
		}
		std::cout << std::endl;
	}

	return (0);
}