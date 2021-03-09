#include "headers\game.h"

game::game()
{
	texture.loadFromFile("../resources/textures/suit.png");
	font.loadFromFile("../resources/fonts/OpenSans-Regular.ttf");

	b_fold = new button("Pas", font, 150, 100, 400, 250);
	b_draw = new button("Dobierz", font, 350, 100, 400, 550);

	std::vector<card*> deckToCopy;

	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_ace("A", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_two("2", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_three("3", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_four("4", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_five("5", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_six("6", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_seven("7", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_eight("8", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_nine("9", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_ten("10", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_jack("J", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_queen("Q", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
	}
	for (int i = 0; i < 4; i++)
	{
		card* newCard = new card_king("K", suitNumber(i), font, texture, 120, 180, 400, 400, sf::Color::White);
		deckToCopy.push_back(newCard);
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

	addDraw = false;
	addDrawAmount = 1;
}

game::~game()
{
	delete b_fold;
	delete b_draw;
}

AI* game::getAI(int number)
{
	return nullptr;
}

int game::getWon()
{
	return won;
}

void game::drawACard(int howMany)
{
	if (howMany == 0) return;
	if (deck.back()->ableToPlay(deck.front(), addDraw))
	{
		deck.push_front(deck.back());
		deck.pop_back();
		cardDoThings(deck.front());
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
		cardDoThings(nullptr);
	}
}

void game::cardDoThings(card* current)
{
	if (current == nullptr)
	{
		addDraw = false;
		addDrawAmount = 1;
	}
	else if (typeid(*current).name() == typeid(card_two).name())
	{
		if (!addDraw)
			addDrawAmount += 1;
		else 
			addDrawAmount += 2;
		addDraw = true;
	}
	else if (typeid(*current).name() == typeid(card_three).name())
	{
		if (!addDraw)
			addDrawAmount += 2;
		else
			addDrawAmount += 3;
		addDraw = true;
	}
	else
	{
		addDraw = false;
		addDrawAmount = 1;
	}
}

gameStateNumber game::update(sf::Event event, sf::RenderWindow& window)
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
		if ((*i)->ableToPlay(deck.front(), addDraw, second) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && (*i)->isChosen())
		{
			(*i)->setChosen(false);
			deck.push_front((*i));
			auto j = hand.erase(i);
			for (j; j != hand.end(); j++)
				(*j)->setPosition(sf::Vector2f((*j)->getX() - 128, 800));
			second = true;
			cardDoThings(deck.front());
			if (hand.empty())
			{
				won = 1 + wonCounter;
				wonCounter++;
			}
			break;
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
		drawACard(addDrawAmount);
		b_draw->setChosen(false);
		turn++;
	}

	deck.front()->setPosition(sf::Vector2f(400, 400));

	if (second) 
		b_fold->uptade(getMousePos(window));

	if (!second && deck.front() != deck.back()) 
		b_draw->uptade(getMousePos(window));

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		return gameStateNumber::menu;

	return gameStateNumber::def;
}

void game::draw(sf::RenderWindow& window)
{
	for (std::vector<card*>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		//if ((*i)->getX() > 0 && (*i)->getX() < 800) 
			(*i)->draw(window);
	}

	deck.front()->draw(window);
	b_fold->draw(window);
	b_draw->draw(window);
}
