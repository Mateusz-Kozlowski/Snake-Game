#pragma once

#include "State.h"
#include "Arena.h"
#include "PauseMenu.h"
#include "PathFinder.h"

class FakeAiState : public State
{
private:
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	std::shared_ptr<sf::Font> font;
	PauseMenu* pmenu;
	PauseMenu* gameOverMenu;
	int numberOfFruits;
	Arena* arena;
	PathFinder* pathFinder;

	float delay;
	float timer;

	bool gameOver;

	void initVariables();
	void initDeferredRender();
	void initKeybinds();
	void initPauseMenu();
	void initArena();
	void initPathFinder();
	void initGameOverMenu();

public:
	FakeAiState(StateData* stateData);
	~FakeAiState();

	void updateDelay(const float& dt);
	void isStatesStackTopAgain();
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void askPathFinder();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};
