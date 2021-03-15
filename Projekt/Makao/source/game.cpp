#include "headers\game.h"

game::game()
{
	textureSuit.loadFromFile("../resources/textures/suit.png");
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	b_fold = new button("Pas", font, 150, 100, 400, 250);
	b_draw = new button("Dobierz", font, 350, 100, 400, 550);

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

	for (std::vector<card*>::reverse_iterator i = deckToCopy.rbegin(); i != deckToCopy.rbegin() + 5; i++)
		hand.push_back((*i));

	for (int i = 0; i < 5; i++)
		deckToCopy.pop_back();

	std::move(deckToCopy.begin(), deckToCopy.end(), std::back_inserter(deck));
	deckToCopy.clear();

	float addX = 0;
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		(*i)->setPosition(sf::Vector2f(72 + addX, 800));
		addX += 128;
	}

	turn = 1;
	won = 0;
	wonCounter = 0;

	actionCardIsActive = false;
	addDrawAmount = 1;
	currentSuit = suitNumber::null;
	currentFigure = figureNumber::null;

	delay = 0;
	myDelay = 0;
	jackID = 0;
}

game::~game()
{
	delete b_fold;
	delete b_draw;
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

int game::getWon()
{
	return won;
}

card* game::drawACard(int howMany)
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
			hand.back()->setPositon(sf::Vector2f(x + 128, 800));
		}
		return nullptr;
	}
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
	if (myDelay == 0)
	{
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0 && (*hand.begin())->getX() < 800)
			{
				for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
				{
					(*i)->setPosition(sf::Vector2f((*i)->getX() + 128, 800));
				}
			}
			else if (event.mouseWheelScroll.delta < 0 && hand.back()->getX() > 0)
			{
				for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
				{
					(*i)->setPosition(sf::Vector2f((*i)->getX() - 128, 800));
				}
			}
		}

		for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
		{
			(*i)->uptade(getMousePos(window));
			if ((*i)->ableToPlay(deck.front(), actionCardIsActive, currentSuit, currentFigure, second) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && (*i)->isChosen())
			{
				(*i)->setChosen(false);
				deck.push_front((*i));
				auto j = hand.erase(i);
				for (j; j != hand.end(); j++)
					(*j)->setPosition(sf::Vector2f((*j)->getX() - 128, 800));
				second = true;
				if (hand.empty())
				{
					won = 1 + wonCounter;
					wonCounter++;
				}
				return cardDoThings(deck.front(), myDelay, 1);
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
			turn++;
			return cardDoThings(drawACard(addDrawAmount), myDelay, 1);
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
		myDelay--;
		turn++;
	}
	return gameStateNumber::def;
}

void game::draw(sf::RenderWindow& window)
{
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->getX() > -200 && (*i)->getX() < 1000) 
			(*i)->draw(window);
	}

	deck.front()->draw(window);
	b_fold->draw(window);
	b_draw->draw(window);
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
}
