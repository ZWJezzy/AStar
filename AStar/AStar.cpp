// AStar.cpp: Defines the entrypoint for the console application
//

#include "stdafx.h"
#include "Map.h"
#include "Pathfinder.h"
#include "Agent.h"

#include <iostream>

int main()
{
	int mapWidth = 0;
	int mapHeight = 0;

	std::cout << "Breite:\t";
	std::cin >> mapWidth;

	std::cout << "Hoehe:\t";
	std::cin >> mapHeight;

	system("cls");

	Map* map = new Map(mapWidth, mapHeight);
	map->PrepareNonWalkableNodes(std::vector<Point> {Point(7, 6), Point(7, 7), Point(7, 8), Point(7, 9), Point(7, 10), Point(7, 11), Point(7, 12), Point(7, 13), Point(7, 14), Point(7, 15), Point(7, 16), Point(7, 17), Point(7, 18), Point(7, 19)});
	//Agent* agent = new Agent(map);
	Agent* agent2 = new Agent(map);
	
	//agent->Walk(Point(0, 2), Point(18, 18));
	agent2->Walk(Point(6, 9), Point(10, 10));
	
	system("pause");
    return 0;
}

