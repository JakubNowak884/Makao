#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <locale>
#include <io.h>
#include <fcntl.h>
#include <sstream>
#include <codecvt>
#include <stdexcept>

class Resources
{
	std::unique_ptr<sf::Font> font;
	std::vector<std::unique_ptr<sf::Texture>> textures;
	std::vector<std::vector<std::wstring>> language;
	char languageVersion = 0;

public:
	void loadResources();
	void loadLanguage(std::string _language);
	sf::Font& getFont();
	const sf::Texture& getTexture(std::string texture);
	std::wstring getText(size_t gameState, size_t line);
	sf::Texture* getTexturePtr(std::string texture);
	char getLanguageVersion();
};

