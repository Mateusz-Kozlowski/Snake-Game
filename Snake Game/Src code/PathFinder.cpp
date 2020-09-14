#include "stdafx.h"
#include "PathFinder.h"

PathFinder::PathFinder(const std::string& filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		std::cout << "ERROR: PathFinder::PathFinder: CANNOT OPEN: " << filePath << '\n';
		exit(41);
	}
	while (ifs.good())
	{
		int a, b, c, d;
		ifs >> a >> b >> c >> d;
		this->nextNodes[{a, b}] = { c, d };
	}
	ifs.close();
}

PathFinder::~PathFinder()
{

}

std::pair<int, int> PathFinder::getNextNode(std::pair<int, int> startNode)
{
	return this->nextNodes[startNode];
}
