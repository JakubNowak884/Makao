#include "..\headers\GUI\card.h"

Card::Card(figureNumber _figure, suitNumber _suit, sf::Texture* texture, float _width, float _height, float _x, float _y)
	: figure(_figure), suit(_suit), Object(_width, _height, _x, _y, texture, sf::Color::White)
{
	//ustawienie odpowiedniego fragmentu obrazu jako teksturê karty
	getShape().setTextureRect(sf::IntRect((int(_figure) - 1) * 148, (int(_suit) - 1) * 230, 145, 230));

	frame.setSize(sf::Vector2f(_width + 20, _height + 20));
	frame.setOrigin(sf::Vector2f((_width + 20) / 2, (_height + 20) / 2));
	frame.setPosition(sf::Vector2f(_x, _y));
	frame.setFillColor(sf::Color::Green);
}

suitNumber Card::getSuit()
{
	return suit;
}

figureNumber Card::getFigure()
{
	return figure;
}

void Card::uptade(sf::Vector2f mousePos)
{
	Object::uptade(mousePos);
	if (isChosen() == true)
		setPosition(sf::Vector2f(getX(), 700));
	else 
		setPosition(sf::Vector2f(getX(), 800));
}

void Card::setPosition(sf::Vector2f position)
{
	Object::setPosition(position);
	frame.setPosition(position);
}

void Card::frameSetFillColor(sf::Color color)
{
	frame.setFillColor(color);
}

bool Card::ableToPlay(Card* current, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, bool second)
{
	bool suitMatches;
	if (current->getSuit() == getSuit()) 
		suitMatches = true; 
	else 
		suitMatches = false;

	bool figureMatches;
	if (current->getFigure() == getFigure()) 
		figureMatches = true;
	else 
		figureMatches = false;

	//sprawdzenie czy aktualnie na grê dzia³a efekt którejœ z kart
	if (actionCardIsActive)
	{
		switch (current->getFigure())
		{
		//na asa mo¿e zostaæ zagrany tylko inny as lub ¿¹dany przez niego kolor
		case figureNumber::ace:
			if (figureMatches || (getSuit() == currentSuit && !second))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		//na dwójkê/trójkê mo¿e zostaæ zagrana tylko dwójka/trójka lub trójka/dwójka odpowiadaj¹ca kolorem
		case figureNumber::two:
			if (figureMatches || (getFigure() == figureNumber::three && suitMatches && !second))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		case figureNumber::three:
			if (figureMatches || (getFigure() == figureNumber::two && suitMatches && !second))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		//na czwórkê mo¿na zagrac tylko czwórkê
		case figureNumber::four:
			if (figureMatches)
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		//na waleta mo¿na zagraæ tylko waleta lub ¿¹dan¹ przez niego figurê
		case figureNumber::jack:
			if (figureMatches || (getFigure() == currentFigure && !second))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		//na króla serce/pik mo¿na zagraæ tylko króla pik/serce
		case figureNumber::king:
			if (figureMatches && (getSuit() == suitNumber::hearts || getSuit() == suitNumber::spades))
			{
				frame.setFillColor(sf::Color::Green);
				return true;
			}
			else
			{
				frame.setFillColor(sf::Color::Red);
				return false;
			}
			break;
		default:
			return false;
			break;
		}
	}
	//na królow¹ mo¿na zagraæ wszystko, królow¹ mo¿na zagraæ na wszystko
	else if ((current->getFigure() == figureNumber::queen || getFigure() == figureNumber::queen) && !second) 
	{
		frame.setFillColor(sf::Color::Green);
		return true;
	}
	//jeœli grana przez gracza karta jest pierwsz¹ w tej turze, mog¹ pasowaæ do karty na stole jej figura lub kolor
	else if (!second)
	{
		if (suitMatches || figureMatches)
		{
			frame.setFillColor(sf::Color::Green);
			return true;
		}
		else
		{
			frame.setFillColor(sf::Color::Red);
			return false;
		}
	}
	//jeœli grana przez gracza karta nie jest pierwsz¹ w tej turze, z kart¹ na stole musi mieæ ona wspóln¹ figurê
	else
	{
		if (figureMatches)
		{
			frame.setFillColor(sf::Color::Green);
			return true;
		}
		else
		{
			frame.setFillColor(sf::Color::Red);
			return false;
		}
	}
}

void Card::draw(sf::RenderWindow& window)
{
	if (isChosen() == true)
		window.draw(frame);

	Object::draw(window);
}
