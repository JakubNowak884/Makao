#include "..\headers\GameStates\game.h"
#include "..\headers\Resources.h"

Game::Game(Resources* _resources, bool onlyQueens)
	: GameState(_resources)
{
	b_fold = std::make_unique<Button>(resources->getText(int(gameStateNumber::game), 1), resources->getFont(), 110, 50, 400, 280, resources->getTexturePtr("button"), 32);
	b_makao = std::make_unique<Button>(resources->getText(int(gameStateNumber::game), 2), resources->getFont(), 110, 50, 400, 225, resources->getTexturePtr("button"), 32);
	b_draw = std::make_unique<Button>(resources->getText(int(gameStateNumber::game), 3), resources->getFont(), 280, 60, 400, 530, resources->getTexturePtr("button"), 42);

	initText(wanting, 250, 575, 32);
	initText(addDraw, 0, 0, 32);

	std::vector<std::shared_ptr<Card>> deckToCopy;

	if (onlyQueens)
	{
		for (int suit = 1; suit < 5; suit++)
		{
			for (int figure = 1; figure < 14; figure++)
			{
				deckToCopy.push_back(std::make_shared<Card>(figureNumber(12), suitNumber(suit), resources->getFont(), resources->getTexturePtr("deck"), 120, 180, 400, 400, sf::Color::White));
			}
		}
	}
	else
	{
		for (int suit = 1; suit < 5; suit++)
		{
			for (int figure = 1; figure < 14; figure++)
			{
				deckToCopy.push_back(std::make_shared<Card>(figureNumber(figure), suitNumber(suit), resources->getFont(), resources->getTexturePtr("deck"), 120, 180, 400, 400, sf::Color::White));
			}
		}

		//shuffling
		std::shuffle(deckToCopy.begin(), deckToCopy.end(), std::mt19937{ std::random_device{}() });
	}

	std::move(deckToCopy.begin(), deckToCopy.end(), std::back_inserter(deck));
	deckToCopy.clear();
}

void Game::setCurrentSuit(suitNumber _suit)
{
	currentSuit = _suit;
}

void Game::setCurrentFigure(figureNumber _figure)
{
	currentFigure = _figure;
}

AI* Game::getAI(int number)
{
	return nullptr;
}

std::vector<std::shared_ptr<Card>>& Game::getHand()
{
	return player->hand;
}

int Game::getAmountOfPlayers()
{
	return amountOfPlayers;
}

int Game::getWon()
{
	return player->getWon();
}

void Game::bumpTurn()
{
	turn++;
	if (turn > amountOfPlayers)
		turn = 1;
}

gameStateNumber Game::cardDoThings(Card* current, int& _delay, int ID, bool bot)
{
	if (current == nullptr)
	{
		actionCardIsActive = false;
		addDrawAmount = 1;
		currentSuit = suitNumber::null;
		if (jackID != 0 && ID != jackID)
			actionCardIsActive = true;
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
		four = true;
	}
	else if (current->getFigure() == figureNumber::jack)
	{
		actionCardIsActive = true;
		jackID = ID;
		return gameStateNumber::setFigure;
	}
	else if (current->getFigure() == figureNumber::king)
	{
		if (current->getSuit() == suitNumber::hearts)
		{
			addDrawAmount += 4;
			actionCardIsActive = true;
		}
		else if ((current->getSuit() == suitNumber::spades))
		{
			addDrawAmount += 4;
			actionCardIsActive = true;
			if (!bot)
			{
				turn -= 1;
				if (turn < 1)
				{
					turn = amountOfPlayers;
				}
			}
			else
			{
				turn -= 2;
				while (turn < 1)
				{
					turn = amountOfPlayers + turn;
				}
			}
		}
		else
		{
			actionCardIsActive = false;
			addDrawAmount = 1;
			currentSuit = suitNumber::null;
			currentFigure = figureNumber::null;
			jackID = 0;
		}
	}
	else
	{
		actionCardIsActive = false;
		addDrawAmount = 1;
		currentSuit = suitNumber::null;
		currentFigure = figureNumber::null;
		jackID = 0;
	}
	return gameStateNumber::def;
}

gameStateNumber Game::update(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseWheelScrolled || event.type == sf::Event::KeyPressed)
	{
		if ((event.mouseWheelScroll.delta > 0 || event.key.code == sf::Keyboard::Right) && (player->hand.front())->getX() < 800)
		{
			for (auto i = player->hand.begin(); i != player->hand.end(); i++)
			{
				(*i)->setPosition(sf::Vector2f((*i)->getX() + 128, 800));
			}
		}
		else if ((event.mouseWheelScroll.delta < 0 || event.key.code == sf::Keyboard::Left) && player->hand.back()->getX() > 0)
		{
			for (auto i = player->hand.begin(); i != player->hand.end(); i++)
			{
				(*i)->setPosition(sf::Vector2f((*i)->getX() - 128, 800));
			}
		}
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !threadRunning2)
		return gameStateNumber::menu;

	if (turn == player->getID())
	{
		player->setTextColor(sf::Color::Green);
		if (player->getWon() == 0)
		{
			if (player->getDelay() == 0)
			{
				for (auto i = player->hand.begin(); i != player->hand.end(); i++)
				{
					(*i)->uptade(getMousePos(window));
					if ((*i)->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure, second) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && (*i)->isChosen())
					{
						(*i)->setChosen(false);
						deck.push_front((*i));
						auto j = player->hand.erase(i);
						for (j; j != player->hand.end(); j++)
							(*j)->setPosition(sf::Vector2f((*j)->getX() - 128, 800));
						second = true;
						if (player->hand.empty())
						{
							wonCounter++;
							player->setWon(wonCounter);
							player->setTextColor(sf::Color::White);
							bumpTurn();
						}
						return cardDoThings(deck.front().get(), player->getDelay(), 1);
					}
				}

				if (b_fold->clicked(event))
				{
					b_fold->setChosen(false);
					player->setTextColor(sf::Color::White);
					bumpTurn();
					if (player->hand.size() == 1)
						player->drawACard(deck, actionCardIsActive, currentSuit, currentFigure, 5);
					if (four && !second)
					{
						player->setDelay(delay);
						delay = 0;
						four = false;
						actionCardIsActive = false;
					}
					second = false;
				}

				if (b_makao->clicked(event))
				{
					b_fold->setChosen(false);
					player->setTextColor(sf::Color::White);
					bumpTurn();
					if (four && !second)
					{
						player->setDelay(delay);
						delay = 0;
						four = false;
						actionCardIsActive = false;
					}
					second = false;
				}

				if (b_draw->clicked(event))
				{
					b_draw->setChosen(false);
					player->setTextColor(sf::Color::White);
					bumpTurn();
					return cardDoThings(player->drawACard(deck, actionCardIsActive, currentSuit, currentFigure, addDrawAmount), player->getDelay(), 1);
				}

				deck.front()->setPosition(sf::Vector2f(400, 400));

				b_fold->setChosen(false);
				if (second || four)
					b_fold->uptade(getMousePos(window));

				b_makao->setChosen(false);
				if ((second || four) && player->hand.size() == 1)
					b_makao->uptade(getMousePos(window));

				if (!second && deck.front() != deck.back() && !four)
					b_draw->uptade(getMousePos(window));
			}
			else
			{
				player->decrementDelay();
				player->setTextColor(sf::Color::White);
				bumpTurn();
			}
		}
		else
		{
			player->setTextColor(sf::Color::White);
			bumpTurn();
		}
	}
	
	return gameStateNumber::def;
}

void Game::draw(sf::RenderWindow& window)
{
	if (currentSuit != suitNumber::null || currentFigure != figureNumber::null)
	{
		std::wstring toText = resources->getText(int(gameStateNumber::game), 4);
		if (currentSuit != suitNumber::null)
			switch (currentSuit)
			{
			case suitNumber::clubs:
				toText += resources->getText(int(gameStateNumber::game), 5);
				break;
			case suitNumber::diamonds:
				toText += resources->getText(int(gameStateNumber::game), 6);
				break;
			case suitNumber::hearts:
				toText += resources->getText(int(gameStateNumber::game), 7);
				break;
			case suitNumber::spades:
				toText += resources->getText(int(gameStateNumber::game), 8);
				break;
			default:
				break;
			}
		else
			switch (currentFigure)
			{
			case figureNumber::five:
				toText += resources->getText(int(gameStateNumber::game), 9);
				break;
			case figureNumber::six:
				toText += resources->getText(int(gameStateNumber::game), 10);
				break;
			case figureNumber::seven:
				toText += resources->getText(int(gameStateNumber::game), 11);
				break;
			case figureNumber::eight:
				toText += resources->getText(int(gameStateNumber::game), 12);
				break;
			case figureNumber::nine:
				toText += resources->getText(int(gameStateNumber::game), 13);
				break;
			case figureNumber::ten:
				toText += resources->getText(int(gameStateNumber::game), 14);
				break;
			default:
				break;
			}
		wanting.setString(toText);
		window.draw(wanting);
	}
	addDraw.setString(resources->getText(int(gameStateNumber::game), 15) + std::to_wstring(addDrawAmount));
	window.draw(addDraw);

	player->draw(window);

	if (deck.front() != nullptr)
		deck.front()->draw(window);

	b_fold->draw(window);
	b_makao->draw(window);
	b_draw->draw(window);
}

Game::Player::Player(std::list<std::shared_ptr<Card>>& deck, Resources* _resources, int _ID)
	: resources(_resources)
{
	info.setFont(resources->getFont());
	info.setCharacterSize(24);
	info.setPosition(580, 600);

	int j = 0;
	for (std::list<std::shared_ptr<Card>>::iterator i = deck.begin(); i != deck.end(); i++)
	{
		if (j == 5) break;
		hand.push_back((*i));
		j++;
	}

	for (int i = 0; i < 5; i++)
		deck.pop_front();

	float addX = 0;
	for (std::vector<std::shared_ptr<Card>>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		(*i)->setPosition(sf::Vector2f(72 + addX, 800));
		addX += 128;
	}

	ID = _ID;
	won = 0;
	delay = 0;
}

int Game::Player::getID()
{
	return ID;
}

int Game::Player::getWon()
{
	return won;
}

int& Game::Player::getDelay()
{
	return delay;
}

void Game::Player::decrementDelay(int value)
{
	delay -= value;
}

void Game::Player::setWon(int _won)
{
	won = _won;
}

void Game::Player::setDelay(int _delay)
{
	delay = _delay;
}

void Game::Player::setTextColor(sf::Color color)
{
	info.setFillColor(color);
}

Card* Game::Player::drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany)
{
	if (deck.back()->ableToPlay(deck.front().get(), actionCardIsActive, currentSuit, currentFigure))
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
			float x = hand.back()->getX();
			hand.push_back(deck.back());
			deck.pop_back();
			hand.back()->setPosition(sf::Vector2f(x + 128, 800));
		}
		return nullptr;
	}
}

void Game::Player::draw(sf::RenderWindow& window)
{
	info.setString(getPlayerName() + resources->getText(int(gameStateNumber::game), 16) + std::to_wstring(hand.size()) + resources->getText(int(gameStateNumber::game), 17) + std::to_wstring(delay));
	window.draw(info);

	for (std::vector<std::shared_ptr<Card>>::iterator i = hand.begin(); i != hand.end(); i++)
	{
		if ((*i)->getX() > -200 && (*i)->getX() < 1000)
			(*i)->draw(window);
	}
}
