#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <random>
#include <chrono> 

#include "liczbaZespolona.h"

template<class T>
void wypisz(std::vector<T> vec)
{
	for (auto i = vec.begin(); i < vec.end(); i++)
		std::cout << (*i) << " ";
	std::cout << std::endl;
}

void wypiszZespolona(liczbaZespolona z)
{
	std::cout << z.getRe() << ' ' << z.getIm() << 'i' << std::endl;
}

int main()
{

	//zad 1

	srand(time(NULL));
	std::vector<int> vec;
	for (int i = 0; i < rand() % 20; i++)
		vec.push_back(i);

	wypisz(vec);

	//zad 2

	std::cout << std::endl;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
	wypisz(vec);

	std::sort(vec.begin(), vec.end());
	wypisz(vec);

	std::reverse(vec.begin(), vec.end());
	wypisz(vec);

	std::replace(vec.begin(), vec.end(), 0, 8);
	wypisz(vec);

	std::reverse(vec.begin(), vec.end());
	wypisz(vec);

	if (std::binary_search(vec.begin(), vec.end(), 4))
		std::fill(vec.begin(), vec.end(), 4);
	wypisz(vec);

	//zad 3

	std::vector<char> vec2;
	std::vector<std::string> vec3;
	vec2.push_back('q'); 
	vec2.push_back('w'); 
	vec2.push_back('e'); 
	vec2.push_back('r'); 
	vec2.push_back('t'); 
	vec2.push_back('y');
	vec3.push_back("Wplynalem na suchego przestwor oceanu,|"); 
	vec3.push_back("Woz nurza sie w zielonosc i jak lodka brodzi,|"); 
	vec3.push_back("Srod fali lak szumiacych, srod kwiatow powodzi,|"); 
	vec3.push_back("omijam koralowe ostrowy burzanu");
	std::sort(vec2.begin(), vec2.end());
	std::sort(vec3.begin(), vec3.end());
	wypisz(vec2);
	wypisz(vec3);
	//dla kontenerow przechowujacych char funkcja std::sort sortuje elementy wedlug ich wartosci kodu ASCII
	//dla kontenerow przechowujacych std::string funkcja std::sort sortuje elementy wedlug wartosci kodu ASCII pierwszego elementu tablicy znakow std::string

	//zad 4

	std::vector<liczbaZespolona> vec4;

	for (int i = 0; i < 10; i++)
	{
		liczbaZespolona z(rand() % 100, rand() % 100);
		vec4.push_back(z);
	}
	std::cout << std::endl;
	std::for_each(vec4.begin(), vec4.end(), wypiszZespolona);

	std::sort(vec4.begin(), vec4.end());
	std::cout << std::endl;
	std::for_each(vec4.begin(), vec4.end(), wypiszZespolona);
	//funckja std::sort w tym przypadku wykorzytuje przeciazony operator porownania klasy liczbaZespolona

	return (0);
}