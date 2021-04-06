#include "headers\singlePlayer.h"

singlePlayer::singlePlayer(gameState* prev)
{
	amountOfPlayers = prev->getAmountOfPlayers();

	player = std::make_unique<Player>(deck, font, 1);

	bool oneBot;
	if (amountOfPlayers == 2)
		oneBot = true;
	else
		oneBot = false;

	for (int i = 2; i < amountOfPlayers + 1; i++)
		bots.push_back(std::make_unique<AI>(deck, font, i, oneBot));

	//t = std::thread(&singlePlayer::botsTakesTurn, this);
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
	//while (true)
	//{
		for (auto bot = bots.begin(); bot < bots.end(); bot++)
		{
			if (turn == (*bot)->getID())
			{
				if ((*bot)->getWon() == 0)
				{
					if (everyoneElseWon())
					{
						(*bot)->setWon(1 + wonCounter);
						end = true;
					}

					if ((*bot)->getDelay() == 0)
					{
						if ((*bot)->hasACardAbleToPlay(deck, actionCardIsActive, currentSuit, currentFigure))
						{
							cardDoThings((*bot)->playACard(deck, actionCardIsActive, currentSuit, currentFigure), (*bot)->getDelay(), (*bot)->getID());
							if ((*bot)->handEmpty())
							{
								(*bot)->setWon(1 + wonCounter);
								wonCounter++;
							}
						}
						else
						{
							if (deck.front() != deck.back())
								cardDoThings((*bot)->drawACard(deck, actionCardIsActive, currentSuit, currentFigure, addDrawAmount), (*bot)->getDelay(), (*bot)->getID());
						}
						std::this_thread::sleep_for(std::chrono::seconds(sleepDuration));
					}
					else
						(*bot)->getDelay()--;
				}
				bumpTurn();
			}
		}

		if (player->getWon() != 0)
		{
			sleepDuration = 0;
			bumpTurn();
		}

		test = true;
	//}
}

gameStateNumber singlePlayer::update(sf::Event event, sf::RenderWindow& window)
{
	if (turn == player->getID())
	{
		if (everyoneElseWon())
		{
			player->setWon(1 + wonCounter);
			return gameStateNumber::endgame;
		}

		return game::update(event, window);	
	}

	if (end)
		return gameStateNumber::endgame;

	return gameStateNumber::def;
}

void singlePlayer::draw(sf::RenderWindow& window)
{
	if (turn != 1 && test == true)
	{
		test = false;
		std::thread t1(&singlePlayer::botsTakesTurn, this);
		t1.detach();
	}

	game::draw(window);

	for (auto bot = bots.begin(); bot < bots.end(); bot++)
		(*bot)->draw(window);
}
