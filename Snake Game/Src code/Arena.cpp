#include "stdafx.h"
#include "Arena.h"

bool Arena::isSpawnFruitPossible() const
{
	if (this->dimensions.first * this->dimensions.second >= this->snake->getBodyPos().size() + this->fruits.size())
		return true;
	return false;
}

Fruit Arena::spawnFruit()
{
	int x, y;
	do
	{
		x = rand() % this->dimensions.first;
		y = rand() % this->dimensions.second;

	} while (this->gridsStates[y][x] != GridState::ILDE);

	this->gridsStates[y][x] = GridState::FRUIT;
	this->rectangles[y][x].setFillColor(this->fruitColor);

	Fruit temp(x, y);
	return temp;
}

Arena::Arena(unsigned width, unsigned height, unsigned tilePixelSize, unsigned numberOfFruits)
{
	this->idleColor = sf::Color(50, 50, 50, 255);
	this->snakeColor = sf::Color(200, 0, 0, 255);
	this->fruitColor = sf::Color(0, 200, 0, 255);

	this->gridsStates.reserve(height);
	this->rectangles.reserve(height);

	sf::RectangleShape rect(sf::Vector2f(tilePixelSize - 1, tilePixelSize - 1));
	rect.setFillColor(this->idleColor);
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color(200, 200, 200, 255));

	for (int y = 0; y < height; y++)
	{
		std::vector<GridState> temp1;
		std::vector<sf::RectangleShape> temp2;
		temp1.reserve(width);
		temp2.reserve(width);

		for (int x = 0; x < width; x++)
		{
			temp1.emplace_back(GridState::ILDE);
			rect.setPosition(x * tilePixelSize, y * tilePixelSize);			
			temp2.push_back(rect);
		}

		this->gridsStates.emplace_back(temp1);
		this->rectangles.emplace_back(temp2);
	}
	
	this->dimensions.first = static_cast<int>(width);
	this->dimensions.second = static_cast<int>(height);

	this->snake = new Snake(this->dimensions);
	
	for (int i = 0; i < this->snake->getBodyPos().size(); i++)
	{
		this->gridsStates[this->snake->getBodyPos()[i].second][this->snake->getBodyPos()[i].first] = GridState::SNAKE;
		this->rectangles[this->snake->getBodyPos()[i].second][this->snake->getBodyPos()[i].first].setFillColor(this->snakeColor);
	}
	
	this->fruits.reserve(numberOfFruits);

	for (int i = 0; i < numberOfFruits; i++)
		this->fruits.emplace_back(this->spawnFruit());

	this->gameOver = false;
}

Arena::~Arena()
{
	delete this->snake;
}

Snake& Arena::getSnake() const
{
	return *this->snake;
}

bool Arena::getGameOver() const
{
	return this->gameOver;
}

std::pair<int, int> Arena::getDimensions() const
{
	return this->dimensions;
}

void Arena::restart()
{
	for (int y = 0; y < this->gridsStates.size(); y++)
		for (int x = 0; x < this->gridsStates[y].size(); x++)
		{
			this->gridsStates[y][x] = GridState::ILDE;
			this->rectangles[y][x].setFillColor(this->idleColor);
		}

	delete this->snake;
	this->snake = new Snake(this->dimensions);

	for (int i = 0; i < this->snake->getBodyPos().size(); i++)
	{
		this->gridsStates[this->snake->getBodyPos()[i].second][this->snake->getBodyPos()[i].first] = GridState::SNAKE;
		this->rectangles[this->snake->getBodyPos()[i].second][this->snake->getBodyPos()[i].first].setFillColor(this->snakeColor);
	}

	for (int i = 0; i < this->fruits.size(); i++)
		this->fruits[i] = this->spawnFruit();

	this->gameOver = false;
}

void Arena::update()
{	
	this->snake->update();

	this->gridsStates[this->snake->getTailTrace().second][this->snake->getTailTrace().first] = GridState::ILDE;
	this->rectangles[this->snake->getTailTrace().second][this->snake->getTailTrace().first].setFillColor(this->idleColor);

	if (this->gridsStates[snake->getBodyPos()[0].second][snake->getBodyPos()[0].first] == GridState::SNAKE)
	{
		this->gameOver = true;
		return;
	}	
	else if (this->gridsStates[snake->getBodyPos()[0].second][snake->getBodyPos()[0].first] == GridState::FRUIT)
	{
		this->snake->grow();
		this->gridsStates[snake->getTailTrace().second][snake->getTailTrace().first] = GridState::SNAKE;
		this->rectangles[snake->getTailTrace().second][snake->getTailTrace().first].setFillColor(this->snakeColor);

		if (!this->isSpawnFruitPossible())
		{
			this->gameOver = true;
			return;
		}

		for (int i = 0; i < this->fruits.size(); i++)
		{
			if (this->fruits[i].getPos() == snake->getBodyPos()[0])
			{
				this->fruits[i] = this->spawnFruit();
				break;
			}
		}
	}
	
	this->gridsStates[snake->getBodyPos()[0].second][snake->getBodyPos()[0].first] = GridState::SNAKE;
	this->rectangles[snake->getBodyPos()[0].second][snake->getBodyPos()[0].first].setFillColor(this->snakeColor);
}

void Arena::render(sf::RenderTarget& target)
{
	for (auto& y : this->rectangles)
		for (auto& x : y)
			target.draw(x);
}
