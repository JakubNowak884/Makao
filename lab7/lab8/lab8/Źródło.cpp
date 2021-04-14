#include <iostream>
#include <vector>
#include <regex>

int main()
{
	//zad 1

	std::vector<std::string> vec = { "aaaa", "aa", "baa", "aba", "abababaabab" };
	std::regex reg("aa");

	for (auto i = vec.begin(); i != vec.end(); i++)
	{
		if (std::regex_search((*i), reg))
			std::cout << "Napis zawierajacy podwojne a: " << (*i) << std::endl;
	}
	for (auto i = vec.begin(); i != vec.end(); i++)
	{
		if (std::regex_match((*i), reg))
			std::cout << "Napis bedacy podwojnym a: " << (*i) << std::endl;
	}
	
	//zad 2

	std::regex reg2("(([0]{2}|[1-2]{1}|[1]{1}[0-9]{1}|[2][0-4]{1})[:]{1}[0-5]{1}[0-9]{1})");

	while (true)
	{
		std::cout << "Podaj godzine:\n";
		std::string godzina;
		std::cin >> godzina;
		if (std::regex_match(godzina, reg2))
		{
			std::cout << "Podana godzina: " << godzina << std::endl;
			break;
		}
		else
			std::cout << "Niepoprawna godzina" << std::endl;
	}
	
	//zad 3

	std::regex reg3("([A-Za-z0-9]{5,})(@{1})([A-Za-z0-9]{1,})(.{1})([a-z]{2,3})");
	std::smatch dopasowania;

	while (true)
	{
		std::cout << "Podaj email:\n";
		std::string email;
		std::cin >> email;
		if (std::regex_match(email, dopasowania, reg3))
		{
			std::cout << "Podany email: " << email << " zostal zalozony na poczcie: " << dopasowania[3] << std::endl;
			break;
		}
		else
			std::cout << "Niepoprawny email" << std::endl;
	}
	
	//zad 4

	std::string phoneNumbers = "023 456 789, 223-111-555, 666 666 666, 999-999-999";

	std::regex reg4("([1-9]{1}[0-9]{2}[- ]{1}[0-9]{3}[- ]{1})[0-9]{3}");

	std::string str = std::regex_replace(phoneNumbers, reg4, "nr_telefonu");
	std::cout << str << std::endl;

	//zad 5

	std::string str2 = "Wzorzec opisujacy lancuch symboli. Teoria wyrazen regularnych jest zwiazana z teoria jezykow regularnych. Wyrazenia regularne moga okreslac zbior pasujacych lancuchow, jak rowniez wyszczegolniac istotne czesci lancucha.";

	std::regex reg5("[A-Za-z,.]{1,}[eyuioa]{2}[A-Za-z,.]{1,}", std::regex_constants::icase);

	std::cout << "Ilosc slow z przynajmniej dwiema samogloskami obok siebie: " << std::distance(std::sregex_iterator(str2.begin(), str2.end(), reg5), std::sregex_iterator()) << std::endl;

	return 0;
}