﻿#include "BinaryTree.h"
#include <stack>
#include <iostream>

using namespace std;

BinaryTree::BinaryTree():root(nullptr)
{}

BinaryTree::~BinaryTree()
{
	delete root;
}

void BinaryTree::make(vector<int> arr)
{
	root=makeTree(arr, 0, arr.size());
}

void BinaryTree::print()
{
	printTree("", root, false);
}

Node* BinaryTree::makeTree(std::vector<int> arr, int from, int n)
{
	if(n==0) return nullptr;
	Node * p=new Node(arr[from]);
	int nl=n/2;
	int nr=n-nl-1;
	p->left=makeTree(arr, from+1, nl);
	p->right=makeTree(arr, from+1+nl, nr);
	return p;
}

void BinaryTree::printTree(const string& prefix, Node* node, bool isLeft) {
  if (node != nullptr) {
    cout << prefix;
    cout << (isLeft ? char(195) : char(192)) << char(196) << char(196);
    cout << node->data << endl;
    printTree(prefix + (isLeft ? "|   " : "    "), node->left, true);
	printTree(prefix + (isLeft ? "|   " : "    "), node->right, false);
  }
}
