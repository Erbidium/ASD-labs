#pragma once
#include <string>
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
	Node * makeTree(std::vector<int>arr, int from, int n);
	void printTree(const std::string& prefix, Node* node, bool isLeft);
public:
    BinaryTree();
	~BinaryTree();
	void make(std::vector<int> arr);
	void print();
};
