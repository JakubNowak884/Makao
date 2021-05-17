#include "headers\AI.h"
#include "headers\Resources.h"

AI::AI(std::list<std::shared_ptr<Card>>& deck, std::shared_ptr<Resources> _resources, int _ID, bool onlyOne)
	: resources(_resources)
{
	info.setFont(resources->getFont());
	info.setCharacterSize(24);

	//je�li tylko jeden gracz komputerowy zostanie utworzony jego graficzne przedstawienie znajduje si� u g�ry ekranu
	if (onlyOne)
	{
		info.setPosition(470, 10);
		cardBack = std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White);
	}
	else {
		switch (_ID)
		{
		case 2:		
			info.setPosition(10, 210);
			cardBack = std::make_unique<Object>(120, 180, 70, 400, resources->getTexturePtr("deck"), sf::Color::White);
			break;
		case 3:
			info.setPosition(470, 10);
			cardBack = std::make_unique<Object>(120, 180, 400, 100, resources->getTexturePtr("deck"), sf::Color::White);
			break;
		case 4:
			info.setPosition(580, 210);
			cardBack = std::make_unique<Object>(120, 180, 640, 400, resources->getTexturePtr("deck"), sf::Color::White);
			break;
		default:
			break;
		}
	}

	cardBack->getShape().setTextureRect(sf::IntRect(296, 920, 145, 230));
	//utworzenie r�ki gracza komputerowego
	int j = 0;
	for (std::list<std::shared_ptr<Card>>::iterator i = deck.begin(); i != deck.end(); ++i)
	{
		if (j == 5) break;
		hand.push_back((*i));
		j++;
	}

	for (int i = 0; i < 5; i++)
		deck.pop_front();

	ID = _ID;
	won = 0;
	delay = 0;
}

int AI::getID()
{
	return ID;
}

int AI::getWon()
{
	return won;
}

int& AI::getDelay()
{
	return delay;
}

bool AI::handEmpty()
{
	return hand.empty();
}

void AI::setWon(int _won)
{
	won = _won;
}

void AI::setDelay(int _delay)
{
	delay = _delay;
}

void AI::setTextColor(sf::Color color)
{
	info.setFillColor(color);
}

suitNumber AI::wantSuit()
{
	//je�li gracz komputerowy ma karty w r�ce ��da on koloru kt�ry posiada
	if (hand.size() > 0)
		return hand.front()->getSuit();
	//je�li gracz komputerowy ��da koloru swoj� ostatni� kart�, ��da on koloru kt�ry zosta� zagrany w najwi�kszej ilo�ci
	else
	{
		//utworzenie wektora, kt�rego ka�dy element reprezentuje mo�liwy do za��dania kolor
		std::vector<howManyCards> vec;
		for (int i = 1; i < 4; i++)
		{
			suitNumber suit = suitNumber(i);
			howManyCards temp(suit);
			vec.push_back(temp);
		}
		//zliczanie ile razy ka�dy kolor zosta� zagrany w trakcie gry
		for (auto i = cardsPlayed.begin(); i != cardsPlayed.end(); i++)
		{
			for (auto j = vec.begin(); j != vec.end(); j++)
			{
				if ((*i)->suit == j->suit)
					j->howMany++;
			}
		}
		auto max = max_element(std::begin(vec), std::end(vec));
		return max->suit;
	}
}

figureNumber AI::wantFigure()
{
	//je�li gracz komputerowy posiada conajmniej jedn� kart� w r�ce i mo�e zosta� ona za��dana, to ��da jej
	if (hand.size() > 0)
	{
		for (auto i = hand.begin(); i != hand.end(); ++i)
		{
			switch ((*i)->getFigure())
			{
			case figureNumber::five:
				return figureNumber::five;
				break;
			case figureNumber::six:
				return figureNumber::six;
				break;
			case figureNumber::seven:
				return figureNumber::seven;
				break;
			case figureNumber::eight:
				return figureNumber::eight;
				break;
			case figureNumber::nine:
				return figureNumber::nine;
				break;
			case figureNumber::ten:
				return figureNumber::ten;
				break;
			default:
				break;
			}
		}
	}
	//inaczej gracz komputerowy ��da figury, kt�ra zosta�a zagrana w najwi�kszej ilo�ci
	//utworzenie wektora, kt�rego ka�dy element reprezentuje mo�liw� do za��dania figur�
	std::vector<howManyCards> vec;
	for (int i = 5; i < 11; i++)
	{
		figureNumber figure = figureNumber(i);
		howManyCards temp(figure);
		vec.push_back(temp);
	}
	//zliczanie ile razy ka�da z figur zosta�a zagrana w trakcie gry
	for (auto i = cardsPlayed.begin(); i != cardsPlayed.end(); i++)
	{
		for (auto j = vec.begin(); j != vec.end(); j++)
		{
			if ((*i)->figure == j->figure)
				j->howMany++;
		}
	}
	auto max = max_element(std::begin(vec), std::end(vec));
	return max->figure;
}

void AI::rememberCard(suitNumber suit, figureNumber figure)
{
	cardsPlayed.push_back(std::make_unique<cardPlayed>(suit, figure));
	//je�li ilo�� kart przekroczy 52, znaczy to �e na pewno si� powtarzaj�, wi�c pierwszy element listy zostaje usuwany
	if (cardsPlayed.size() > 52)
		cardsPlayed.pop_front();
}

bool AI::hasACardAbleToPlay(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure)
{
	for (std::vector<std::shared_ptr<Card>>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure, second))
			return true;
	}
	second = false;
	return false;
}

Card* AI::playACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure)
{
	bool queen = false;
	std::vector<std::shared_ptr<Card>>::iterator temp = hand.begin();
	for (std::vector<std::shared_ptr<Card>>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure, second))
		{
			//je�li gracz komputerowy posiada� kr�low� to nie zagrywa jej, ale funkcja zapami�tuje ten fakt
			if ((*i)->getFigure() == figureNumber::queen)
			{
				queen = true;
				temp = i;
				continue;
			}
			deck.push_front((*i));
			hand.erase(i);
			second = true;
			return deck.front().get();
		}
	}
	//je�li �adna karta nie zosta�a zagrana, ale gracz komputerowy posiada kr�low� w r�ce to zagrywa j�
	if (queen)
	{
		deck.push_front((*temp));
		hand.erase(temp);
		second = true;
		return deck.front().get();
	}
	return nullptr;
}

Card* AI::drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany)
{
	//je�li dobrana karta mo�e zosta� zagrana, to jest zagrywana odrazu
	if (deck.back()->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure, second))
	{
		deck.push_front(deck.back());
		deck.pop_back();
		return deck.front().get();
	}
	else
	{
		for (int i = 0; i < howMany; i++)
		{
			if (deck.front() == deck.back()) break;
			hand.push_back(deck.back());
			deck.pop_back();
		}
		return nullptr;
	}
}

void AI::draw(sf::RenderWindow& window)
{
	size_t amount = hand.size();
	std::string amountText = std::to_string(amount);

	info.setString(resources->getText(14,1) + std::to_wstring(ID - 1) + resources->getText(14, 2) + std::to_wstring(hand.size()) + resources->getText(14, 3) + std::to_wstring(delay));
	window.draw(info);

	cardBack->draw(window);
}
