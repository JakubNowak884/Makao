#include "headers\singlePlayer.h"

singlePlayer::singlePlayer(singlePlayerSettings* prev)
{
	if (prev->getOnlyQueens())
	{
		deck.clear();

		for (int suit = 1; suit < 5; suit++)
		{
			for (int figure = 1; figure < 14; figure++)
			{
				deck.push_back(std::make_shared<card>(figureNumber(12), suitNumber(suit), font, textureSuit.get(), 120, 180, 400, 400, sf::Color::White));
			}
		}
	}

	amountOfPlayers = prev->getAmountOfPlayers();

	player = std::make_unique<Player>(deck, font, 1);

	bool oneBot;
	if (amountOfPlayers == 2)
		oneBot = true;
	else
		oneBot = false;

	for (int i = 2; i < amountOfPlayers + 1; i++)
		bots.push_back(std::make_unique<AI>(deck, font, textureSuit.get(), i, oneBot));
}

AI* singlePlayer::getAI(int ID)
{
	for (auto bot = bots.begin(); bot < bots.end(); bot++)
		if ((*bot)->getID() == ID)
			return (*bot).get();
}

bool singlePlayer::everyoneElseWon()
{
	int counter = 0;

	if (player->getWon() != 0)
		counter++;

	for (auto bot = bots.begin(); bot < bots.end(); bot++)
		if ((*bot)->getWon() != 0)
			counter++;

	if (counter == amountOfPlayers - 1)
		return true;
	else
		return false;
}

void singlePlayer::botsTakesTurn()
{
	for (auto bot = bots.begin(); bot < bots.end(); bot++)
	{
		if (turn == (*bot)->getID())
		{
			(*bot)->setTextColor(sf::Color::Green);
			if ((*bot)->getWon() == 0)
			{
				if (everyoneElseWon())
				{
					(*bot)->setWon(1 + wonCounter);
					end = true;
				}
				else if ((*bot)->getDelay() == 0)
				{
					if ((*bot)->hasACardAbleToPlay(deck, actionCardIsActive, currentSuit, currentFigure))
					{
						cardDoThings((*bot)->playACard(deck, actionCardIsActive, currentSuit, currentFigure), (*bot)->getDelay(), (*bot)->getID(), true);
						if ((*bot)->handEmpty())
						{
							(*bot)->setWon(1 + wonCounter);
							wonCounter++;
						}
					}
					else
					{
						if (deck.front() != deck.back() && !four)
							cardDoThings((*bot)->drawACard(deck, actionCardIsActive, currentSuit, currentFigure, addDrawAmount), (*bot)->getDelay(), (*bot)->getID(), true);
						else if (four)
						{
							(*bot)->setDelay(delay);
							delay = 0;
							four = false;
							actionCardIsActive = false;
						}
					}
					std::this_thread::sleep_for(std::chrono::seconds(sleepDuration));
				}
				else
					(*bot)->getDelay()--;
			}
			(*bot)->setTextColor(sf::Color::White);
			bumpTurn();
		}
	}

	if (player->getWon() != 0)
	{
		sleepDuration = 0;
		bumpTurn();
	}

	threadRunning = false;
}

gameStateNumber singlePlayer::update(sf::Event event, sf::RenderWindow& window)
{
	if (end && threadRunning == false)
		return gameStateNumber::endgame;

	
	if (everyoneElseWon())
	{
		player->setWon(1 + wonCounter);
		return gameStateNumber::endgame;
	}

	return game::update(event, window);	
}

void singlePlayer::draw(sf::RenderWindow& window)
{
	if (turn != 1 && threadRunning == false)
	{
		threadRunning = true;
		std::thread t1(&singlePlayer::botsTakesTurn, this);
		t1.detach();
	}

	game::draw(window);

	for (auto bot = bots.begin(); bot < bots.end(); bot++)
		(*bot)->draw(window);
}
