#include "..\headers\GameStates\singlePlayer.h"

SinglePlayer::SinglePlayer(SinglePlayerSettings* prev, std::shared_ptr<Resources> _resources)
	: Game(_resources, prev->getOnlyQueens())
{
	amountOfPlayers = prev->getAmountOfPlayers();
	sleepDuration = prev->getBotSpeed();

	player = std::make_unique<Player>(deck, resources, 1);
	//je�li tylko jeden gracz komputerowy znajduje si� on u g�ry ekranu
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
		//ka�dy z graczy komputerowych zapami�tuje aktualn� kart� na stole
		for (auto bot = bots.begin(); bot < bots.end(); bot++)
		{
			(*bot)->rememberCard(deck.front()->getSuit(), deck.front()->getFigure());
		}
		if (turn == (*bot)->getID())
		{
			(*bot)->setTextColor(sf::Color::Green);
			//tworzenie odst�pu czasowego mi�dzy turami graczy komputerowych
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
			if ((*bot)->getWon() == 0)
			{
				//jesli wszyscy pozostali gracze zako�czyli rozgrywk�
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
							//sprawdzenie czy karta zagrana przez gracza komputerowego to As lub Walet
							switch (cardDoThings((*bot)->playACard(deck, actionCardIsActive, currentSuit, currentFigure), (*bot)->getDelay(), (*bot)->getID(), true))
							{
							case gameStateNumber::wantSuit:
								currentSuit = (*bot)->wantSuit();
								break;
							case gameStateNumber::wantFigure:
								currentFigure = (*bot)->wantFigure();
								break;
							default:
								break;
							}
							//zwyci�stwo gracza komputerowego
							if ((*bot)->handEmpty())
							{
								wonCounter++;
								(*bot)->setWon(wonCounter);
							}
						}
					}
					else
					{
						//dobranie karty je�li talia ma wi�cej ni� jedn� kart� oraz nie jest aktualnie zagrana Czw�rka
						if (deck.front() != deck.back() && !four)
							cardDoThings((*bot)->drawACard(deck, actionCardIsActive, currentSuit, currentFigure, addDrawAmount), (*bot)->getDelay(), (*bot)->getID(), true);
						//je�li jest zagrana czw�rka ustawienie op�nienia dla aktualnego gracza komputerowego
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
	//je�li gracz ludzki sko�czy� rozgrywk� ustawienie op�nienia mi�dzy turami graczy komputerowych na zero
	if (player->getWon() != 0)
	{
		sleepDuration = 0;
		bumpTurn();
	}

	threadRunning = false;
}

gameStateNumber SinglePlayer::update(sf::Event event, sf::RenderWindow& window)
{
	if (end && threadRunning == false)
		return gameStateNumber::endgame;
	//je�li gracze komputerowi sko�czyli gr�
	if (wonCounter == amountOfPlayers - 1 && player->getWon() == 0)
	{
		player->setWon(1 + wonCounter);
		return gameStateNumber::endgame;
	}
	//je�li wszyscy gracze sko�czyli gr�
	if (wonCounter == amountOfPlayers)
		return gameStateNumber::endgame;

	return Game::update(event, window);	
}

void SinglePlayer::draw(sf::RenderWindow& window)
{
	//je�li gracz sko�czy� tur�, tura graczy komputerowych rozpoczyna prac� na osobnym w�tku
	if (turn != 1 && threadRunning == false)
	{
		threadRunning = true;
		std::thread t1(&SinglePlayer::botsTakesTurn, this);
		t1.detach();
	}

	Game::draw(window);

	for (auto bot = bots.begin(); bot < bots.end(); bot++)
		(*bot)->draw(window);
}
