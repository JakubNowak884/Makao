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
	std::vector<std::unique_ptr<sf::Texture>> textures; /*!< Wektor tesktur wczytywanych z plik�w. */
	std::vector<std::vector<std::wstring>> language;	/*!< Wektor przechowuj�cy odpowiadaj�ce poszczeg�lnym stanom gry wektory napis�w wy�wietlanych w grze. */
	char languageVersion = 0;							/*!< Wersja j�zykowa gry. */

public:
	/**
	  * \brief Funkcja wczytuj�ca zasoby z pliku.
	  */
	void loadResources();
	/**
	  * \brief Funkcja wczytuj�ca napisu z pliku.
	  * \param _language okre�lenie z jakiego pliku maj� zosta� wczytane napisy.
	  */
	void loadLanguage(std::string _language);
	sf::Font& getFont();
	const sf::Texture& getTexture(std::string texture);
	/**
	  * \brief Funkcja zwracaj�ca odpowiedni tekst.
	  * \param gameState okre�la kt�ry wektor z wektora wektor�w ma zosta� zwr�cony.
	  * \param line okre�la kt�ry element wektora ma zosta� zwr�cony.
	  * \return napis do wy�wietlenia w grze.
	  */
	std::wstring getText(size_t gameState, size_t line);
	sf::Texture* getTexturePtr(std::string texture);
	char getLanguageVersion();
};

