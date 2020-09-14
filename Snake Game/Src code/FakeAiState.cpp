#include "stdafx.h"
#include "FakeAiState.h"

void FakeAiState::initVariables()
{
	// defalut values:
	this->numberOfFruits = 1;
	this->delay = 0.25f;

	std::fstream file("Config\\fake_ai.ini", std::ios::in);
	
	if (file.is_open())
	{
		file >> this->numberOfFruits;
		file >> this->delay;
	}
	else
	{
		std::cout << "ERROR: void FakeAiState::initVariables: CANNOT OPEN: Config\\fake_ai.ini'\n";
		exit(41);
	}

	file.close();
	
	this->timer = 0.f;

	this->gameOver = false;
}

void FakeAiState::initDeferredRender()
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

void FakeAiState::initKeybinds()
{
	std::ifstream ifs("Config/fake_ai_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
			this->keybinds[key] = this->stateData->supportedKeys->at(key2);
	}
	else
	{
		std::cout << "ERROR: void FakeAiState::initKeybinds: CANNOT OPEN: Config/fake_ai_keybinds.ini\n";
		exit(41);
	}

	ifs.close();

	for (auto& it : this->keybinds)
		this->keysBlockades[it.first] = true;
}

void FakeAiState::initPauseMenu()
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

	// buttons:
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

void FakeAiState::initArena()
{
	delete this->arena;
	this->arena = new Arena(
		this->stateData->window->getSize().x / this->stateData->gfxSettings->gridPixelsSize,
		this->stateData->window->getSize().y / this->stateData->gfxSettings->gridPixelsSize,
		this->stateData->gfxSettings->gridPixelsSize,
		this->numberOfFruits
	);
	this->arena->getSnake().resetDir();
}

void FakeAiState::initPathFinder()
{
	this->pathFinder = new PathFinder("Config\\fake_ai_path.ini");
}

void FakeAiState::initGameOverMenu()
{
	delete this->gameOverMenu;

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->gameOverMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->gameOverMenu->addText(gui::p2pY(10.f, vm), gui::calcCharSize(vm), "GAME OVER", sf::Color::White);

	this->gameOverMenu->addText(gui::p2pY(43.f, vm), gui::calcCharSize(vm, 70), "FAKE AI SCORE", sf::Color::White);

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

FakeAiState::FakeAiState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initDeferredRender();
	this->initKeybinds();
	this->initPauseMenu();
	this->initArena();
	this->initPathFinder();
}

FakeAiState::~FakeAiState()
{
	std::fstream file("Config\\fake_ai.ini", std::ios::out);

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
		std::cout << "ERROR: FakeAiState::~FakeAiState: CANNOT OPEN: Config\\fake_ai.ini'\n";
		exit(41);
	}

	file.close();

	delete this->pmenu;
	delete this->arena;
	delete this->pathFinder;
	ResourceManager::murderTextureOrphans();
	ResourceManager::murderFontOrphans();
}

void FakeAiState::updateDelay(const float& dt)
{
	this->timer += dt;
}

void FakeAiState::isStatesStackTopAgain()
{
	for (auto& it : this->keybinds)
		this->keysBlockades[it.first] = true;

	for (auto& it : this->pmenu->getButtons())
		it.second->setClickBlockade(true);

	for (auto& it : this->pmenu->getButtons())
		it.second->setIdle();
}

void FakeAiState::updateInput(const float& dt)
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

void FakeAiState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonClicked("QUIT"))
		this->endState();

	else if (this->pmenu->isButtonClicked("CONTINUE"))
		this->paused = false;
}

void FakeAiState::askPathFinder()
{
	std::pair<int, int> temp = this->pathFinder->getNextNode(this->arena->getSnake().getBodyPos()[0]);

	if (temp.first + 1 == this->arena->getSnake().getBodyPos()[0].first)
		this->arena->getSnake().changeDir(Direction::LEFT);

	else if (temp.first - 1 == this->arena->getSnake().getBodyPos()[0].first)
		this->arena->getSnake().changeDir(Direction::RIGHT);

	else if (temp.second + 1 == this->arena->getSnake().getBodyPos()[0].second)
		this->arena->getSnake().changeDir(Direction::UP);

	else if (temp.second - 1 == this->arena->getSnake().getBodyPos()[0].second)
		this->arena->getSnake().changeDir(Direction::DOWN);

	else if (temp.first == 0 && this->arena->getSnake().getBodyPos()[0].first == this->arena->getDimensions().first - 1)
		this->arena->getSnake().changeDir(Direction::RIGHT);

	else if (temp.first == this->arena->getDimensions().first - 1 && this->arena->getSnake().getBodyPos()[0].first == 0)
		this->arena->getSnake().changeDir(Direction::LEFT);

	else if (temp.second == 0 && this->arena->getSnake().getBodyPos()[0].second == this->arena->getDimensions().second - 1)
		this->arena->getSnake().changeDir(Direction::DOWN);

	else if (temp.second == this->arena->getDimensions().second - 1 && this->arena->getSnake().getBodyPos()[0].second == 0)
		this->arena->getSnake().changeDir(Direction::UP);

	else
	{
		std::cout << "NIE WYBRANO POLA!\n";
		std::cout << "OBECNE POLE: " << this->arena->getSnake().getBodyPos()[0].first << ' ' << this->arena->getSnake().getBodyPos()[0].second << '\n';
		std::cout << "NASTEPNE POLE: " << temp.first << ' ' << temp.second << '\n';
		exit(41);
	}
}

void FakeAiState::update(const float& dt)
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
		if (this->timer >= this->delay)
		{
			this->timer = 0.f;
			this->askPathFinder();
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

void FakeAiState::render(sf::RenderTarget* target)
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
