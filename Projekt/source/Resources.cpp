#include "headers/Resources.h"

void Resources::loadResources()
{
	std::ifstream file;
	file.open("..\\resources\\resources.txt");
	if (!file.is_open())
		throw("Resource file not found");
	std::string textureName;
	std::getline(file, textureName);
	font = std::make_unique<sf::Font>();
	if (!font->loadFromFile(textureName))
		throw("Font file not found");
	while (std::getline(file, textureName))
	{
		textures.push_back(std::make_unique<sf::Texture>());
		textures.back()->loadFromFile(textureName);
		if (!textures.back()->loadFromFile(textureName))
			throw("Texture files not found");
	}
	file.close();
}

void Resources::loadLanguage(std::string _language)
{
	for (auto i = language.begin(); i != language.end(); i++)
		i->clear();
	language.clear();
	std::wifstream file;
	file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	file.open("..\\resources\\language\\" + _language + ".txt");
	if (!file.is_open())
		throw("Language file not found");
	std::wstring temp;
	std::wstring text;
	std::getline(file, text);
	std::vector<std::wstring> vec;
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
	if (language[0].size() != 7 || language[1].size() != 5 || language[2].size() != 2 || language[3].size() != 7)
		throw("Language file incorrect format");
	if (language[5].size() != 14 || language[6].size() != 12 || language[7].size() != 2 || language[8].size() != 3)
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
