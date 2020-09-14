#pragma once

#include "State.h"
#include "Gui.h"

class SettingsState : public State
{
private:
	std::shared_ptr<sf::Texture> backgroundTexture;
	sf::Sprite background;

	std::shared_ptr<sf::Font> font;

	std::unordered_map<std::string, gui::Button*> buttons;
	std::unordered_map<std::string, gui::Modifier*> modifiers;
	
	int gameFruitsQuantity;
	float gameDelay;
	
	int fakeAiFruitsQuantity;
	float fakeAiDelay;

	void initFonts();
	void initKeybinds();
	void initBackground();
	void initVariables();
	void initGui();
	void initGameStateSettings();
	void initFakeAiSettings();

public:
	SettingsState(StateData* stateData);
	~SettingsState();

	void isStatesStackTopAgain();
	void updateInput(const float& dt);
	void updateGui();
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};
