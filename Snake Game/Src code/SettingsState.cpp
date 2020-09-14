#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	std::fstream gameFile("Config\\game.ini", std::ios::in);

	if (gameFile.is_open())
	{
		gameFile >> this->gameFruitsQuantity;
		gameFile >> this->gameDelay;
	}
	else
	{
		std::cout << "ERROR: void SettingsState::initVariables: CANNOT OPEN: Config\\game.ini\n";
		exit(41);
	}

	gameFile.close();

	std::fstream fakeAiFile("Config\\fake_ai.ini", std::ios::in);

	if (fakeAiFile.is_open())
	{
		fakeAiFile >> this->fakeAiFruitsQuantity;
		fakeAiFile >> this->fakeAiDelay;
	}
	else
	{
		std::cout << "ERROR: void SettingsState::initVariables: CANNOT OPEN: Config\\fake_ai.ini\n";
		exit(41);
	}

	fakeAiFile.close();
}

void SettingsState::initFonts()
{
	this->font = ResourceManager::acquireFont("Resources\\Fonts\\Retroica.ttf");
}

void SettingsState::initKeybinds()
{
	
}

void SettingsState::initBackground()
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

void SettingsState::initGui()
{
	this->initGameStateSettings();
	this->initFakeAiSettings();

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(60.f, vm), gui::p2pY(80.f, vm),
		gui::p2pX(15.f, vm), gui::p2pY(10.f, vm),
		this->font, "APPLY", gui::calcCharSize(vm, 50),
		sf::Color(75, 75, 75, 255), sf::Color(125, 125, 125, 255), sf::Color(50, 50, 50, 255),
		sf::Color(125, 125, 125, 255), sf::Color(175, 175, 175, 255), sf::Color(100, 100, 100, 255),
		sf::Color(225, 225, 225, 255), sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255),
		gui::p2pY(0.5f, vm)
	);

	this->buttons["QUIT"] = new gui::Button(
		gui::p2pX(80.f, vm), gui::p2pY(80.f, vm),
		gui::p2pX(15.f, vm), gui::p2pY(10.f, vm),
		this->font, "QUIT", gui::calcCharSize(vm, 50),
		sf::Color(75, 75, 75, 255), sf::Color(125, 125, 125, 255), sf::Color(50, 50, 50, 255),
		sf::Color(125, 125, 125, 255), sf::Color(175, 175, 175, 255), sf::Color(100, 100, 100, 255),
		sf::Color(225, 225, 225, 255), sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255),
		gui::p2pY(0.5f, vm)
	);
}

void SettingsState::initGameStateSettings()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	
	this->buttons["GAME_FRUITS"] = new gui::Button(
		gui::p2pX(44.f, vm), gui::p2pY(15.f, vm),
		gui::p2pX(12.f, vm), gui::p2pY(8.f, vm),
		this->font, "GAME FRUITS", gui::calcCharSize(vm),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->modifiers["GAME_FRUITS"] = new gui::Modifier(
		gui::p2pX(50.f, vm), gui::p2pY(27.5f, vm),
		0.125f, 9.f, false,
		"Resources\\Textures\\Modifier\\axis.png", "Resources\\Textures\\Modifier\\handle.png",
		"Resources\\Textures\\Modifier\\axisHovered.png", "Resources\\Textures\\Modifier\\handleHovered.png",
		"Resources\\Textures\\Modifier\\axisPressed.png", "Resources\\Textures\\Modifier\\handlePressed.png"
	);

	this->modifiers["GAME_FRUITS"]->setValue(this->gameFruitsQuantity);

	this->buttons["GAME_FRUITS_QUANTITY"] = new gui::Button(
		gui::p2pX(44.f, vm), gui::p2pY(32.f, vm),
		gui::p2pX(12.f, vm), gui::p2pY(8.f, vm),
		this->font, std::to_string(this->gameFruitsQuantity), gui::calcCharSize(vm),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
}

void SettingsState::initFakeAiSettings()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["FAKE_AI_FRUITS"] = new gui::Button(
		gui::p2pX(44.f, vm), gui::p2pY(45.f, vm),
		gui::p2pX(12.f, vm), gui::p2pY(8.f, vm),
		this->font, "FAKE AI FRUITS", gui::calcCharSize(vm),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->modifiers["FAKE_AI_FRUITS"] = new gui::Modifier(
		gui::p2pX(50, vm), gui::p2pY(57.5f, vm),
		0.125f, 9.f, false,
		"Resources\\Textures\\Modifier\\axis.png", "Resources\\Textures\\Modifier\\handle.png",
		"Resources\\Textures\\Modifier\\axisHovered.png", "Resources\\Textures\\Modifier\\handleHovered.png",
		"Resources\\Textures\\Modifier\\axisPressed.png", "Resources\\Textures\\Modifier\\handlePressed.png"
	);

	this->modifiers["FAKE_AI_FRUITS"]->setValue(this->fakeAiFruitsQuantity);

	this->buttons["FAKE_AI_FRUITS_QUANTITY"] = new gui::Button(
		gui::p2pX(44.f, vm), gui::p2pY(62.f, vm),
		gui::p2pX(12.f, vm), gui::p2pY(8.f, vm),
		this->font, std::to_string(this->fakeAiFruitsQuantity), gui::calcCharSize(vm),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
}

SettingsState::SettingsState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initBackground();
	this->initGui();
}

SettingsState::~SettingsState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	for (auto it = this->modifiers.begin(); it != this->modifiers.end(); ++it)
		delete it->second;

	ResourceManager::murderTextureOrphans();
	ResourceManager::murderFontOrphans();
}

void SettingsState::isStatesStackTopAgain()
{
	for (auto& it : this->buttons)
		it.second->setClickBlockade(true);

	for (auto& it : this->buttons)
		it.second->setIdle();
}

void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosWindow);

	for (auto& it : this->modifiers)
		it.second->update(this->mousePosWindow);

	this->gameFruitsQuantity = round(this->modifiers["GAME_FRUITS"]->getValue());
	if (this->gameFruitsQuantity == 0)
		this->gameFruitsQuantity = 1;
	this->buttons["GAME_FRUITS_QUANTITY"]->setText(std::to_string(this->gameFruitsQuantity));

	this->fakeAiFruitsQuantity = round(this->modifiers["FAKE_AI_FRUITS"]->getValue());
	if (this->fakeAiFruitsQuantity == 0)
		this->fakeAiFruitsQuantity = 1;
	this->buttons["FAKE_AI_FRUITS_QUANTITY"]->setText(std::to_string(this->fakeAiFruitsQuantity));
	
	if (this->buttons["APPLY"]->isClicked())
	{
		std::fstream gameFile("Config\\game.ini", std::ios::out);

		if (gameFile.is_open())
		{
			gameFile << this->gameFruitsQuantity << '\n';

			if (this->gameDelay > 0.5f)
				this->gameDelay = 0.5f;
			else if (this->gameDelay < 0.f)
				this->gameDelay = 0.f;

			gameFile << this->gameDelay;
		}
		else
		{
			std::cout << "ERROR: void SettingsState::updateGui: CANNOT OPEN: Config\\game.ini\n";
			exit(41);
		}

		gameFile.close();

		std::fstream fakeAiFile("Config\\fake_ai.ini", std::ios::out);

		if (fakeAiFile.is_open())
		{
			fakeAiFile << this->fakeAiFruitsQuantity << '\n';

			if (this->fakeAiDelay > 0.5f)
				this->fakeAiDelay = 0.5f;
			else if (this->fakeAiDelay < 0.f)
				this->fakeAiDelay = 0.f;

			fakeAiFile << this->fakeAiDelay << '\n';
		}
		else
		{
			std::cout << "ERROR: void SettingsState::updateGui: CANNOT OPEN FILE: Config\\fake_ai.ini\n";
			exit(41);
		}

		fakeAiFile.close();
	}

	if (this->buttons["QUIT"]->isClicked())
		this->endState();
}

void SettingsState::update(const float& dt)
{
	this->updateKeysBlockade();
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGui();
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
		it.second->render(target);

	for (auto& it : this->modifiers)
		it.second->render(target);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->stateData->window;

	target->draw(this->background);

	this->renderGui(*target);
}
