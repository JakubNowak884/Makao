#include "headers/Resources.h"

void Resources::loadResources()
{
	//otworzenie pliku z sciezkami do fontu oraz tekstur
	std::ifstream file;
	file.open("..\\resources\\resources.txt");
	if (!file.is_open())
		throw("Resource file not found");
	//utworzenie sciezki do fontu, utworzenie obiektu font, wczytanie fontu spod sciezki
	std::string textureName;
	std::getline(file, textureName);
	font = std::make_unique<sf::Font>();
	if (!font->loadFromFile(textureName))
		throw("Font file not found");
	//wczytywanie sciezek do tesktur, zapisywanie tekstur do wektora, wczytywanie tekstur spod sciezki
	while (std::getline(file, textureName))
	{
		textures.push_back(std::make_unique<sf::Texture>());
		if (!textures.back()->loadFromFile(textureName))
			throw("Texture files not found");
	}
	file.close();
}

void Resources::loadLanguage(std::string _language)
{
	//zmienna sprawdzajaca kompatybilnosc wersji jezykowych w grze wielu graczy, bedaca pierwsza litera podanej wersji jezykowej
	languageVersion = _language[0];
	//czyszczenie wektora przechowujacego napisy w grze
	for (auto i = language.begin(); i != language.end(); i++)
		i->clear();
	language.clear();
	//umo�liwienie wczytania polskich znak�w
	std::wifstream file;
	file.imbue(std::locale("en_US.UTF-8"));
	file.open("..\\resources\\language\\" + _language + ".txt");
	if (!file.is_open())
		throw("Language file not found");
	std::wstring temp;
	std::wstring text;
	std::getline(file, text);
	std::vector<std::wstring> vec;
	//ka�dy # oznacza inny stan gry, wi�c jest zapisywany do innego wektora
	//poszczeg�lne linie w pliku s� oddzielone �rednikiem
	while (std::getline(file, temp))
	{
		if (temp.front() == '#')
		{
			language.push_back(vec);
			vec.clear();
			continue;
		}
		text = temp;
		while (temp.back() != ';')
		{
			std::getline(file, temp);
			text += '\n';
			text += temp;
		}
		text.erase(text.length() - 1);
		vec.push_back(text);
	}
	//sprawdzenie czy plik j�zykowy zawiera� poprawn� liczb� stan�w gry oddzielonych # oraz linii
	if (language[0].size() != 7 || language[1].size() != 5 || language[2].size() != 2 || language[3].size() != 7)
		throw("Language file incorrect format");
	if (language[5].size() != 15 || language[6].size() != 12 || language[7].size() != 2 || language[8].size() != 3)
		throw("Language file incorrect format");
	if (language[9].size() != 5 || language[10].size() != 7 || language[11].size() != 17 || language[12].size() != 3)
		throw("Language file incorrect format");
	file.close();
}

sf::Font& Resources::getFont()
{
	return *font.get();
}

const sf::Texture& Resources::getTexture(std::string texture)
{
	if (texture == "button")
		return *textures[0].get();
	else if (texture == "deck")
		return *textures[1].get();
	else
		return *textures[2].get();
}

std::wstring Resources::getText(size_t gameState, size_t line)
{
	return language[gameState - 2][line - 1];
}

sf::Texture* Resources::getTexturePtr(std::string texture)
{
	if (texture == "button")
		return textures[0].get();
	else if (texture == "deck")
		return textures[1].get();
	else
		return textures[2].get();
}

char Resources::getLanguageVersion()
{
	return languageVersion;
}
