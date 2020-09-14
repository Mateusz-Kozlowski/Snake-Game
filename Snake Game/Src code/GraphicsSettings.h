#pragma once

class GraphicsSettings
{
public:
	std::vector<sf::VideoMode> videoModes;
	sf::VideoMode resolution;
	std::string title;
	sf::ContextSettings contextSettings;
	bool fullscreen;
	bool verticalSync;
	unsigned framerateLimit;
	unsigned gridPixelsSize;
	std::pair<int, int> position;

	GraphicsSettings();

	void saveToFile(const std::string& path);
	void loadFromFile(const std::string& path);
};
