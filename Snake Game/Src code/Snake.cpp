#include "stdafx.h"
#include "Snake.h"

Snake::Snake(std::pair<int, int> arenaSize)
{
	this->arenaSize = arenaSize;
	
	srand(static_cast<unsigned>(time(0)));
	
	int temp = rand() % 4;
	
	if (temp == 0)
		this->dir = Direction::UP;
	else if (temp == 1)
		this->dir = Direction::DOWN;
	else if (temp == 2)
		this->dir = Direction::LEFT;
	else
		this->dir = Direction::RIGHT;
	
	this->lastDir = this->dir;

	int x = rand() % arenaSize.first;
	int y = rand() % arenaSize.second;
	this->bodyPos.emplace_back(x, y);

	this->tailTrace = { x - 1, y - 1 };

	if (this->tailTrace.first < 0)
		this->tailTrace.first = arenaSize.first - 1;

	if (this->tailTrace.second < 0)
		this->tailTrace.second = arenaSize.second - 1;
}

std::vector<std::pair<int, int> > Snake::getBodyPos() const
{
	return this->bodyPos;
}

std::pair<int, int> Snake::getTailTrace() const
{
	return this->tailTrace;
}

void Snake::changeDir(Direction dir)
{
	if (dir == Direction::UP && this->lastDir != Direction::DOWN)
		this->dir = dir;

	else if (dir == Direction::DOWN && this->lastDir != Direction::UP)
		this->dir = dir;

	else if (dir == Direction::LEFT && this->lastDir != Direction::RIGHT)
		this->dir = dir;

	else if (dir == Direction::RIGHT && this->lastDir != Direction::LEFT)
		this->dir = dir;
}

void Snake::resetDir()
{
	this->lastDir = Direction::NONE;
	this->dir = Direction::NONE;
}

void Snake::grow()
{
	this->bodyPos.push_back(this->tailTrace);
}

void Snake::update()
{
	this->tailTrace.first = this->bodyPos[this->bodyPos.size() - 1].first;
	this->tailTrace.second = this->bodyPos[this->bodyPos.size() - 1].second;

	// przesuwanie cia³a:
	for (int i = this->bodyPos.size() - 1; i > 0; i--)
	{
		this->bodyPos[i].first = this->bodyPos[i - 1].first;
		this->bodyPos[i].second = this->bodyPos[i - 1].second;
	}	
	
	// przemieszczanie siê g³owy wê¿a:
	if (this->dir == Direction::UP)
		this->bodyPos[0].second--;

	else if (this->dir == Direction::DOWN)
		this->bodyPos[0].second++;

	else if (this->dir == Direction::LEFT)
		this->bodyPos[0].first--;

	else
		this->bodyPos[0].first++;

	// je¿eli w¹¿ przeszed³ przez œcianê:
	if (this->bodyPos[0].first < 0)
		this->bodyPos[0].first = this->arenaSize.first - 1;

	else if (this->bodyPos[0].first >= this->arenaSize.first)
		this->bodyPos[0].first = 0;

	else if (this->bodyPos[0].second < 0)
		this->bodyPos[0].second = this->arenaSize.second - 1;

	else if (this->bodyPos[0].second >= this->arenaSize.second)
		this->bodyPos[0].second = 0;

	this->lastDir = this->dir;
}
