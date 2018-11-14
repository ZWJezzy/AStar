#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <Windows.h>

Map::Map()
{
}

Map::Map(int width, int heigth)
{
	Node* parent = nullptr;

	for (int i = 0; i<heigth; i++)
	{
		std::vector<Node*> tmp;
		for (int j = 0; j < width; j++)
		{
			Node* node = new Node();
			node->x = j;
			node->y = i;
			if (parent != nullptr)
			{
				node->parent = parent;
				parent = node;
			}
			tmp.push_back(node);
		}
		_grid.push_back(tmp);
	}

	this->_width = width;
	this->_heigth = heigth;
}


Map::~Map()
{
	_grid.clear();
}

int Map::getWidth()
{
	return this->_width;
}

int Map::getHeigth()
{
	return this->_heigth;
}

std::vector<std::vector<Node*>> Map::GetGrid()
{
	return _grid;
}

void Map::SetGridField(Point currentPoint, char character)
{
	_mutex.lock();
	_grid[currentPoint.y][currentPoint.x]->activeAgent = character;
	_mutex.unlock();
}

void Map::PrepareNonWalkableNodes(std::vector<Point> points)
{
	for (int i = 0; i < points.size(); i++)
	{
		if (!IsNodeOutOfMap(points[i])) _grid[points[i].y][points[i].x]->walkable = false;
	}
}

void Map::Draw()
{
	Sleep(150);
	system("cls");
	for (int i = _heigth-1; i >= 0; i--) {
		for (int j = 0; j < _width; j++) {
			if (_grid.at(i).at(j)->walkable)
				if(!isblank(_grid[i][j]->activeAgent)) std::cout << "[" << _grid[i][j]->activeAgent << "]";
				else "[ ]";
			else
				std::cout << "[X]";
		}
		std::cout << std::endl;
	}
}

//Just implemented for some debugging sessions
void Map::Draw(Point start, Point target)
{
	for (int i = 0; i < _heigth; i++) {
		for (int j = 0; j < _width; j++) {
			if (_grid[i][j]->walkable) {
				if (start == Point(j, i)) std::cout << "[S]";
				else if (target== Point(j, i)) std::cout << "[Z]";
				else std::cout << "[ ]";
			}
			else
				std::cout << "[X]";
		}
		std::cout << std::endl;
	}
}

bool Map::IsNodeOutOfMap(Point point)
{
	return (point.x < 0 || point.x >= _width) || (point.y < 0 || point.y >= _heigth) || !_grid[point.y][point.x]->walkable;
}
