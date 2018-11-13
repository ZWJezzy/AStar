#ifndef MAP_H
#define MAP_H

#include "Node.h"
#include "Point.h"
#include <mutex>

class Map
{
public:
	Map();
	Map(int width, int heigth);
	~Map();
	int getWidth();
	int getHeigth();
	std::vector<std::vector<Node*>> GetGrid();
	void SetGridField(Point currentPoint, char character);
	void PrepareNonWalkableNodes(std::vector<Point> points);
	void Draw();
	void Draw(Point start, Point target);
	bool IsNodeOutOfMap(Point point);

private:
	int _width;
	int _heigth;
	std::vector<std::vector<Node*>> _grid;
	std::mutex _mutex;
};

#endif // !MAP_H