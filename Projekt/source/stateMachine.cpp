#include "headers\stateMachine.h"

stateMachine::stateMachine()
{
	current = new menu;
	prev = nullptr;
}

stateMachine::~stateMachine()
{
	delete current;
	delete prev;
}

bool stateMachine::update(sf::Event event, sf::RenderWindow& window)
{
	switch (current->update(event, window))
	{
	case gameStateNumber::singlePlayerSettings:
		delete prev;
		prev = current;
		current = new singlePlayerSettings;
		break;
	case gameStateNumber::singlePlayer:
		delete prev;
		prev = current;
		current = new singlePlayer;
		break;
	case gameStateNumber::multiPlayerSettings:
		delete prev;
		prev = current;
		current = new multiPlayerSettings;
		break;
	case gameStateNumber::changeIP:
		prev = current;
		current = new changeIP(prev);
		break;
	case gameStateNumber::mutliPlayer:
		prev = current;
		current = new multiPlayer(prev);
		break;
	case gameStateNumber::endgame:
		delete prev;
		prev = current;
		current = new endgame(prev);
		break;
	case gameStateNumber::menu:
		delete prev;
		prev = current;
		current = new menu;
		break;
	case gameStateNumber::changeName:
		delete prev;
		prev = current;
		current = new changeName;
		break;
	case gameStateNumber::quit:
		return false;
		break;
	case gameStateNumber::setSuit:
		prev = current;
		current = new setSuit(prev);
		break;
	case gameStateNumber::setFigure:
		prev = current;
		current = new setFigure(prev);
		break;
	case gameStateNumber::resume:
		delete current;
		current = prev;
		prev = nullptr;
		break;
	default:
		break;
	}
	return true;
}

void stateMachine::draw(sf::RenderWindow& window)
{
	current->draw(window);
}
