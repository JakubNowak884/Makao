#include "headers/StateMachine.h"

StateMachine::StateMachine(std::shared_ptr<Resources> _resources)
	: resources(_resources)
{
	current = new Menu(resources.get());
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
	current = new Error(error, resources.get());
	prev = nullptr;
}

bool StateMachine::update(sf::Event event, sf::RenderWindow& window)
{
	switch (current->update(event, window))
	{
	case gameStateNumber::singlePlayerSettings:
		delete prev;
		prev = current;
		current = new SinglePlayerSettings(resources.get());
		break;
	case gameStateNumber::singlePlayer:
		delete prev;
		prev = current;
		current = new SinglePlayer(dynamic_cast<SinglePlayerSettings*>(prev), resources.get());
		break;
	case gameStateNumber::multiPlayerSettings:
		delete prev;
		prev = current;
		current = new MultiPlayerSettings(resources.get());
		break;
	case gameStateNumber::changeIP:
		prev = current;
		current = new ChangeIP(dynamic_cast<MultiPlayerSettings*>(prev), resources.get());
		break;
	case gameStateNumber::multiPlayer:
		delete prev;
		prev = current;
		try
		{
			current = new MultiPlayer(dynamic_cast<MultiPlayerSettings*>(prev), resources.get());
		}
		catch (std::wstring error)
		{
			delete current;
			current = new Error(error, resources.get());
			prev = nullptr;
		}
		break;
	case gameStateNumber::endgame:
		delete prev;
		prev = current;
		if (dynamic_cast<MultiPlayer*>(prev) == nullptr)
			current = new Endgame(dynamic_cast<SinglePlayer*>(prev), resources.get());
		else
			current = new Endgame(dynamic_cast<MultiPlayer*>(prev), resources.get());
		break;
	case gameStateNumber::menu:
		delete prev;
		prev = nullptr;
		delete current;
		current = new Menu(resources.get());
		break;
	case gameStateNumber::changeName:
		delete prev;
		prev = current;
		current = new ChangeName(resources.get());
		break;
	case gameStateNumber::instruction:
		delete prev;
		prev = current;
		current = new Instruction(resources.get());
		break;
	case gameStateNumber::quit:
		return false;
		break;
	case gameStateNumber::setSuit:
		prev = current;
		current = new SetSuit(dynamic_cast<Game*>(prev), resources.get());
		break;
	case gameStateNumber::setFigure:
		prev = current;
		current = new SetFigure(dynamic_cast<Game*>(prev), resources.get());
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
