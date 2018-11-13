#include "stdafx.h"
#include "Point.h"

Point::Point()
{
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::~Point()
{
}

bool operator==(const Point & p1, const Point & p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}
