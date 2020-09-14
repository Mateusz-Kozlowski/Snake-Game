#pragma once

#include "GameState.h"
#include "FakeAiState.h"
#include "SettingsState.h"

class MainMenuState : public State
{
private:
	std::shared_ptr<sf::Texture> backgroundTexture;
	sf::Sprite background;

	std::shared_ptr<sf::Font> font;

	std::unordered_map<std::string, gui::Button*> buttons;

	void initFonts();
	void initKeybinds();
	void initBackground();
	void initButtons();

public:
	MainMenuState(StateData* stateData);
	~MainMenuState();

	void isStatesStackTopAgain();
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};
