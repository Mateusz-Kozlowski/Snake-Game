#pragma once

class PathFinder
{
private:
	std::map<std::pair<int, int>, std::pair<int, int> > nextNodes;

public:
	PathFinder(const std::string& filePath);
	~PathFinder();

	std::pair<int, int> getNextNode(std::pair<int, int> startNode);
};
