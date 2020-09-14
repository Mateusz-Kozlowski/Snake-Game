#pragma once

enum class GridState { ILDE = 0, SNAKE, FRUIT };

#include "Snake.h"
#include "Fruit.h"

class Arena
{
private:
	sf::Color idleColor;
	sf::Color snakeColor;
	sf::Color fruitColor;
	
	std::pair<int, int> dimensions;
	
	std::vector<std::vector<GridState> > gridsStates;
	std::vector<std::vector<sf::RectangleShape> > rectangles;
	
	Snake* snake;
	std::vector<Fruit> fruits;

	bool gameOver;
	
	bool isSpawnFruitPossible() const;
	Fruit spawnFruit();

public:
	Arena(unsigned width, unsigned height, unsigned tilePixelSize, unsigned numberOfFruits = 1);
	~Arena();
	
	bool getGameOver() const;

	Snake& getSnake() const;
	std::pair<int, int> getDimensions() const;
	
	void restart();
	void update();
	void render(sf::RenderTarget& target);
};

