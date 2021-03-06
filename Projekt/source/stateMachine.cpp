#include "headers/StateMachine.h"

StateMachine::StateMachine(std::shared_ptr<Resources> _resources)
	: resources(_resources)
{
	current = new Menu(resources);
	prev = nullptr;
}

StateMachine::~StateMachine()
{
	delete current;
	delete prev;
}

void StateMachine::exception(std::wstring error)
{
	delete current;
	current = new Error(error, resources);
	prev = nullptr;
}

bool StateMachine::update(sf::Event event, sf::RenderWindow& window)
{
	switch (current->update(event, window))
	{
	case gameStateNumber::singlePlayerSettings:
		delete prev;
		prev = current;
		current = new SinglePlayerSettings(resources);
		break;

	case gameStateNumber::singlePlayer:
		delete prev;
		prev = current;
		current = new SinglePlayer(dynamic_cast<SinglePlayerSettings*>(prev), resources);
		break;

	case gameStateNumber::multiPlayerSettings:
		delete prev;
		prev = current;
		current = new MultiPlayerSettings(resources);
		break;

	case gameStateNumber::changeIP:
		prev = current;
		current = new ChangeIP(dynamic_cast<MultiPlayerSettings*>(prev), resources);
		break;

	case gameStateNumber::multiPlayer:
		delete prev;
		prev = current;
		try
		{
			current = new MultiPlayer(dynamic_cast<MultiPlayerSettings*>(prev), resources);
		}
		catch (std::wstring error)
		{
			delete current;
			current = new Error(error, resources);
			prev = nullptr;
		}
		break;

	case gameStateNumber::endgame:
	{
		delete prev;
		prev = current;
		//sprawdzenie czy poprzedni stan gry by? gr? dla jednego gracza, czy dla wielu
		MultiPlayer* temp = dynamic_cast<MultiPlayer*>(prev);
		if (temp == nullptr)
			current = new Endgame(dynamic_cast<SinglePlayer*>(prev), resources);
		else
			current = new Endgame(temp, resources); 
	}
		break;

	case gameStateNumber::menu:
		delete prev;
		prev = nullptr;
		delete current;
		current = new Menu(resources);
		break;

	case gameStateNumber::changeName:
		delete prev;
		prev = current;
		current = new ChangeName(resources);
		break;

	case gameStateNumber::instruction:
		delete prev;
		prev = current;
		current = new Instruction(resources);
		break;

	case gameStateNumber::quit:
		return false;
		break;

	case gameStateNumber::wantSuit:
		prev = current;
		current = new WantSuit(dynamic_cast<Game*>(prev), resources);
		break;

	case gameStateNumber::wantFigure:
	{
		prev = current;
		Game* temp = dynamic_cast<Game*>(prev);
		if (temp != nullptr)
			current = new WantFigure(temp, resources); 
	}
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

void StateMachine::draw(sf::RenderWindow& window)
{
	current->draw(window);
}
