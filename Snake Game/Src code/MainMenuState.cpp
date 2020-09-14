#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	this->font = ResourceManager::acquireFont("Resources\\Fonts\\Retroica.ttf");
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/main_menu_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
			this->keybinds[key] = this->stateData->supportedKeys->at(key2);
	}
	else
	{
		std::cout << "ERROR: void MainMenuState::initKeybinds: CANNOT OPEN: Config/main_menu_keybinds.ini\n";
		exit(41);
	}

	ifs.close();

	for (auto& it : this->keybinds)
		this->keysBlockades[it.first] = true;
}

void MainMenuState::initBackground()
{
	this->backgroundTexture = ResourceManager::acquireTexture("Resources\\Textures\\Backgrounds\\bg0.png");
	this->background.setTexture(*this->backgroundTexture);
	this->background.setScale(
		sf::Vector2f(
			static_cast<float>(this->stateData->window->getSize().x) / this->background.getGlobalBounds().width,
			static_cast<float>(this->stateData->window->getSize().y) / this->background.getGlobalBounds().height
		)
	);
}

void MainMenuState::initButtons()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(41.f, vm), gui::p2pY(17.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(12.f, vm),
		this->font, "PLAY", gui::calcCharSize(vm, 47),
		sf::Color(75, 75, 75, 255), sf::Color(125, 125, 125, 255), sf::Color(50, 50, 50, 255),
		sf::Color(125, 125, 125, 255), sf::Color(175, 175, 175, 255), sf::Color(100, 100, 100, 255),
		sf::Color(225, 225, 225, 255), sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255),
		gui::p2pY(0.5f, vm), 0
	);

	this->buttons["FAKE_AI_STATE"] = new gui::Button(
		gui::p2pX(41.f, vm), gui::p2pY(35.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(12.f, vm),
		this->font, "FAKE AI", gui::calcCharSize(vm, 47),
		sf::Color(75, 75, 75, 255), sf::Color(125, 125, 125, 255), sf::Color(50, 50, 50, 255),
		sf::Color(125, 125, 125, 255), sf::Color(175, 175, 175, 255), sf::Color(100, 100, 100, 255),
		sf::Color(225, 225, 225, 255), sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255),
		gui::p2pY(0.5f, vm), 1
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(41.f, vm), gui::p2pY(53.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(12.f, vm),
		this->font, "SETTINGS", gui::calcCharSize(vm, 47),
		sf::Color(75, 75, 75, 255), sf::Color(125, 125, 125, 255), sf::Color(50, 50, 50, 255),
		sf::Color(125, 125, 125, 255), sf::Color(175, 175, 175, 255), sf::Color(100, 100, 100, 255),
		sf::Color(225, 225, 225, 255), sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255),
		gui::p2pY(0.5f, vm), 3
	);	

	this->buttons["EXIT"] = new gui::Button(
		gui::p2pX(41.f, vm), gui::p2pY(71.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(12.f, vm),
		this->font, "EXIT", gui::calcCharSize(vm, 47),
		sf::Color(75, 75, 75, 255), sf::Color(125, 125, 125, 255), sf::Color(50, 50, 50, 255),
		sf::Color(125, 125, 125, 255), sf::Color(175, 175, 175, 255), sf::Color(100, 100, 100, 255),
		sf::Color(225, 225, 225, 255), sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255),
		gui::p2pY(0.5f, vm), 4
	);
}

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	this->initFonts();
	this->initKeybinds();
	this->initBackground();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	ResourceManager::murderTextureOrphans();
	ResourceManager::murderFontOrphans();
}

void MainMenuState::isStatesStackTopAgain()
{
	for (auto& it : this->keybinds)
		this->keysBlockades[it.first] = true;

	for (auto& it : this->buttons)
		it.second->setClickBlockade(true);

	for (auto& it : this->buttons)
		it.second->setIdle();
}

void MainMenuState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])) && !this->keysBlockades["CLOSE"])
		this->endState();
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosWindow);

	if (this->buttons["GAME_STATE"]->isClicked())
		this->stateData->states->push(new GameState(this->stateData));

	else if (this->buttons["FAKE_AI_STATE"]->isClicked())
		this->stateData->states->push(new FakeAiState(this->stateData));

	else if (this->buttons["SETTINGS_STATE"]->isClicked())
		this->stateData->states->push(new SettingsState(this->stateData));

	else if (this->buttons["EXIT"]->isClicked())
		this->endState();			
}

void MainMenuState::update(const float& dt)
{
	this->updateKeysBlockade();
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->stateData->window;

	target->draw(this->background);

	this->renderButtons(*target);
}
