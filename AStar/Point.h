#pragma once
class Point
{
public:
	Point();
	Point(int x, int y);
	friend bool operator==(const Point &p1, const Point &p2);
	~Point();
	int x;
	int y;
};

