#include "stdafx.h"
#include "Pathfinder.h"
#include <iostream>

Pathfinder::Pathfinder()
{
}

Pathfinder::Pathfinder(Map * map)
{
	this->_map = map;
}

std::vector<Node> Pathfinder::GetPath(Point start, Point end)
{
	_start = start;
	_target = end;

	if (start == end || _map->IsNodeOutOfMap(start) || _map->IsNodeOutOfMap(end)) return std::vector<Node>();

	_closedList.clear();
	_openList.clear();

	std::vector<std::vector<Node*>> grid = _map->GetGrid();
	std::vector<Node> tmpList;
	Point currentLocation = start;
	Node tmpNode = Node(grid[start.y][start.x]);
	bool finished = false;
	bool targetReachable = false;

	std::cout << std::endl <<  "--------------- Logging ---------------" << std::endl;

	do {
		std::cout << "Currentnode: " << currentLocation.x << " : " << currentLocation.y << std::endl;

		tmpList = GetNeighbors(currentLocation);
		for (int i = 0; i < tmpList.size(); i++) {
			tmpList[i].parent = new Node(tmpNode);
			AddNodeToUniqueVector(_openList, tmpList[i]);
		}
		SetFScore(_openList, end);

		tmpNode = GetNodeWithLowestFScore(_openList);

		//DeleteNodeFromVector(_openList, currentLocation);
		DeleteNodeFromVector(_openList, Point(tmpNode.x, tmpNode.y));
		AddNodeToUniqueVector(_closedList, tmpNode);

		currentLocation.x = tmpNode.x;
		currentLocation.y = tmpNode.y;

		if (!(_openList.size() > 0) || currentLocation == end) {
			if (currentLocation == end) targetReachable = true;
			_closedList.push_back(GetNodeWithLowestFScore(_openList));
			std::cout << "Currentnode: " << currentLocation.x << " : " << currentLocation.y << std::endl;
			std::cout << "--------------- Finished ---------------" << std::endl << std::endl;
			finished = true;
		}
	} while (!finished);

	if(!targetReachable) return std::vector<Node>();
	
	//tmpList.clear();
	//tmpNode = GetNodeWithLowestFScore(_closedList);

	tmpNode = _closedList[_closedList.size()-2];
	tmpList.clear();

	while (tmpNode.parent != nullptr) {
		tmpList.push_back(tmpNode.parent);
		tmpNode = tmpNode.parent;
	}

	std::reverse(tmpList.begin(), tmpList.end());

	return tmpList;
}

void Pathfinder::DeleteNodeFromVector(std::vector<Node> &vector, Point target)
{
	for (int i = 0; i < vector.size(); i++) {
		Point *tmp = new Point(vector[i].x, vector[i].y);
		if (*tmp == target) vector.erase(vector.begin() + i);
	}
}

Node Pathfinder::GetNodeWithLowestFScore(std::vector<Node> nodes)
{
	Node* dest = nullptr;
	
	for (int i = 0; i < nodes.size(); i++)
		if(dest == nullptr || dest->fScore > nodes[i].fScore)
			dest = &nodes[i];
	
	return Node(*dest);
}

std::vector<Node> Pathfinder::GetNeighbors(Point currentLocation)
{
	std::vector<std::vector<Node*>> grid = _map->GetGrid();
	Node* node = nullptr;
	Node* currentNode = grid[currentLocation.y][currentLocation.x];
	Point* newPoint = new Point(currentLocation.x, currentLocation.y + 1);
	std::vector<Node> nodes;

	node = _map->IsNodeOutOfMap(*newPoint) ? nullptr : new Node(grid[newPoint->y][newPoint->x]);
	if (node != nullptr) {
		
		nodes.push_back(Node(node));
	}

	newPoint = new Point(currentLocation.x + 1, currentLocation.y);
	node = _map->IsNodeOutOfMap(*newPoint) ? nullptr : new Node(grid[newPoint->y][newPoint->x]);
	if (node != nullptr) {
		
		nodes.push_back(Node(node));
	}

	newPoint = new Point(currentLocation.x, currentLocation.y - 1);
	node = _map->IsNodeOutOfMap(*newPoint) ? nullptr : new Node(grid[newPoint->y][newPoint->x]);
	if (node != nullptr) {
		
		nodes.push_back(Node(node));
	}

	newPoint = new Point(currentLocation.x - 1, currentLocation.y);
	node = _map->IsNodeOutOfMap(*newPoint) ? nullptr : new Node(grid[newPoint->y][newPoint->x]);
	if (node != nullptr) {
		
		nodes.push_back(Node(node));
	}

	return nodes;
}

void Pathfinder::SetFScore(std::vector<Node> &nodes, Point end)
{
	for (int nodeIndex = 0; nodeIndex < nodes.size(); nodeIndex++) {
		if (nodes[nodeIndex].fScore > 0) continue;

		if (nodes[nodeIndex].parent != nullptr) nodes[nodeIndex].gScore += nodes[nodeIndex].parent->gScore + 1;
		else nodes[nodeIndex].gScore += 1;

		int xDistance = end.x - nodes[nodeIndex].x;
		int yDistance = end.y - nodes[nodeIndex].y;

		xDistance = xDistance < 0 ? xDistance *= -1 : xDistance;
		yDistance = yDistance < 0 ? yDistance *= -1 : yDistance;

		nodes[nodeIndex].hScore = xDistance + yDistance;
		nodes[nodeIndex].fScore = nodes[nodeIndex].gScore + nodes[nodeIndex].hScore;
	}

	//int x = 0;
	//int y = 0;

	//std::vector<std::vector<Node*>> grid = _map->GetGrid();

	//for (int nodeIndex = 0; nodeIndex < nodes.size(); nodeIndex++) {
	//	if (nodes[nodeIndex].fScore > 0) continue;

	//	x = nodes[nodeIndex].x;
	//	y = nodes[nodeIndex].y;
	//	if (grid[y][x]->parent != nullptr) grid[y][x]->gScore += grid[y][x]->parent->gScore+1;
	//	else grid[y][x]->gScore += 1;

	//	int xDistance = end.x - grid[y][x]->x;
	//	int yDistance = end.y - grid[y][x]->y;

	//	xDistance = xDistance < 0 ? xDistance *= -1 : xDistance;
	//	yDistance = yDistance < 0 ? yDistance *= -1 : yDistance;

	//	nodes[nodeIndex].hScore = xDistance + yDistance;
	//	nodes[nodeIndex].fScore = nodes[nodeIndex].gScore + nodes[nodeIndex].hScore;
	//}
}

void Pathfinder::AddNodesToUniqueVector(std::vector<Node> &list, std::vector<Node> nodes)
{
	for (int i = 0; i < nodes.size(); i++) {
		AddNodeToUniqueVector(list, nodes[i]);
	}
}

void Pathfinder::AddNodeToUniqueVector(std::vector<Node>& list, Node node)
{
	if (std::find(_openList.begin(), _openList.end(), node) == _openList.end() && std::find(_closedList.begin(), _closedList.end(), node) == _closedList.end() && !(Point(node.x, node.y) == _start)) {
		list.push_back(node);
	}
}

Pathfinder::~Pathfinder()
{
}
