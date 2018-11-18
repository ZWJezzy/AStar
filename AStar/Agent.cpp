#include "stdafx.h"
#include "Agent.h"

int Agent::agentCount = 0;

void WalkingTask(Point start, Point target, Map* map, int agentID);

Agent::Agent()
{
}

Agent::Agent(Map * map)
{
	_map = map;
	_agentID = agentCount;
	agentCount++;
}

void Agent::Walk(Point start, Point target)
{
	try
	{
		std::thread first(WalkingTask, start, target, _map, _agentID);
		//first.join();
		first.detach();
	}
	catch (const std::exception&)
	{
		
	}
}

void WalkingTask(Point start, Point target, Map* map, int agentID)
{
	Pathfinder* pathfinder = new Pathfinder(map);
	std::vector<Node> route = pathfinder->GetPath(start, target);

	for (int i = 0; i < route.size(); i++) {
		map->SetGridField(Point(route[i].x, route[i].y), 'A');
		map->Draw();
	}

	//map->Draw();
}

Agent::~Agent()
{
	agentCount--;
}