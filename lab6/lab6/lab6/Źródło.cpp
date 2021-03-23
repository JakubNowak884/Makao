#include <memory>
#include <vector>
#include <time.h>

#include "centrum_handlowe.h"

void wypisz(std::vector<std::shared_ptr<int>> vec)
{
	for (std::vector<std::shared_ptr<int>>::iterator i = vec.begin(); i < vec.end(); i++)
		std::cout << *i << ' ';
	std::cout << std::endl;
}

void wypiszWartosci(std::vector<std::shared_ptr<int>> vec)
{
	for (std::vector<std::shared_ptr<int>>::iterator i = vec.begin(); i < vec.end(); i++)
		std::cout << **i << ' ';
	std::cout << std::endl;
}

int main()
{
	std::unique_ptr<centrum_handlowe>p1(new centrum_handlowe(20));
	std::unique_ptr<centrum_handlowe>p2 = std::make_unique<centrum_handlowe>(30);

	std::cout << p1->getLiczba_sklepow() << ' ' << p2->getLiczba_sklepow() << std::endl;

	//p1.release();
	//p2.release();
	//metoda release ustawia wskaznik na nullptr, ale nie usuwa obiektu

	//p1.reset();
	//p2.reset();
	//metoda reset usuwa obiekt pod wskazanym adresem

	swap(p1, p2);
	std::cout << p1->getLiczba_sklepow() << ' ' << p2->getLiczba_sklepow() << std::endl;
	
	//p1 = p2;
	//nie mozna przypisac dwoch wskaznikow typu unique do tej samej wartosci

	p2 = move(p1);
	std::cout << p2->getLiczba_sklepow() << std::endl;
	//funkcja move przenosi obiekt spod wskaznika p1 na adres wskaznika p2, a nastepnie ustawia wskaznik p1 na nullptr
	//powoduje to wyciek pamieci, poniewaz obiekt, ktory byl pod adresem wskaznika p1 nie zostaje usuniety

	srand(time(NULL));

	std::vector<std::shared_ptr<int>> vec;

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<int> temp = std::make_shared<int>(rand() % 100);
		vec.push_back(temp);
	}

	wypisz(vec);
	wypiszWartosci(vec);

	std::shared_ptr<int> sp1 = vec[5];
	std::shared_ptr<int> sp2 = vec[5];
	std::shared_ptr<int> sp3 = vec[5];
	std::weak_ptr<int> wp1 = vec[5];

	std::cout << wp1.owner_before(vec[5]) << std::endl;
	
	std::cout << "Do adresu przechowujacego wartosc: ";
	auto sp4 = wp1.lock();
	std::cout << *sp4;
	std::cout << " przypisane jest " << wp1.use_count() << " wskaznikow" << std::endl;
	//weak.lock wynosi 0 (weak_ptr przestaje istniec) gdy use_count wynosi 0
	//dla wskaznika shared lepiej uzyc release, poniewaz obiekt pod danym adresem moze byc wspoldzielony przez inne wskazniki shared

	return (0);
}