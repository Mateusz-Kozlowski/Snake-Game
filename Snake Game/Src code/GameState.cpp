#include "stdafx.h"
#include "GameState.h"

void GameState::initVariables()
{
	// default values:
	this->numberOfFruits = 1;
	this->delay = 0.25f;

	// reading from file:
	std::fstream file("Config\\game.ini", std::ios::in);

	if (file.is_open())
	{
		file >> this->numberOfFruits;
		file >> this->delay;
	}
	else
	{
		std::cout << "ERROR: void GameState::initVariables: CANNOT OPEN: Config\\game.ini\n";
		exit(41);
	}
	
	file.close();
	
	this->timer = 0.f;

	this->gameOver = false;
}

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/game_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
			this->keybinds[key] = this->stateData->supportedKeys->at(key2);
	}
	else
	{
		std::cout << "ERROR: void GameState::initKeybinds: CANNOT OPEN FILE: Config/game_keybinds.ini\n";
		exit(41);
	}

	ifs.close();

	for (auto& it : this->keybinds)
		this->keysBlockades[it.first] = true;
}

void GameState::initPauseMenu()
{
	this->font = ResourceManager::acquireFont("Resources\\Fonts\\Retroica.ttf");

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addText(gui::p2pY(10.f, vm), gui::calcCharSize(vm), "PAUSED", sf::Color::White);
	
	this->pmenu->addText(gui::p2pY(43.5f, vm), gui::calcCharSize(vm, 70), "SPEED MODIFIER", sf::Color::White);
	this->pmenu->addModifier(
		"SPEED_MODIFIER",
		gui::p2pY(53.f, vm), 0.125f, 0.5f, true,
		"Resources\\Textures\\Modifier\\axis.png", "Resources\\Textures\\Modifier\\handle.png",
		"Resources\\Textures\\Modifier\\axisHovered.png", "Resources\\Textures\\Modifier\\handleHovered.png",
		"Resources\\Textures\\Modifier\\axisPressed.png", "Resources\\Textures\\Modifier\\handlePressed.png"
	);
	this->pmenu->getModifier("SPEED_MODIFIER").setValue(this->delay);
	this->pmenu->getModifier("SPEED_MODIFIER").setMinimizeToZero(true);

	this->pmenu->addButton(
		"CONTINUE", gui::p2pY(74.f, vm), gui::p2pX(14.f, vm), gui::p2pY(6.f, vm),
		gui::calcCharSize(vm, 70), "CONTINUE",
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(200, 200, 200, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 100)
	);
	
	this->pmenu->addButton(
		"QUIT", gui::p2pY(84.f, vm), gui::p2pX(14.f, vm), gui::p2pY(6.f, vm),
		gui::calcCharSize(vm, 70), "QUIT",
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(200, 200, 200, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 100)
	);
}

void GameState::initArena()
{
	delete this->arena;
	this->arena = new Arena(
		this->stateData->window->getSize().x / this->stateData->gfxSettings->gridPixelsSize,
		this->stateData->window->getSize().y / this->stateData->gfxSettings->gridPixelsSize,
		this->stateData->gfxSettings->gridPixelsSize,
		this->numberOfFruits
	);
}

void GameState::initGameOverMenu()
{
	delete this->gameOverMenu;

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->gameOverMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->gameOverMenu->addText(gui::p2pY(10.f, vm), gui::calcCharSize(vm), "GAME OVER", sf::Color::White);

	this->gameOverMenu->addText(gui::p2pY(43.f, vm), gui::calcCharSize(vm, 70), "YOUR SCORE", sf::Color::White);

	this->gameOverMenu->addText(gui::p2pY(51.f, vm), gui::calcCharSize(vm, 70), std::to_string(this->arena->getSnake().getBodyPos().size() - 1), sf::Color::White);

	this->gameOverMenu->addButton(
		"RESTART", gui::p2pY(74.f, vm), gui::p2pX(14.f, vm), gui::p2pY(6.f, vm),
		gui::calcCharSize(vm, 70), "RESTART",
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(200, 200, 200, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 100)
	);

	this->gameOverMenu->addButton(
		"QUIT", gui::p2pY(84.f, vm), gui::p2pX(14.f, vm), gui::p2pY(6.f, vm),
		gui::calcCharSize(vm, 70), "QUIT",
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(200, 200, 200, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 100)
	);
}

GameState::GameState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initDeferredRender();
	this->initKeybinds();
	this->initPauseMenu();
	this->initArena();
}

GameState::~GameState()
{
	std::fstream file("Config\\game.ini", std::ios::out);

	if (file.is_open())
	{
		file << this->numberOfFruits << '\n';

		if (this->delay > 0.5f)
			this->delay = 0.5f;
		else if (this->delay < 0.f)
			this->delay = 0.f;

		file << this->delay;
	}
	else
	{
		std::cout << "ERROR: GameState::~GameState: CANNOT OPEN: Config\\game.ini\n";
		exit(41);
	}

	file.close();

	delete this->pmenu;
	delete this->arena;
	ResourceManager::murderTextureOrphans();
	ResourceManager::murderFontOrphans();
}

void GameState::updateDelay(const float& dt)
{
	this->timer += dt;
}

void GameState::isStatesStackTopAgain()
{
	for (auto& it : this->keybinds)
		this->keysBlockades[it.first] = true;

	for (auto& it : this->pmenu->getButtons())
		it.second->setClickBlockade(true);

	for (auto& it : this->pmenu->getButtons())
		it.second->setIdle();
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])) && !this->keysBlockades["CLOSE"])
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();

		this->keysBlockades["CLOSE"] = true;
	}
}

void GameState::updatePlayerInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_UP"])))
		this->arena->getSnake().changeDir(Direction::UP);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_DOWN"])))
		this->arena->getSnake().changeDir(Direction::DOWN);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_LEFT"])))
		this->arena->getSnake().changeDir(Direction::LEFT);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_RIGHT"])))
		this->arena->getSnake().changeDir(Direction::RIGHT);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_UP_WASD"])))
		this->arena->getSnake().changeDir(Direction::UP);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_DOWN_WASD"])))
		this->arena->getSnake().changeDir(Direction::DOWN);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_LEFT_WASD"])))
		this->arena->getSnake().changeDir(Direction::LEFT);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_RIGHT_WASD"])))
		this->arena->getSnake().changeDir(Direction::RIGHT);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonClicked("QUIT"))
		this->endState();

	else if (this->pmenu->isButtonClicked("CONTINUE"))
		this->paused = false;
}

void GameState::update(const float& dt)
{
	this->updateKeysBlockade();
	this->updateDelay(dt);
	this->updateMousePositions();
	this->updateInput(dt);

	if (this->arena->getGameOver() && !this->gameOver)
	{
		this->initGameOverMenu();
		this->gameOver = true;
	}

	if (this->gameOver)
	{
		this->gameOverMenu->update(this->mousePosWindow);

		if (this->gameOverMenu->isButtonClicked("RESTART"))
		{
			this->timer = 0.f;
			this->initArena();
			this->gameOver = false;
			return;
		}
		else if (this->gameOverMenu->isButtonClicked("QUIT"))
			this->endState();
	}
	else if (!this->paused) //Unpaused update
	{
		this->updatePlayerInput();

		if (this->timer >= this->delay)
		{
			this->timer = 0.f;
			this->arena->update();
		}
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
		this->delay = this->pmenu->getModifier("SPEED_MODIFIER").getValue();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->stateData->window;

	this->renderTexture.clear();

	this->arena->render(this->renderTexture);
	
	if (this->gameOver)
		this->gameOverMenu->render(this->renderTexture);
	else if (this->paused)
		this->pmenu->render(this->renderTexture);

	// FINAL RENDER:
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
