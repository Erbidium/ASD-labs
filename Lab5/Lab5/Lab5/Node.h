#pragma once
#include <iostream>

class Node
{
	void printTree(bool isRight, std::string indent);
public:
    int data;
    Node *left, *right;
    Node(int);
	~Node();
	void printTree();
};
