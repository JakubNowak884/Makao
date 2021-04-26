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
		current = new singlePlayer(dynamic_cast<singlePlayerSettings*>(prev));
		break;
	case gameStateNumber::multiPlayerSettings:
		delete prev;
		prev = current;
		current = new multiPlayerSettings;
		break;
	case gameStateNumber::changeIP:
		prev = current;
		current = new changeIP(dynamic_cast<multiPlayerSettings*>(prev));
		break;
	case gameStateNumber::multiPlayer:
		delete prev;
		prev = current;
		current = new multiPlayer(dynamic_cast<multiPlayerSettings*>(prev));
		break;
	case gameStateNumber::endgame:
		delete prev;
		prev = current;
		if (dynamic_cast<multiPlayer*>(prev) == nullptr)
			current = new endgame(dynamic_cast<singlePlayer*>(prev));
		else
			current = new endgame(dynamic_cast<multiPlayer*>(prev));
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
	case gameStateNumber::instruction:
		delete prev;
		prev = current;
		current = new instruction;
		break;
	case gameStateNumber::quit:
		return false;
		break;
	case gameStateNumber::setSuit:
		prev = current;
		current = new setSuit(dynamic_cast<game*>(prev));
		break;
	case gameStateNumber::setFigure:
		prev = current;
		current = new setFigure(dynamic_cast<game*>(prev));
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
