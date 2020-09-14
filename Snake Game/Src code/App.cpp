#include "stdafx.h"
#include "App.h"

void App::initVariables()
{
	this->dt = 0.f;
}

void App::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void App::initWindow()
{
	if (this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings
		);
	else
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings
		);

	this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
	this->window->setPosition(
		sf::Vector2i(
			this->gfxSettings.position.first, 
			this->gfxSettings.position.second
		)
	);
}

void App::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
			this->supportedKeys[key] = key_value;
	}
	else
	{
		std::cout << "ERROR: void App::initKeys: CANNOT OPEN: Config/supported_keys.ini\n";
		exit(41);
	}

	ifs.close();
}

void App::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
}

void App::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

App::App()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

App::~App()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void App::updateDt()
{
	this->dt = this->clock.restart().asSeconds();
}

void App::updateFps()
{
	if (rand() % static_cast<int>(1.f / this->dt) == 1)
		std::cout << static_cast<int>(1.f / this->dt) << '\n';
}

void App::updateEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			this->window->close();
}

void App::update()
{
	//this->updateFps();
	this->updateEvents();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();

				if (!this->states.empty())
					this->states.top()->isStatesStackTopAgain();
			}
		}
	}

	if (this->states.empty())
		this->window->close();
}

void App::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void App::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
