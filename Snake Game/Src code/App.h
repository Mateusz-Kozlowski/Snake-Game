#pragma once

#include "MainMenuState.h"

class App
{
private:
	GraphicsSettings gfxSettings;
	sf::RenderWindow* window;
	std::unordered_map<std::string, int> supportedKeys;
	std::stack<State*> states;

	StateData stateData;

	sf::Clock clock;
	float dt;
	
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	App();
	~App();
	
	void updateDt();
	void updateFps();
	void updateEvents();
	void update();
	void render();
	void run();
};
