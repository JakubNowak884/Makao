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

bool stateMachine::uptade(sf::Event event, sf::RenderWindow& window)
{
	switch (current->update(event, window))
	{
	case gameStateNumber::singlePlayer:
		delete current;
		current = new singlePlayer;
		break;
	case gameStateNumber::singlePlayerSettings:
		delete current;
		current = new singlePlayerSettings;
		break;
	case gameStateNumber::endgame:
		prev = current;
		current = new endgame(prev);
		break;
	case gameStateNumber::menu:
		delete prev;
		delete current;
		current = new menu;
		break;
	case gameStateNumber::quit:
		return false;
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
