#pragma once
#include <string>
#include <vector>
#include "Node.h"

class BinaryTree
{
    Node * root;
	Node * makeTree(std::vector<int>arr, int from, int n);
	void printTree(const std::string& prefix, Node* node, bool isLeft);
	void symPrintTree(Node* node, int indent);
	void TLR(Node*, int, int);
	void counter(Node* current, int &numberNodalVerticles);
public:
    BinaryTree();
	~BinaryTree();
	void make(std::vector<int> arr);
	void traversing();
	int countNodalVerticles();
	void print();
	void symmetricPrint();
};
