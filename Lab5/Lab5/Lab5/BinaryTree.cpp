#include "BinaryTree.h"
#include <iomanip>
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

void BinaryTree::traversal()
{
	vector<vector<int>>positionsOnLevels;
	TLR(root, 1, positionsOnLevels);
	cout<<endl;
}

int BinaryTree::countNodalVerticles()
{
	int numberNodalVerticles=0;
	counterTLR(root, numberNodalVerticles);
	return numberNodalVerticles;
}

void BinaryTree::print()
{
	if(root!=nullptr)
		root->printTree();
}

void BinaryTree::TLR(Node*p, int level, vector<vector<int>>&positionsOnLevels)
{
	if(p!=nullptr)
	{
		int numberBranch=0;
		if(positionsOnLevels.size()<level)
		{
			positionsOnLevels.resize(level);
		}
		if(positionsOnLevels[level-1].empty()==true)
		{
			numberBranch=1;
			positionsOnLevels[level-1].push_back(1);
		}
		else
		{
			numberBranch=positionsOnLevels[level-1].back()+1;
			positionsOnLevels[level-1].push_back(numberBranch);
		}
		
		if((p->left!=nullptr)||(p->right!=nullptr))
		{
			cout<<"Nodal vertex: "<<setw(3)<<p->data<<" level: "<<setw(3)<<level<<" number of branch: "<<setw(3)<<numberBranch<<endl;
		}
		TLR(p->left, level+1, positionsOnLevels);
		TLR(p->right, level+1, positionsOnLevels);
	}
}

void BinaryTree::counterTLR(Node* current, int &numberNodalVerticles)
{
	if(current!=nullptr)
	{
		if((current->left!=nullptr)||(current->right!=nullptr))
		numberNodalVerticles++;
		counterTLR(current->left, numberNodalVerticles);
		counterTLR(current->right, numberNodalVerticles);	
	}
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
