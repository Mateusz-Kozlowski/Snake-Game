#pragma once

#include "GraphicsSettings.h"
#include "ResourceManager.h"

class State;

class StateData
{
public:
	StateData()
	{
		this->gfxSettings = nullptr;
		this->window = nullptr;
		this->supportedKeys = nullptr;
		this->states = nullptr;
	}

	GraphicsSettings* gfxSettings;
	sf::RenderWindow* window;
	std::unordered_map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
protected:
	StateData* stateData;

	std::unordered_map<std::string, int> keybinds;
	std::unordered_map<std::string, bool> keysBlockades;

	bool quit;
	bool paused;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;

	virtual void initKeybinds() = 0;

public:
	State(StateData* stateData);
	virtual ~State() = 0;
	
	bool getQuit() const;
	void endState();
	void pauseState();
	void unpauseState();
	void updateMousePositions();
	void updateKeysBlockade();
	
	virtual void isStatesStackTopAgain() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};
