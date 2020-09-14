#include "stdafx.h"
#include "State.h"

State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->quit = false;
	this->paused = false;
}

State::~State()
{

}

bool State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->stateData->window);
}

void State::updateKeysBlockade()
{
	for (auto& it : this->keybinds)
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(it.second)))
			this->keysBlockades[it.first] = false;
}