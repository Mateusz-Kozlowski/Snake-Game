#pragma once

enum class Direction { UP = 0, DOWN, LEFT, RIGHT, NONE };

class Snake
{
private:
	std::vector<std::pair<int, int> > bodyPos;
	std::pair<int, int> tailTrace;

	Direction dir;
	Direction lastDir;

	std::pair<int, int> arenaSize;

public:
	Snake(std::pair<int, int> arenaSize);

	std::vector<std::pair<int, int> > getBodyPos() const;
	std::pair<int, int> getTailTrace() const;

	void changeDir(Direction dir);
	void resetDir();
	void grow();
	void update();
};

