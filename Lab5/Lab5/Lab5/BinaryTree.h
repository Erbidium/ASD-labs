#pragma once
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
	Node * makeTree(std::vector<int>, int, int);
	void TLR(Node*, int, std::vector<std::vector<int>>&);
	void counter(Node*, int&);
public:
    BinaryTree();
	~BinaryTree();
	void make(std::vector<int>);
	void traversing();
	int countNodalVerticles();
	void print();
};
