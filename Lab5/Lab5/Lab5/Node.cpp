#include "Node.h"

Node::Node(int data):data(data), left(nullptr), right(nullptr){}

Node::~Node()
{
	delete left;
	delete right;
}