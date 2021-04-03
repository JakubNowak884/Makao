#include "headers\singlePlayer.h"

singlePlayer::singlePlayer()
{
	player = std::make_unique<Player>(deck, 1);
	bot = new AI(deck, font, 2);
}

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
	if (player->getWon() == 0 || bot->getWon() == 0)
	{
		if (player->getWon() != 0)
		{
			bot->setWon(1 + wonCounter);
			return gameStateNumber::endgame;
		}

		if (bot->getDelay() == 0)
		{
			if (turn == bot->getID())
			{
				if (bot->getWon() == 0)
				{
					if (bot->hasACardAbleToPlay(deck, actionCardIsActive, currentSuit, currentFigure))
					{
						cardDoThings(bot->playACard(deck, actionCardIsActive, currentSuit, currentFigure), bot->getDelay(), bot->getID());
						if (bot->handEmpty())
						{
							bot->setWon(1 + wonCounter);
							wonCounter++;
						}
					}
					else
					{
						if (deck.front() != deck.back())
							cardDoThings(bot->drawACard(deck, actionCardIsActive, currentSuit, currentFigure, addDrawAmount), bot->getDelay(), bot->getID());
					}

				}
				turn--;
			}
		}
		else
		{
			bot->getDelay()--;
			turn--;
		}
		

		if (bot->getWon() != 0)
		{
			player->setWon(1 + wonCounter);
			return gameStateNumber::endgame;
		}

		if (player->getWon() == 0)
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
