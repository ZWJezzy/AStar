#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Map.h"
#include "Node.h"
#include "Point.h"

class Pathfinder
{
public:
	Pathfinder();
	Pathfinder(Map* map);
	std::vector<Node> GetPath(Point start, Point end);
	~Pathfinder();

private:
	void DeleteNodeFromVector(std::vector<Node> &vector, Point target);
	Node GetNodeWithLowestFScore(std::vector<Node> nodes);
	std::vector<Node> GetNeighbors(Point currentLocation);
	void SetFScore(std::vector<Node> &nodes, Point end);
	void AddNodesToUniqueVector(std::vector<Node> &list, std::vector<Node> nodes);
	void AddNodeToUniqueVector(std::vector<Node> &list, Node node);
	Map* _map;
	std::vector<Node> _openList;
	std::vector<Node> _closedList;
	Point _start;
	Point _target;
};

#endif // !PATHFINDER_H