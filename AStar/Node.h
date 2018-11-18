#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
public:
	Node();
	Node(int x, int y, bool walkable, Node* parent);
	Node(Node* node);
	~Node();
	int x;
	int y;
	unsigned int gScore;
	unsigned int hScore;
	unsigned int fScore;
	Node* parent;
	bool walkable = true;
	bool isDiagonal;
	char activeAgent;
	friend bool operator==(Node node1, Node node2);
};

#endif // !NODE_H