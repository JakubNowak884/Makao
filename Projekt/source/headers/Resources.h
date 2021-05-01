#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

class Resources
{
	std::unique_ptr<sf::Font> font;
	std::vector<std::unique_ptr<sf::Texture>> textures;

public:
	void loadResources();
	sf::Font& getFont();
	const sf::Texture& getTexture(std::string texture);
	sf::Texture* getTexturePtr(std::string texture);
};

