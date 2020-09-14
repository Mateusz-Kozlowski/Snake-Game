#pragma once

#include "Gui.h"

class PauseMenu
{
private:
	sf::VideoMode& vm;
	std::shared_ptr<sf::Font> font;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Modifier*> speedModifiers;
	std::vector<sf::Text> texts;
	
public:
	PauseMenu(sf::VideoMode& vm, std::shared_ptr<sf::Font> font);
	~PauseMenu();

	std::map<std::string, gui::Button*>& getButtons();
	gui::Modifier& getModifier(std::string key);

	bool isButtonClicked(std::string key);

	void addButton(
		std::string key,
		float posY,
		float width, float height,
		int charSize, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,
		sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlinePressedColor,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textPressedColor,
		float outlineThickness = 1.f, short unsigned id = 0
	);
	void addModifier(
		std::string key,
		float posY,
		float textureScale,
		float maxValue, bool maxOnLeft,
		std::string axis_idle_path, std::string handle_idle_path,
		std::string axis_hover_path, std::string handle_hover_path,
		std::string axis_pressed_path, std::string handle_pressed_path
	);
	void addText(float posY, unsigned charSize, std::string text, sf::Color textColor);

	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget& target);
};

