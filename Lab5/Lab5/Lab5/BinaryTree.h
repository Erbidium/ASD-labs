#pragma once
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
	Node * makeTree(std::vector<int>arr, int from, int n);
	void TLR(Node*, int, int);
	void counter(Node* current, int &numberNodalVerticles);
public:
    BinaryTree();
	~BinaryTree();
	void make(std::vector<int> arr);
	void traversing();
	int countNodalVerticles();
	void print();
};
