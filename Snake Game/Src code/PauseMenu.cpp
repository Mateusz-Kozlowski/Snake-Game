#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, std::shared_ptr<sf::Font> font)
	: vm(vm), font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 220));
	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		0.f
	);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	for (auto it = this->speedModifiers.begin(); it != this->speedModifiers.end(); ++it)
		delete it->second;
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

gui::Modifier& PauseMenu::getModifier(std::string key)
{
	return *this->speedModifiers[key];
}

bool PauseMenu::isButtonClicked(std::string key)
{
	return this->buttons[key]->isClicked();
}

void PauseMenu::addButton(
	std::string key,
	float posY,
	float width, float height,
	int charSize, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlinePressedColor,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textPressedColor,
	float outlineThickness, short unsigned id)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, posY, width, height,
		this->font, text, charSize,
		idleColor, hoverColor, pressedColor,
		outlineIdleColor, outlineHoverColor, outlinePressedColor,
		textIdleColor, textHoverColor, textPressedColor,
		outlineThickness, id
	);
}

void PauseMenu::addModifier(
	std::string key,
	float posY,
	float textureScale,
	float maxValue, bool max_on_the_left,
	std::string axis_idle_path, std::string handle_idle_path,
	std::string axis_hover_path, std::string handle_hover_path,
	std::string axis_pressed_path, std::string handle_pressed_path)
{
	this->speedModifiers[key] = new gui::Modifier(
		gui::p2pX(50, vm), posY, textureScale, maxValue, max_on_the_left,
		axis_idle_path, handle_idle_path,
		axis_hover_path, handle_hover_path,
		axis_pressed_path, handle_pressed_path
	);
}

void PauseMenu::addText(float posY, unsigned charSize, std::string text, sf::Color textColor)
{
	sf::Text temp;
	temp.setFont(*this->font);
	temp.setCharacterSize(charSize);
	temp.setString(text);
	temp.setFillColor(textColor);
	temp.setPosition(gui::p2pX(50, this->vm) - temp.getGlobalBounds().width / 2.f, posY);	
	this->texts.push_back(temp);
}

void PauseMenu::update(sf::Vector2i mousePosWindow)
{
	for (auto& i : this->buttons)
		i.second->update(mousePosWindow);

	for (auto& i : this->speedModifiers)
		i.second->update(mousePosWindow);
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
		i.second->render(target);
	
	for (auto& i : this->speedModifiers)
		i.second->render(target);

	for (auto& i : this->texts)
		target.draw(i);
}
