#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
	this->resolution = sf::VideoMode::getDesktopMode();
	this->title = "WINDOW WITH DEFAULT GRAPHICS SETTINGS";
	this->contextSettings.antialiasingLevel = 0;
	this->fullscreen = false;
	this->verticalSync = false;
	this->framerateLimit = 60;
	this->gridPixelsSize = 48;
	this->position.first = 240;
	this->position.second = 180;
}

void GraphicsSettings::saveToFile(const std::string& path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->framerateLimit;
		ofs << this->verticalSync;
		ofs << this->contextSettings.antialiasingLevel;
		ofs << this->gridPixelsSize;
		ofs << this->position.first;
		ofs << this->position.second;
	}
	else
	{
		std::cout << "ERROR: void GraphicsSettings::saveToFile: CANNOT OPEN: " << path << '\n';
		exit(41);
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string& path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->framerateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
		ifs >> this->gridPixelsSize;
		ifs >> this->position.first;
		ifs >> this->position.second;
	}
	else
	{
		std::cout << "ERROR: void GraphicsSettings::loadFromFile: CANNOT OPEN: " << path << '\n';
		exit(41);
	}

	ifs.close();
}
