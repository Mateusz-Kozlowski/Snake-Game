#include "stdafx.h"
#include "Fruit.h"

Fruit::Fruit(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}

std::pair<int, int> Fruit::getPos() const
{
	return { this->x, this->y };
}

void Fruit::setPos(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}
