#include "stdafx.h"
#include "Node.h"


Node::Node()
{
	this->parent = nullptr;
	this->gScore = 0;
	this->hScore = 0;
}

Node::Node(int x, int y, bool walkable, Node* parent)
{
	this->x = x;
	this->y = y;
	this->walkable = walkable;
	this->parent = parent;
}

Node::Node(Node * node)
{
	if (node == nullptr) return;

	x = node->x;
	y = node->y;
	gScore = node->gScore;
	hScore = node->hScore;
	fScore = node->fScore;
	parent = node->parent;
	walkable = node->walkable;
	isDiagonal = node->isDiagonal;
}

bool operator==(Node node1, Node node2)
{
	return (node1.fScore == node2.fScore && node1.gScore == node2.gScore && node1.hScore == node2.hScore && node1.x == node2.x && node1.y == node2.y && &node1.parent == &node2.parent && node1.walkable == node2.walkable);;
}

Node::~Node()
{
}
