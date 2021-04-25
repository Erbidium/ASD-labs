#pragma once
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
	Node * makeTree(std::vector<int>, int, int);
	void TLR(Node*, int, std::vector<std::vector<int>>&);
	void counterTLR(Node*, int&);
public:
    BinaryTree();
	~BinaryTree();
	void make(std::vector<int>);
	void traversal();
	int countNodalVerticles();
	void print();
};
