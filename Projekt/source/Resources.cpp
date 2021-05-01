#include "headers/Resources.h"

void Resources::loadResources()
{
	std::ifstream file;
	file.open("..\\resources\\resources.txt");
	std::string textureName;
	std::getline(file, textureName);
	font = std::make_unique<sf::Font>();
	font->loadFromFile(textureName);
	while (std::getline(file, textureName))
	{
		textures.push_back(std::make_unique<sf::Texture>());
		textures.back()->loadFromFile(textureName);
	}
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

sf::Texture* Resources::getTexturePtr(std::string texture)
{
	if (texture == "button")
		return textures[0].get();
	else if (texture == "deck")
		return textures[1].get();
	else
		return textures[2].get();
}
