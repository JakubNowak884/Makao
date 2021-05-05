#include "..\headers\GameStates\singlePlayer.h"
#include "..\headers\Resources.h"

SinglePlayer::SinglePlayer(SinglePlayerSettings* prev, Resources* _resources)
	: Game(_resources, prev->getOnlyQueens())
{
	amountOfPlayers = prev->getAmountOfPlayers();
	sleepDuration = prev->getBotSpeed();

	player = std::make_unique<Player>(deck, resources, 1);

	bool oneBot;
	if (amountOfPlayers == 2)
		oneBot = true;
	else
		oneBot = false;

	for (int i = 2; i < amountOfPlayers + 1; i++)
		bots.push_back(std::make_unique<AI>(deck, resources, i, oneBot));
}

AI* SinglePlayer::getAI(int ID)
{
	for (auto bot = bots.begin(); bot < bots.end(); bot++)
		if ((*bot)->getID() == ID)
			return (*bot).get();
	return nullptr;
}

void SinglePlayer::botsTakesTurn()
{
	for (auto bot = bots.begin(); bot < bots.end(); bot++)
	{
		for (auto bot = bots.begin(); bot < bots.end(); bot++)
		{
			(*bot)->rememberCard(deck.front()->getSuit(), deck.front()->getFigure());
		}
		if (turn == (*bot)->getID())
		{
			(*bot)->setTextColor(sf::Color::Green);
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
			if ((*bot)->getWon() == 0)
			{
				if (wonCounter == amountOfPlayers - 1)
				{
					wonCounter++;
					(*bot)->setWon(wonCounter);
					end = true;
				}
				else if ((*bot)->getDelay() == 0)
				{
					if ((*bot)->hasACardAbleToPlay(deck, actionCardIsActive, currentSuit, currentFigure))
					{
						while ((*bot)->hasACardAbleToPlay(deck, actionCardIsActive, currentSuit, currentFigure))
						{
							switch (cardDoThings((*bot)->playACard(deck, actionCardIsActive, currentSuit, currentFigure), (*bot)->getDelay(), (*bot)->getID(), true))
							{
							case gameStateNumber::setSuit:
								currentSuit = (*bot)->wantSuit();
								break;
							case gameStateNumber::setFigure:
								currentFigure = (*bot)->wantFigure();
								break;
							default:
								break;
							}

							if ((*bot)->handEmpty())
							{
								wonCounter++;
								(*bot)->setWon(wonCounter);
							}
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

	threadRunning2 = false;
}

gameStateNumber SinglePlayer::update(sf::Event event, sf::RenderWindow& window)
{
	if (end && threadRunning2 == false)
		return gameStateNumber::endgame;

	
	if (wonCounter == amountOfPlayers - 1 && player->getWon() == 0)
	{
		player->setWon(1 + wonCounter);
		return gameStateNumber::endgame;
	}

	if(wonCounter == amountOfPlayers)
		return gameStateNumber::endgame;

	return Game::update(event, window);	
}

void SinglePlayer::draw(sf::RenderWindow& window)
{
	if (turn != 1 && threadRunning2 == false)
	{
		threadRunning2 = true;
		std::thread t1(&SinglePlayer::botsTakesTurn, this);
		t1.detach();
	}

	Game::draw(window);

	for (auto bot = bots.begin(); bot < bots.end(); bot++)
		(*bot)->draw(window);
}
