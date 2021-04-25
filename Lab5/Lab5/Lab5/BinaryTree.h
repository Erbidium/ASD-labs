#pragma once
#include <string>
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
public:
    BinaryTree():root(nullptr){}
	~BinaryTree();
	Node * getRoot(){return root;}
    void buildTree(std::vector<int>arr);
	void printTree(const std::string& prefix, Node* node, bool isLeft);
};
