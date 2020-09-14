#pragma once

class Fruit
{
private:
	int x, y;

public:
	Fruit(int posX, int posY);
	
	std::pair<int, int> getPos() const;

	void setPos(int posX, int posY);
};
