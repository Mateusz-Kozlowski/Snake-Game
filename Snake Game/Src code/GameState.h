#pragma once

#include "State.h"
#include "Arena.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	std::shared_ptr<sf::Font> font;
	PauseMenu* pmenu;
	PauseMenu* gameOverMenu;
	int numberOfFruits;
	Arena* arena;

	float delay;
	float timer;

	bool gameOver;

	void initVariables();
	void initDeferredRender();
	void initKeybinds();
	void initPauseMenu();
	void initArena();
	void initGameOverMenu();

public:
	GameState(StateData* stateData);
	~GameState();

	void updateDelay(const float& dt);
	void isStatesStackTopAgain();
	void updateInput(const float& dt);
	void updatePlayerInput();
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

