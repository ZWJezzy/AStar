#pragma once
#include "Map.h"
#include "Point.h"
#include "Pathfinder.h"
#include <thread>

class Agent
{
public:
	Agent();
	Agent(Map* map);
	void Walk(Point start, Point target);
	~Agent();
	static int agentCount;

private:
	Map * _map;
	int _agentID;
};

void WalkingTask(Point start, Point target, Map* map, int agentID);