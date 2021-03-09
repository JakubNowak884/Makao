#include "headers\singlePlayer.h"

singlePlayer::~singlePlayer()
{
	delete bot;
}

AI* singlePlayer::getAI(int number)
{
	return bot;
}

gameStateNumber singlePlayer::update(sf::Event event, sf::RenderWindow& window)
{
	if (won == 0 || bot->getWon() == 0)
	{
		if (won != 0)
		{
			bot->setWon(1 + wonCounter);
			return gameStateNumber::endgame;
		}

		if (turn == bot->getID())
		{
			if (bot->getWon() == 0)
			{
				if (bot->hasACardAbleToPlay(deck, addDraw))
				{
					cardDoThings(bot->playACard(deck, addDraw));
					if (bot->handEmpty())
					{
						bot->setWon(1 + wonCounter);
						wonCounter++;
					}
				}
				else
				{
					if (deck.front() != deck.back())
						cardDoThings(bot->drawACard(deck, addDraw, addDrawAmount));
				}

			}
			turn--;
		}

		

		if (bot->getWon() != 0)
		{
			won = 1 + wonCounter;
			return gameStateNumber::endgame;
		}

		if (won == 0) 
			return game::update(event, window);
		turn++;

		return gameStateNumber::def;
	}
	else 
		return gameStateNumber::endgame;
}

void singlePlayer::draw(sf::RenderWindow& window)
{
	game::draw(window);
	bot->draw(window);
}
