#include "headers\game.h"

game::game()
{
	textureSuit.loadFromFile("../resources/textures/suit.png");
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	b_fold = std::make_unique<button>("Pas", font, 110, 50, 400, 280, 32);
	b_makao = std::make_unique<button>("Makao", font, 110, 50, 400, 225, 32);
	b_draw = std::make_unique<button>("Dobierz karte", font, 280, 60, 400, 530, 42);

	wanting.setFont(font);
	wanting.setCharacterSize(32);
	wanting.setFillColor(sf::Color::White);
	wanting.setPosition(225, 600);

	std::vector<card*> deckToCopy;

	for (int suit = 1; suit < 5; suit++)
	{
		for (int figure = 1; figure < 14; figure++)
		{
			card* newCard = new card(figureNumber(figure), suitNumber(suit), font, textureSuit, 120, 180, 400, 400, sf::Color::White);
			deckToCopy.push_back(newCard);
		}
	}

	//shuffling
	std::shuffle(deckToCopy.begin(), deckToCopy.end(), std::mt19937{ std::random_device{}() });

	std::move(deckToCopy.begin(), deckToCopy.end(), std::back_inserter(deck));
	deckToCopy.clear();
}

void game::setCurrentSuit(suitNumber _suit)
{
	currentSuit = _suit;
}

void game::setCurrentFigure(figureNumber _figure)
{
	currentFigure = _figure;
}

AI* game::getAI(int number)
{
	return nullptr;
}

int game::getAmountOfPlayers()
{
	return amountOfPlayers;
}

int game::getWon()
{
	return player->getWon();
}

void game::bumpTurn()
{
	turn++;
	if (turn > amountOfPlayers)
		turn = 1;
}

gameStateNumber game::cardDoThings(card* current, int& _delay, int ID)
{
	if (current == nullptr)
	{
		_delay = delay;
		delay = 0;
		actionCardIsActive = false;
		addDrawAmount = 1;
		currentSuit = suitNumber::null;
		if (ID == jackID)
			currentFigure = figureNumber::null;
	}
	else if (current->getFigure() == figureNumber::ace)
	{
		actionCardIsActive = true;
		return gameStateNumber::setSuit;
	}
	else if (current->getFigure() == figureNumber::two)
	{
		if (!actionCardIsActive)
			addDrawAmount += 1;
		else 
			addDrawAmount += 2;
		actionCardIsActive = true;
	}
	else if (current->getFigure() == figureNumber::three)
	{
		if (!actionCardIsActive)
			addDrawAmount += 2;
		else
			addDrawAmount += 3;
		actionCardIsActive = true;
	}
	else if (current->getFigure() == figureNumber::four)
	{
		delay++;
		actionCardIsActive = true;
	}
	else if (current->getFigure() == figureNumber::jack)
	{
		actionCardIsActive = true;
		jackID = ID;
		return gameStateNumber::setFigure;
	}
	else
	{
		_delay = delay;
		delay = 0;
		actionCardIsActive = false;
		addDrawAmount = 1;
		currentSuit = suitNumber::null;
		if (ID == jackID)
			currentFigure = figureNumber::null;
	}
	return gameStateNumber::def;
}

gameStateNumber game::update(sf::Event event, sf::RenderWindow& window)
{
	if (player->getWon() == 0)
	{
		if (player->getDelay() == 0)
		{
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0 && (player->hand.front())->getX() < 800)
				{
					for (std::vector<card*>::iterator i = player->hand.begin(); i != player->hand.end(); i++)
					{
						(*i)->setPosition(sf::Vector2f((*i)->getX() + 128, 800));
					}
				}
				else if (event.mouseWheelScroll.delta < 0 && player->hand.back()->getX() > 0)
				{
					for (std::vector<card*>::iterator i = player->hand.begin(); i != player->hand.end(); i++)
					{
						(*i)->setPosition(sf::Vector2f((*i)->getX() - 128, 800));
					}
				}
			}

			for (std::vector<card*>::iterator i = player->hand.begin(); i != player->hand.end(); i++)
			{
				(*i)->uptade(getMousePos(window));
				if ((*i)->ableToPlay(deck.front(), actionCardIsActive, currentSuit, currentFigure, second) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && (*i)->isChosen())
				{
					(*i)->setChosen(false);
					deck.push_front((*i));
					auto j = player->hand.erase(i);
					for (j; j != player->hand.end(); j++)
						(*j)->setPosition(sf::Vector2f((*j)->getX() - 128, 800));
					second = true;
					if (player->hand.empty())
					{
						player->setWon(1 + wonCounter);
						wonCounter++;
						bumpTurn();
					}
					return cardDoThings(deck.front(), player->getDelay(), 1);
				}
			}

			if (b_fold->clicked(event))
			{
				second = false;
				b_fold->setChosen(false);
				turn++;
			}

			if (b_draw->clicked(event))
			{
				b_draw->setChosen(false);
				bumpTurn();
				return cardDoThings(player->drawACard(deck, actionCardIsActive, currentSuit, currentFigure, addDrawAmount), player->getDelay(), 1);
			}

			deck.front()->setPosition(sf::Vector2f(400, 400));

			if (second)
				b_fold->uptade(getMousePos(window));

			if (!second && deck.front() != deck.back())
				b_draw->uptade(getMousePos(window));

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				return gameStateNumber::menu;
		}
		else
		{
			player->decrementDelay();
			bumpTurn();
		}
	}
	else
	{
		bumpTurn();
	}
	
	return gameStateNumber::def;
}

void game::draw(sf::RenderWindow& window)
{
	if (currentSuit != suitNumber::null || currentFigure != figureNumber::null)
	{
		std::string toText = "Zadanie: ";
		if (currentSuit != suitNumber::null)
			switch (currentSuit)
			{
			case suitNumber::clubs:
				toText += "trefl";
				break;
			case suitNumber::diamonds:
				toText += "karo";
				break;
			case suitNumber::hearts:
				toText += "serc";
				break;
			case suitNumber::spades:
				toText += "pik";
				break;
			default:
				break;
			}
		else
			switch (currentFigure)
			{
			case figureNumber::five:
				toText += "piatek";
				break;
			case figureNumber::six:
				toText += "szostek";
				break;
			case figureNumber::seven:
				toText += "siodemek";
				break;
			case figureNumber::eight:
				toText += "osemek";
				break;
			case figureNumber::nine:
				toText += "dziewiatek";
				break;
			case figureNumber::ten:
				toText += "dziesiatek";
				break;
			default:
				break;
			}
		wanting.setString(toText);
		window.draw(wanting);
	}

	player->draw(window);

	deck.front()->draw(window);

	b_fold->draw(window);
	b_makao->draw(window);
	b_draw->draw(window);
}

game::Player::Player(std::list<card*>& deck, sf::Font& font, int _ID)
{
	info.setFont(font);
	info.setCharacterSize(24);
	info.setPosition(580, 600);

	int j = 0;
	for (std::list<card*>::iterator i = deck.begin(); i != deck.end(); i++)
	{
		if (j == 5) break;
		hand.push_back((*i));
		j++;
	}

	for (int i = 0; i < 5; i++)
		deck.pop_front();

	float addX = 0;
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		(*i)->setPosition(sf::Vector2f(72 + addX, 800));
		addX += 128;
	}

	ID = _ID;
	won = 0;
	delay = 0;
}

int game::Player::getID()
{
	return ID;
}

int game::Player::getWon()
{
	return won;
}

int& game::Player::getDelay()
{
	return delay;
}

void game::Player::decrementDelay(int value)
{
	delay -= value;
}

void game::Player::setWon(int _won)
{
	won = _won;
}

card* game::Player::drawACard(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany)
{
	if (deck.back()->ableToPlay(deck.front(), actionCardIsActive, currentSuit, currentFigure))
	{
		deck.push_front(deck.back());
		deck.pop_back();
		return deck.front();
	}
	else
	{
		for (int i = 0; i < howMany; i++)
		{
			if (deck.front() == deck.back()) break;
			float x = hand.back()->getX();
			hand.push_back(deck.back());
			deck.pop_back();
			hand.back()->setPosition(sf::Vector2f(x + 128, 800));
		}
		return nullptr;
	}
}

void game::Player::draw(sf::RenderWindow& window)
{
	info.setString(getPlayerName() + "\nIlosc kart: " + std::to_string(hand.size()) + "\nOpoznienie: " + std::to_string(delay));
	window.draw(info);

	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->getX() > -200 && (*i)->getX() < 1000)
			(*i)->draw(window);
	}
}
