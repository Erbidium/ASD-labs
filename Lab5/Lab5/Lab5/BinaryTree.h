#pragma once
#include <string>
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
public:
    BinaryTree();
	~BinaryTree();
	Node * getRoot();
	void setRoot(Node * newRoot);
	Node * makeTree(std::vector<int>arr, int from, int n);
	void printTree(const std::string& prefix, Node* node, bool isLeft);
};
