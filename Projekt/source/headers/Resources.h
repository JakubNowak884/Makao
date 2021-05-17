#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <locale>
#include <stdexcept>

class Resources
{
	std::unique_ptr<sf::Font> font;						/*!< Font wczytywany z pliku. */
	std::vector<std::unique_ptr<sf::Texture>> textures; /*!< Wektor tesktur wczytywanych z plików. */
	std::vector<std::vector<std::wstring>> language;	/*!< Wektor przechowuj¹cy odpowiadaj¹ce poszczególnym stanom gry wektory napisów wyœwietlanych w grze. */
	char languageVersion = 0;							/*!< Wersja jêzykowa gry. */

public:
	/**
	  * \brief Funkcja wczytuj¹ca zasoby z pliku.
	  */
	void loadResources();
	/**
	  * \brief Funkcja wczytuj¹ca napisu z pliku.
	  * \param _language okreœlenie z jakiego pliku maj¹ zostaæ wczytane napisy.
	  */
	void loadLanguage(std::string _language);
	sf::Font& getFont();
	const sf::Texture& getTexture(std::string texture);
	/**
	  * \brief Funkcja zwracaj¹ca odpowiedni tekst.
	  * \param gameState okreœla który wektor z wektora wektorów ma zostaæ zwrócony.
	  * \param line okreœla który element wektora ma zostaæ zwrócony.
	  * \return napis do wyœwietlenia w grze.
	  */
	std::wstring getText(size_t gameState, size_t line);
	sf::Texture* getTexturePtr(std::string texture);
	char getLanguageVersion();
};

