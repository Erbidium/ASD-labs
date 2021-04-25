#pragma once
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
public:
    BinaryTree():root(nullptr){}
	~BinaryTree();
    void buildTree(std::vector<int>arr);
	void printTree()const;
};
